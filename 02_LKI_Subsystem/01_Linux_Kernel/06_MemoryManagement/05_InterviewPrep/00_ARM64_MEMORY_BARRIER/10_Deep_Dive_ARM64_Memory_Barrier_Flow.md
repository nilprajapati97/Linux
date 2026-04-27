# Deep Dive: ARM64 Memory Barrier Flow

This document provides a step-by-step walkthrough of how memory barriers are used in ARM64 systems, with code and architecture references.

## 1. Code Path
- Application or kernel code issues loads/stores to shared variables.
- Without barriers, CPU or compiler may reorder operations.
- Insert barriers to enforce required ordering.

## 2. Barrier Placement
- Place barriers between critical operations (e.g., after a write, before a read).
- Use the correct barrier for the situation (full, store, load).

## 3. Kernel Example
```c
x = 1;
smp_wmb();
y = 1;
```

## 4. Assembly Example
```asm
str x0, [addr1]
dmb sy
str x1, [addr2]
```

---

**Interview Tip:**
Be ready to walk through a code path and explain where and why barriers are needed.
