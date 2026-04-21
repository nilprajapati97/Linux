# Idmap, TTBRs, and Early Page Tables

One of the hardest early-boot ideas to understand is why Linux builds page tables before the MMU is on.

## The short answer

The page tables are prepared first so that the CPU can switch to translated execution without losing the ability to fetch the code it is currently running.

## What the identity map does

The early identity map maps virtual addresses to the same physical addresses for the low-level boot code that must survive the MMU transition.

In practical terms, this means:

- before MMU-on, instruction fetch uses physical addressing
- after MMU-on, the same code must still be reachable through translation
- the identity map ensures the effective address remains valid across that transition

## Where the early idmap comes from

The boot path uses `__pi_create_init_idmap`, which is backed by the PI early mapping code. That code allocates and fills page-table entries in a reserved linker-script region dedicated to early boot.

## TTBR0 and TTBR1 roles

ARM64 uses two translation table base registers at EL1:

- `TTBR0_EL1` commonly covers the lower virtual address range
- `TTBR1_EL1` commonly covers the higher kernel virtual address range

During early boot Linux uses them in a staged way.

## Early use in __enable_mmu

For the primary CPU path:

- `x2` points to `__pi_init_idmap_pg_dir`
- `x1` points to `reserved_pg_dir`
- `__enable_mmu` writes `TTBR0_EL1` from the idmap
- `__enable_mmu` writes `TTBR1_EL1` from the reserved table

## Why not use swapper_pg_dir immediately

At that exact instant, Linux is still crossing from the physical boot world into the fully mapped kernel world. The final kernel mapping is not yet ready to be relied on. So Linux uses:

- a temporary idmap for continuity of execution
- a temporary kernel-side root while final mappings are built

Only after MMU-on does Linux map the kernel properly and move toward the final translation setup.

## Mental model

Think of early boot as a bridge with three segments:

1. physical-only execution
2. MMU-on execution with a temporary bridge mapping
3. MMU-on execution with the real kernel mapping

`__cpu_setup` belongs to the step that prepares the bridge controls. `__enable_mmu` activates the bridge. `__pi_early_map_kernel` finishes building the destination side of the bridge.
