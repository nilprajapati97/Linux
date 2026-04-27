# Linux Kernel Memory Barrier APIs

## Common APIs
- `smp_mb()` — Full memory barrier
- `smp_rmb()` — Read (load) barrier
- `smp_wmb()` — Write (store) barrier
- `barrier()` — Compiler barrier only

## Usage Example
```c
x = 1;
smp_wmb();
y = 1;
```

## Why Use These?
- They abstract away architecture-specific details.
- Ensure correct ordering on all supported platforms.

---

**Interview Tip:**
Be ready to discuss when and why to use each API in kernel code.
