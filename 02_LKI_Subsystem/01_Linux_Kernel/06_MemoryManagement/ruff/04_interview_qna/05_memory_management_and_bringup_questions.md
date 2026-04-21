# Memory Management and Bring-up Questions

## Q1. Why is an identity map useful during early MMU bring-up?

### Answer

Because the CPU must continue fetching the same boot code across the moment when address translation becomes active. An identity map ensures that the effective translated view still points at the code that was being executed physically just before MMU-on.

## Q2. Why is TCR_EL1 programming so central to early boot?

### Answer

Because TCR_EL1 defines how stage-1 translation behaves: address size, translation granule, shareability, cacheability of table walks, and more. Even perfectly built page tables are useless if the CPU interprets them under the wrong translation-control regime.

## Q3. What are the main failure modes when enabling the MMU?

### Answer

- wrong TTBR root
- wrong granule selection
- wrong physical address size field
- stale TLB or I-cache state
- code not covered by the active mapping
- privilege or exception-level mismatch

A strong debugging answer explains how each one would manifest and how to isolate it.

## Q4. Why does Linux keep the early boot interfaces narrow?

### Answer

Because narrow interfaces are easier to validate in the most fragile execution phase. `__cpu_setup` returns the prepared `SCTLR_EL1` value instead of trying to own all later boot logic. That keeps responsibilities separated and makes the actual MMU-on step small and auditable.

## Q5. If asked to redesign early bring-up for maintainability, what would you propose?

### Answer

I would preserve the staged model, keep architecture-specific transitions explicit, improve traceability around feature-driven branches, and invest in validation hooks rather than collapsing phases together. In early boot, readability and correctness usually beat premature consolidation.
