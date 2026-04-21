# TLB, Cache, Barriers, and MMU Enable

The low-level boot code around `__cpu_setup` is full of invalidations and barriers because the CPU must not observe partially updated translation state.

## Why barriers matter here

When Linux transitions from MMU-off execution to MMU-on execution, correctness depends on strict ordering between:

- page-table writes
- system-register writes
- TLB invalidation
- instruction fetch behavior
- cache visibility

If any of these are observed out of order, the CPU can fetch stale instructions or walk stale page tables.

## TLB invalidation in __cpu_setup

The function begins with `tlbi vmalle1` followed by `dsb nsh`.

### Effect

- stale EL1 stage-1 translations are discarded
- later translation state does not accidentally mix with earlier TLB contents

## Cache maintenance before and after the idmap

The code in `head.S` does different cache work depending on whether Linux entered with the MMU already on or not.

### Reason

Page tables written while the MMU is off may be seen differently by the memory system than page tables written through cached mappings. Linux therefore sanitizes those tables before relying on them.

## __enable_mmu ordering

The actual MMU-on path does the following:

1. validate that the selected granule size is supported
2. load `TTBR0_EL1`
3. load `TTBR1_EL1`
4. write `SCTLR_EL1` with MMU-on bits set
5. execute `ISB`
6. invalidate local I-cache
7. execute `DSB` and `ISB`

## Why I-cache invalidation is done there

Instructions may have been fetched speculatively before the final text mapping and permissions are fully settled. The explicit I-cache invalidation forces the CPU to refetch instructions consistently after the control-state transition.

## CPU behavior after SCTLR_EL1.M becomes 1

Once `SCTLR_EL1.M` is set:

- instruction fetches become translated
- data accesses become translated
- page-table attributes start controlling memory type and permissions
- address interpretation changes from physical to virtual-stage-1 translation

This is the most important architectural transition in the early boot path.

## Key design rule

`__cpu_setup` prepares the policy. `__enable_mmu` commits the transition. The barriers make sure the hardware observes that transition in the correct order.
