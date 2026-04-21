# Exception Levels, Virtualization, and KVM Context

To understand early ARM64 boot well, you need to separate exception-level management from memory-translation management.

## Why EL handling is separate from __cpu_setup

`init_kernel_el` answers the question:

- In what privilege environment is Linux entering and continuing?

`__cpu_setup` answers a different question:

- How should EL1 stage-1 translation be configured before the MMU is turned on?

That separation is clean and intentional.

## Why EL2 matters

If Linux enters at EL2, it may later take advantage of virtualization capabilities and VHE-related behavior. Early code must therefore:

- avoid inheriting arbitrary EL2 state from firmware
- install a known-safe EL2 baseline
- prepare for later decisions about finalizing EL2 usage

## Why this matters for KVM design

KVM on ARM64 depends on the platform entering a coherent privilege model. The early boot code makes sure that later virtualization logic is built on a stable base instead of firmware leftovers.

## Design lesson

A robust architecture separates:

- privilege normalization
- translation setup
- feature finalization
- high-level subsystem enablement

That is exactly what the ARM64 kernel does here.

## Interview angle

If asked why Linux does not merge all early boot logic into one function, a strong answer is:

Because privilege state, translation state, and higher-level kernel initialization have different correctness constraints, different failure modes, and different reuse boundaries.
