# General Linux Kernel System-Design Questions

## Q1. Why does the kernel separate early CPU setup from the actual MMU enable step?

### Answer

This separation reduces risk and makes the state transition auditable. Early CPU setup programs translation policy such as `TCR_EL1`, `MAIR_EL1`, and optional feature-dependent controls. The MMU enable step then becomes a narrow commit point that loads TTBR roots and sets `SCTLR_EL1.M`.

Architecturally, this is safer because page tables, control registers, and activation order are tightly interdependent. From a design point of view, separating preparation from activation improves reuse, makes failure localization easier, and keeps the most dangerous transition small and deterministic.

## Q2. How would you debug a platform that hangs right after MMU enable?

### Answer

I would narrow it to five buckets:

1. wrong firmware entry contract
2. incorrect idmap or page-table visibility
3. wrong translation-control settings like granule or address width
4. stale TLB or I-cache behavior due to ordering mistakes
5. exception-level or privilege-state mismatch

I would then instrument the last safe points before and after `__enable_mmu`, verify the feature registers read by the CPU, confirm the TTBR roots, and ensure the code immediately after MMU-on is mapped by the active translation regime.

## Q3. What makes early-boot code harder than ordinary kernel code?

### Answer

Early boot runs with almost none of the services developers normally rely on. There is limited stack usage, minimal diagnostics, no scheduler, incomplete memory management, and very tight ordering requirements around architectural state. Bugs are usually catastrophic and can fail silently.

That is why good early-boot design uses minimal interfaces, staged activation, and carefully documented invariants.

## Q4. How would you explain TTBR0 and TTBR1 to an interviewer?

### Answer

At EL1 on ARM64, the CPU can use two translation-table base registers to cover different virtual address regions. Linux leverages that split so the lower-address side can temporarily host an identity map during transition, while the higher-address side hosts kernel mappings. This supports a safe bridge from physical boot execution to fully translated kernel execution.

## Q5. What is the design lesson from reusing __cpu_setup on secondary CPUs?

### Answer

Per-CPU architectural consistency matters more than one-time primary boot convenience. Reusing the same low-level setup path keeps translation policy, feature handling, and errata workarounds aligned across all CPUs, which is critical for SMP correctness and future scalability.
