# Boot Pipeline Mental Model

A useful way to reason about ARM64 early boot is to treat it as a staged control transfer between ownership domains.

## Ownership domains

1. firmware owns the machine first
2. Linux early assembly takes control of the CPU
3. Linux turns on a minimal translation regime
4. Linux constructs the normal kernel memory world
5. Linux enters generic kernel initialization

## Why __cpu_setup matters in that pipeline

`__cpu_setup` sits at the boundary between stage 2 and stage 3.

- before it, Linux has control but not yet active virtual memory
- after it, the CPU is configured to accept a safe MMU-on transition

## Pipeline model

```mermaid
flowchart LR
    A[Firmware state] --> B[Entry normalization]
    B --> C[Early idmap creation]
    C --> D[CPU translation setup]
    D --> E[MMU enable]
    E --> F[Real kernel mapping]
    F --> G[Normal kernel execution]
```

## Design insight

The kernel does not jump directly from firmware entry to the final memory layout because that would couple too many risks together:

- privilege-level normalization
- page-table creation
- translation-policy programming
- MMU activation
- relocation and final mapping

By separating these phases, Linux reduces the blast radius of low-level failures and makes the early boot design reusable across many SoCs and CPU variants.

## Bring-up intuition

When debugging platform boot issues, ask these questions in order:

1. Did firmware enter with valid state?
2. Did Linux build the idmap correctly?
3. Did `init_kernel_el` normalize EL state correctly?
4. Did `__cpu_setup` program the right translation policy?
5. Did `__enable_mmu` activate the MMU with valid TTBR roots?
6. Did the kernel survive the transition into the normal mapping?

That order mirrors the real dependency chain.
