# Kernel Control-Flow View

This document answers a control-flow question: where does `__cpu_setup` sit in the full early kernel path, and what does the kernel gain from it?

## Primary control flow

The primary CPU path is:

1. `primary_entry`
2. `record_mmu_state`
3. `preserve_boot_args`
4. `__pi_create_init_idmap`
5. cache maintenance
6. `init_kernel_el`
7. `__cpu_setup`
8. `__primary_switch`
9. `__enable_mmu`
10. `__pi_early_map_kernel`
11. `__primary_switched`
12. `start_kernel`

## What the kernel gains at each stage

### Before __cpu_setup

The kernel has:

- preserved boot arguments
- an early idmap in RAM
- a normalized exception-level state

But it does not yet have active virtual memory.

### After __cpu_setup

The kernel has:

- a programmed EL1 translation policy
- a prepared `SCTLR_EL1` MMU-on value in `x0`

But it still does not have active virtual memory.

### After __enable_mmu

The kernel gains:

- active stage-1 translation
- valid TTBR roots
- a safe MMU-on execution context

### After __pi_early_map_kernel

The kernel gains:

- the properly mapped kernel image
- relocation-aware early mapping behavior
- the ability to move toward the normal high-level kernel world

### After __primary_switched

The kernel gains:

- proper vector base installation
- initial task and per-CPU stack context
- the saved FDT pointer in kernel-visible state
- access to `start_kernel()`

## Secondary control flow

The secondary CPU path is shorter:

1. `secondary_holding_pen` or `secondary_entry`
2. `init_kernel_el`
3. optional VA52 check
4. `__cpu_setup`
5. `__enable_mmu`
6. `__secondary_switched`
7. `secondary_start_kernel`

## Why the same function is reused

The kernel wants one central implementation for low-level per-CPU translation setup. That reduces duplication and keeps CPU capability handling consistent across boot CPU and secondary CPUs.
