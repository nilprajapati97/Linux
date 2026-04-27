# Debugging and Verification of Memory Barriers

## How to Debug
- Use kernel lockdep/barrier debugging features
- Static analysis tools (e.g., Smatch, Coccinelle)
- Hardware tracing (perf, ftrace)

## How to Verify
- Code review: Look for missing barriers in critical sections
- Stress tests: Try to trigger races
- Formal verification (rare, but possible)

---

**Interview Tip:**
Be ready to explain how you would debug or verify correct barrier usage in kernel code.
