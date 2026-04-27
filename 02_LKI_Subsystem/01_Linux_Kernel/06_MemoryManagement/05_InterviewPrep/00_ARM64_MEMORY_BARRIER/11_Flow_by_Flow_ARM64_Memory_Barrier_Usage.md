# Flow-by-Flow: ARM64 Memory Barrier Usage

This document provides a flow-based explanation of how and where to use memory barriers in ARM64 kernel and C code, with code references.

## 1. Identify Shared Data
- What variables are accessed by multiple threads/CPUs?

## 2. Analyze Access Patterns
- Are there races? Is ordering required?

## 3. Insert Barriers
- Use the appropriate barrier (DMB, DSB, ISB, smp_mb, etc.)

## 4. Test and Verify
- Use stress tests, static analysis, and code review.

## 5. Debug and Iterate
- If bugs appear, check for missing or misplaced barriers.

---

**Interview Tip:**
Be ready to walk through a real-world scenario and explain your barrier placement and reasoning.
