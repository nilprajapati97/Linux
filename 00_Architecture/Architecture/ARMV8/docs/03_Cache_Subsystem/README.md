# Cache Subsystem — ARMv8-A

## Overview

The cache subsystem provides fast local copies of frequently accessed data and
instructions, bridging the speed gap between the CPU and main memory (DRAM).

```
Speed/Latency comparison:
  CPU Register:  ~0.3 ns  (1 cycle)
  L1 Cache:      ~1-2 ns  (3-5 cycles)
  L2 Cache:      ~3-7 ns  (10-20 cycles)
  L3 Cache:      ~10-20 ns (30-50 cycles)
  DRAM:          ~50-100 ns (100-300 cycles)
  SSD:           ~100 μs   (100,000 ns)

  ┌──────────────────────────────────────────────────────────────┐
  │                                                               │
  │   CPU Core                 Shared                            │
  │   ┌──────────┐            ┌──────────┐     ┌──────────┐     │
  │   │ L1 I$    │            │          │     │          │     │
  │   │ 32-64 KB │            │  L2 $    │     │  L3 $    │     │
  │   ├──────────┤  ──miss──▶ │ 256K-1MB │──▶  │ 2-32 MB  │──▶ DRAM
  │   │ L1 D$    │            │ (per core│     │ (shared) │     │
  │   │ 32-64 KB │            │  or pair)│     │          │     │
  │   └──────────┘            └──────────┘     └──────────┘     │
  │              ◀──faster──                ──slower──▶           │
  │              ◀──smaller──               ──larger──▶          │
  │                                                               │
  └──────────────────────────────────────────────────────────────┘
```

## Documents in This Section

| # | Document | Description |
|---|----------|-------------|
| 1 | [Cache Architecture](./01_Cache_Architecture.md) | Cache types, organization, policies |
| 2 | [Cache Coherency](./02_Cache_Coherency.md) | Multi-core coherency, snoop protocols |
| 3 | [MESI/MOESI Protocols](./03_MESI_MOESI_Protocols.md) | State machines, transitions, protocol details |
| 4 | [Cache Maintenance](./04_Cache_Maintenance.md) | Cache operations, cleaning, invalidation |
