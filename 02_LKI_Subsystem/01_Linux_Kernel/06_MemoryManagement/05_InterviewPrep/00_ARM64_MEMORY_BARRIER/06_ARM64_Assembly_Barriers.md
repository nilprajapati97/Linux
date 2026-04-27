# ARM64 Assembly Barriers

## Key Instructions
- `dmb sy` — Full system memory barrier
- `dmb st` — Store barrier
- `dmb ld` — Load barrier
- `dsb sy` — Synchronization barrier
- `isb`    — Instruction barrier

## Example
```asm
mov x0, #1
dmb sy
mov x1, #2
```

## When to Use
- Use in low-level code, drivers, or when writing kernel primitives.

---

**Interview Tip:**
Be able to recognize and explain these instructions in kernel or driver code.
