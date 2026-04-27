# What is a Memory Barrier?

## Definition
A memory barrier (also called a fence) is an instruction or operation that enforces an ordering constraint on memory operations issued before and after the barrier.

## Why Use Memory Barriers?
- Prevents CPUs and compilers from reordering memory accesses across the barrier.
- Ensures correct synchronization between threads/CPUs.

## Types
- Full (DMB SY)
- Store (DMB ST)
- Load (DMB LD)

---

**Interview Tip:**
Be ready to explain what a memory barrier is and why it is needed in concurrent code.
