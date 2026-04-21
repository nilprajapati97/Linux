# Failure Modes, Debugging, and Performance

Early boot failures around `__cpu_setup` are usually severe because the kernel has not yet reached normal diagnostics infrastructure.

## Common failure classes

### Wrong bootloader state

Examples:

- MMU not actually off on entry
- stale cache or instruction state
- bad DTB pointer
- unsupported EL entry assumptions

### Wrong translation setup

Examples:

- unsupported granule size
- wrong physical address size field
- incompatible VA52 or LPA2 expectations
- wrong memory attributes

### Ordering bugs

Examples:

- missing or misunderstood barriers
- stale TLB state
- stale I-cache lines
- page-table visibility problems

### Platform-specific issues

Examples:

- CPU errata interaction
- firmware leaves unusual control state behind
- interconnect or coherency setup incomplete during early boot

## Debug strategy

When the platform dies near `bl __cpu_setup`, narrow the failure in this order:

1. confirm entry conditions from firmware
2. confirm idmap creation and memory visibility
3. confirm EL path through `init_kernel_el`
4. confirm feature register expectations
5. confirm TTBR roots and MMU enable sequence
6. confirm branch into the next stage after MMU-on

## Performance interpretation

Although `__cpu_setup` is not repeatedly executed in the steady state, its decisions can still affect overall system behavior by constraining:

- supported page-table model
- available address-space width
- hardware-managed access-flag behavior
- virtualization readiness
- predictability of secondary CPU bring-up

## System-design lesson

The best performance bugs to prevent are the ones that start as correctness bugs in early bring-up. Low-level initialization quality determines whether the rest of the kernel starts on a stable platform at all.
