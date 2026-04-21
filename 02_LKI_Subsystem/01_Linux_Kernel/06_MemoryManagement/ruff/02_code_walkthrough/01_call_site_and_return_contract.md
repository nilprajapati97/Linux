# Call Site and Return Contract

The instruction in `head.S` is:

```asm
bl __cpu_setup
```

This is a normal branch-with-link instruction. It saves the return address in `x30` and transfers control to `arch/arm64/mm/proc.S::__cpu_setup`.

## Call-site context in primary_entry

Immediately before the call:

- the idmap page tables already exist
- boot arguments are saved
- the current EL state has been normalized by `init_kernel_el`
- `x20` holds the boot-mode result returned by `init_kernel_el`
- the MMU is still off

Immediately after the call, `head.S` branches to `__primary_switch`.

## Return contract of __cpu_setup

`__cpu_setup` returns:

- `x0` = `INIT_SCTLR_EL1_MMU_ON`

This value is not just informational. It is consumed by `__enable_mmu`, which expects:

- `x0` = `SCTLR_EL1` value to install
- `x1` = kernel-side translation root
- `x2` = identity map root

## What __cpu_setup does not return

It does not return page tables. It does not enable the MMU. It does not branch to C code. It does not perform general kernel initialization.

## Why the interface is this small

The early boot path is tightly constrained. The function returns a single critical control-register value because the caller already knows where the page-table roots are and because the actual MMU-on step must happen from an idmapped region under carefully controlled sequencing.

## Secondary CPU call-site

The secondary path also calls `__cpu_setup`, but from `secondary_startup`. That means the function is intentionally written as per-CPU low-level setup logic rather than primary-only boot logic.
