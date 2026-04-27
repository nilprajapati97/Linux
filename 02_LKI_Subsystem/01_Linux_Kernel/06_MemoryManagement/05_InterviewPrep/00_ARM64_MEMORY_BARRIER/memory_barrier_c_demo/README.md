# Simple ARM64 Memory Barrier Demo

This directory contains a simple C program that demonstrates the use of memory barriers in a multi-threaded context on ARM64/Linux.

## Requirements
- Linux system (preferably ARM64, but works on x86 as well)
- GCC with pthread support

## Build
```sh
gcc -O2 -pthread -o simple_mb_demo simple_mb_demo.c
```

## Run
```sh
./simple_mb_demo
```

## What It Does
- Launches two threads that write and read shared variables with a memory barrier in between.
- Looks for the rare case where both threads read zero, which would indicate a reordering (should not happen with barriers).
- Demonstrates the importance of memory barriers in concurrent programming.

## Output Example
```
Test finished.
```

If you ever see:
```
Reordering observed at iteration X! r1=0, r2=0
```
It means the barrier failed (should not happen with proper barriers).

---

**Try removing the `__sync_synchronize()` calls to see the effect of no barriers!**
