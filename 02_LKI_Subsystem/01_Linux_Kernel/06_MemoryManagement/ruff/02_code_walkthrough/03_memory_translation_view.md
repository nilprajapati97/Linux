# Memory Translation View of __cpu_setup

This file explains `__cpu_setup` from the point of view of the memory subsystem rather than the instruction stream.

## Translation is a contract between three things

At MMU-on time the CPU needs three categories of information to agree with each other:

1. page tables in memory
2. translation-control registers
3. final enable state in `SCTLR_EL1`

If any one of these is inconsistent with the others, early boot can fail catastrophically.

## What already exists before __cpu_setup

Before the function runs:

- the idmap page-table memory has already been created
- the page tables describe an identity-mapped region for early code
- the final kernel mapping is not yet fully installed

So the page-table objects exist first, but the hardware policy for interpreting them is not fully programmed yet.

## What __cpu_setup contributes

`__cpu_setup` contributes the interpretation rules:

- `MAIR_EL1` tells the MMU what each memory attribute index means
- `TCR_EL1` tells the MMU how to walk page tables and how to interpret address size, granule size, shareability, and caching
- `TCR2_EL1` and related registers extend that model on newer CPUs

## What __enable_mmu contributes later

`__enable_mmu` contributes the activation step:

- load translation roots into `TTBR0_EL1` and `TTBR1_EL1`
- set `SCTLR_EL1.M`
- synchronize with barriers and instruction-cache invalidation

## Memory-lens interpretation

From a pure memory-management perspective, the sequence is:

1. construct early page tables in RAM
2. clean or invalidate them so the hardware sees the correct contents
3. program the hardware's understanding of those tables
4. load the root pointers to those tables
5. enable translation
6. construct the final long-term kernel mapping

## Why this is a layered design

Linux keeps page-table construction separate from translation-policy setup because:

- it reduces the chance of ordering bugs
- it makes it easier to adapt to different CPUs and page sizes
- it localizes feature detection and errata handling in one place
- it lets the boot path reuse the same low-level CPU setup on both primary and secondary CPUs

## Important consequence for debugging

If early boot fails after `bl __cpu_setup` but before `start_kernel`, the failure is often in one of these categories:

- page-table layout problem
- unsupported granule or address-width mismatch
- barrier or cache-maintenance issue
- wrong EL or SCTLR/TCR expectations
- platform firmware entering with a state Linux did not expect
