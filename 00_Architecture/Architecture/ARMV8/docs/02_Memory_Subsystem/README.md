# Memory Subsystem — ARMv8-A

## Overview

The memory subsystem manages how the CPU accesses memory — from virtual address
translation to physical memory access, including the MMU, TLB, and memory ordering.

```
┌──────────────────────────────────────────────────────────────────┐
│                    Memory Subsystem                               │
│                                                                    │
│   CPU Core                                                        │
│   ┌──────────────────────────┐                                   │
│   │  Virtual Address (VA)    │                                   │
│   │  (from load/store insn)  │                                   │
│   └────────────┬─────────────┘                                   │
│                │                                                  │
│   ┌────────────▼─────────────┐                                   │
│   │         TLB              │  Translation Lookaside Buffer     │
│   │  (VA → PA cache)         │  Fast lookup of recent translations│
│   └────┬──────────────┬──────┘                                   │
│        │ HIT          │ MISS                                     │
│        │              ▼                                           │
│        │  ┌───────────────────┐                                  │
│        │  │  MMU Table Walker │  Walks page tables in memory     │
│        │  │  (Hardware)       │                                  │
│        │  └────────┬──────────┘                                  │
│        │           │                                              │
│        ▼           ▼                                              │
│   ┌────────────────────────┐                                     │
│   │  Physical Address (PA) │                                     │
│   └────────────┬───────────┘                                     │
│                │                                                  │
│   ┌────────────▼───────────┐                                     │
│   │  Cache Hierarchy       │  L1D → L2 → L3                     │
│   └────────────┬───────────┘                                     │
│                │                                                  │
│   ┌────────────▼───────────┐                                     │
│   │  Interconnect → DRAM   │                                     │
│   └────────────────────────┘                                     │
└──────────────────────────────────────────────────────────────────┘
```

## Documents in This Section

| # | Document | Description |
|---|----------|-------------|
| 1 | [Memory Model](./01_Memory_Model.md) | ARM memory model, types, attributes |
| 2 | [Virtual Memory & Address Translation](./02_Virtual_Memory.md) | VA→PA, page tables, granules |
| 3 | [MMU — Memory Management Unit](./03_MMU.md) | MMU architecture, configuration |
| 4 | [TLB — Translation Lookaside Buffer](./04_TLB.md) | TLB structure, maintenance |
| 5 | [Memory Ordering & Barriers](./05_Memory_Ordering.md) | Weak ordering, barriers, acquire/release |
