# Memory Ordering Fundamentals

## What is Memory Ordering?
- The order in which memory operations (loads and stores) appear to execute across CPUs.
- CPUs and compilers may reorder instructions for performance.

## Why Does It Matter?
- In concurrent programs, reordering can lead to subtle bugs.
- Example: One thread writes data, another reads it — without barriers, the order is not guaranteed!

## ARM64 vs x86
- x86 is mostly strongly ordered (Total Store Order).
- ARM64 is weakly ordered — explicit barriers are often required.

---

**Interview Tip:**
Be ready to explain why memory ordering matters and how it differs between architectures.
