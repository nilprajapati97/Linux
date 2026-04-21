# SMP, Secondary CPU Bring-up, and Scalability

The presence of `bl __cpu_setup` in both primary and secondary boot paths tells you something important about ARM64 kernel design.

## Core idea

Every CPU must enter the kernel with a consistent architectural baseline before it can safely execute translated kernel code.

That is why secondaries do not skip low-level CPU setup even though the primary CPU already booted the system.

## Secondary CPU path summary

A secondary CPU:

- arrives through a holding pen or direct secondary entry
- gets EL state normalized
- may validate VA52 capability if configured
- executes `__cpu_setup`
- enables the MMU using the shared kernel mappings
- enters `secondary_start_kernel`

## Why reuse matters

Using the same setup logic for all CPUs helps guarantee:

- uniform translation-control policy
- consistent feature handling
- consistent errata workarounds
- predictable behavior under SMP stress and hotplug scenarios

## Scalability perspective

A system design that depends on one special boot CPU path and many loosely aligned secondary paths becomes fragile as core counts increase. Reusing `__cpu_setup` reduces drift between CPUs.

## Performance angle

The function itself is not a throughput hot path, but its correctness shapes performance later because it determines:

- translation granule selection compatibility
- access-flag behavior
- address-width handling
- the stability of the early mapping transition

A broken early translation setup can manifest later as boot instability, silent data issues, or platform-specific performance anomalies.
