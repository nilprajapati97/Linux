# Interview Q&A: ARM64 Memory Barriers

## Conceptual Questions
1. What is a memory barrier and why is it needed?
2. How do ARM64 and x86 differ in memory ordering?
3. What are the main types of barriers on ARM64?
4. When would you use a DSB vs a DMB?
5. What is the difference between a compiler barrier and a hardware barrier?

## Code/Kernel Questions
1. How do you use `smp_mb()` in the Linux kernel?
2. What happens if you forget a barrier in a lock-free algorithm?
3. How do you debug a suspected memory ordering bug?

## Practical Questions
1. How would you demonstrate a memory ordering bug in C?
2. How do you verify your code is correct on ARM64?

---

**Tip:** Practice explaining both the theory and practical usage of barriers, and be ready to reference code or real bugs.
