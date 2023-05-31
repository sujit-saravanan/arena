# arena
A basic C++ memory arena. It uses a unique_ptr to reference its buffer as to avoid needing a non-default destructor. This allows the class to use the rule of 0, making additional constructors/assignment operators unecessary. It also implements a "Temporal Arena", which allows one to revert to a previously set allocation size.

## Performance
Performance for appending is within margin of error of standard contiguous structures:
### Arena (Exceptions Enabled): 
```
 Performance counter stats for 'output/arena' (1000 runs):

     4,911,367,790      cycles                                                                  ( +-  0.92% )
     4,534,322,008      instructions                     #    1.85  insn per cycle              ( +-  0.91% )
        52,789,630      cache-misses                                                            ( +-  0.91% )
        48,394,516      L1-dcache-load-misses                                                   ( +-  0.91% )
```

### Arena (Exceptions Disabled):
```
 Performance counter stats for 'output/arena' (1000 runs):

     4,753,883,970      cycles                                                                  ( +-  0.92% )
     4,518,841,833      instructions                     #    1.91  insn per cycle              ( +-  0.91% )
        53,864,410      cache-misses                                                            ( +-  0.91% )
        48,444,247      L1-dcache-load-misses                                                   ( +-  0.91% )
```

### C Array: 
```
 Performance counter stats for 'output/arena' (1000 runs):

     4,788,605,156      cycles                                                                  ( +-  0.91% )
     4,456,960,322      instructions                     #    1.85  insn per cycle              ( +-  0.91% )
        52,750,969      cache-misses                                                            ( +-  0.91% )
        48,236,330      L1-dcache-load-misses                                                   ( +-  0.91% )
```

### Array: 
```
 Performance counter stats for 'output/arena' (1000 runs):

     4,764,485,777      cycles                                                                  ( +-  0.91% )
     4,457,911,049      instructions                     #    1.88  insn per cycle              ( +-  0.91% )
        53,283,786      cache-misses                                                            ( +-  0.91% )
        48,364,100      L1-dcache-load-misses                                                   ( +-  0.91% )
```

### Vector:
```
 Performance counter stats for 'output/arena' (1000 runs):

     5,049,859,478      cycles                                                                  ( +-  0.90% )
     4,521,869,079      instructions                     #    1.77  insn per cycle              ( +-  0.91% )
        53,196,717      cache-misses                                                            ( +-  0.91% )
        48,589,582      L1-dcache-load-misses                                                   ( +-  0.91% )
```

## Additional Work
As of right now, there is no specified alignment requirement for the buffer. Doing so while maintaining the unique_ptr would require a custom pointer implementation.
