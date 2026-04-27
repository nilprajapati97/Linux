# Common Bugs and Pitfalls with Memory Barriers

## Typical Issues
- Missing barriers: Data races, subtle bugs
- Unnecessary barriers: Performance loss
- Using compiler barriers instead of hardware barriers
- Assuming x86 rules apply to ARM64

## Real-World Example
- Double-checked locking without barriers can fail on ARM64

---

**Interview Tip:**
Be ready to discuss real bugs caused by missing or misplaced barriers.
