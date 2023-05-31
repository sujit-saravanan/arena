#pragma once

#ifdef ARENA_EXCEPTIONS
#include <fmt/format.h>
#endif

#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <iostream>

template<size_t Capacity>
class Arena {
public: // Constructor/Destructor/Overloads (Rule of 0 is in place)

public: // Public Member Functions
        template<typename T = void, size_t count = 0>
        [[nodiscard]] constexpr T *alloc()
#ifndef ARENA_EXCEPTIONS
        noexcept
#endif
        {
#ifdef ARENA_EXCEPTIONS
                if (m_pointer + sizeof(T) * count > Capacity) throw fmt::system_error(errno, "Exceeded allocation capacity ({} > {})", m_pointer + sizeof(T) * count, Capacity);
#endif
                auto pointer = m_data.get() + m_pointer;
                m_pointer += sizeof(T) * count;
                
                return reinterpret_cast<T *>(pointer);
        };
        
        template<typename T>
        constexpr void append(const T &object)
#ifndef ARENA_EXCEPTIONS
        noexcept
#endif
        {
#ifdef ARENA_EXCEPTIONS
                if (m_pointer + sizeof(T) > Capacity) throw fmt::system_error(errno, "Exceeded allocation capacity({} > {})", m_pointer + sizeof(T), Capacity);
#endif
                
                std::memcpy(m_data.get() + m_pointer, &object, sizeof(T));
                m_pointer += sizeof(T);
        };
        
        template<typename T = void>
        constexpr T &at(size_t index) const
#ifndef ARENA_EXCEPTIONS
        noexcept
#endif
        {
#ifdef ARENA_EXCEPTIONS
                if (m_pointer + index > Capacity) throw fmt::system_error(errno, "Out of bounds exception ({} >= {})", m_pointer + index, Capacity);
#endif
                
                return reinterpret_cast<T &>(*(m_data.get() + index));
        }
        
        inline constexpr void reset() noexcept {
                m_pointer = 0;
        }
        
        [[nodiscard]] inline constexpr size_t capacity() const noexcept {
                return Capacity;
        }
        
        [[nodiscard]] inline constexpr size_t size() const noexcept {
                return m_pointer;
        }
        
        [[nodiscard]] inline constexpr void *data() const noexcept {
                return m_data.get();
        }

public: // Public Member Variables
private: // private Member Functions
private: // private Member Variables
        std::unique_ptr<uint8_t[]> m_data = std::make_unique<uint8_t[]>(Capacity);
        size_t m_pointer{0};
};

template<size_t Capacity>
class TemporalArena : public Arena<Capacity> {
public: // public Member Functions
        inline constexpr void save() noexcept {
                m_revert_point = this->m_pointer;
        }
        
        inline constexpr void revert() noexcept {
                this->m_pointer = m_revert_point;
        }

private: // private Member Variables
        size_t m_revert_point{0};
};
