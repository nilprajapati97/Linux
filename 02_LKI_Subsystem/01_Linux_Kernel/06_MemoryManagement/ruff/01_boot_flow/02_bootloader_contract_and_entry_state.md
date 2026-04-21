# Bootloader Contract and Entry State

The ARM64 kernel expects a very specific entry state before `primary_entry` begins.

## Boot protocol assumptions

According to `Documentation/arch/arm64/booting.rst`, the bootloader must provide at least the following:

- RAM initialized
- a valid device tree blob
- the uncompressed kernel image ready to execute
- entry into the kernel at the correct image entry point

## Register state on entry

The primary CPU enters the kernel with:

- `x0` = physical address of the DTB
- `x1` = 0
- `x2` = 0
- `x3` = 0

Linux preserves these values early because it cannot assume later phases will still have them intact.

## Execution mode requirements

Before entering Linux:

- interrupts must be masked in `PSTATE.DAIF`
- the CPU must be in non-secure EL1 or EL2
- the MMU must be off
- the instruction cache may be on or off
- stale instruction data for the kernel image must not be present

## Why Linux re-checks this state

Firmware is allowed to vary across platforms. Even when the documented contract is followed, Linux still validates and normalizes important state in early assembly because it must run on many SoCs, many firmware stacks, and several exception-level entry modes.

## What record_mmu_state does

`record_mmu_state` checks:

- which exception level the CPU entered in
- whether the MMU was already enabled
- whether endianness needs to be corrected

This gives Linux a reliable low-level baseline before it starts programming translation state.

## What preserve_boot_args does

`preserve_boot_args` saves the bootloader-provided arguments, especially the DTB pointer, before later low-level code begins reusing general-purpose registers for CPU bring-up.

## Practical interpretation

At this point Linux is not yet a fully running kernel. It is still in architecture bring-up mode:

- no scheduler
- no normal interrupt handling path
- no device probing
- no slab allocator in the usual sense
- no fully initialized virtual memory model

The code around `bl __cpu_setup` belongs to this extremely constrained stage.
