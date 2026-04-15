# ARMv8 Architecture — Interview Questions & Answers

## For 15+ Years Experienced Professionals

This directory contains **deep, expert-level** questions and answers covering every ARMv8 subsystem. Each answer is explained **from scratch** — building up from fundamentals to advanced details, as expected in senior architect/principal engineer interviews.

---

## Question Banks by Subsystem

| # | Topic | File | Questions |
|---|-------|------|-----------|
| 1 | [General Architecture](./01_General_Architecture_QA.md) | ARMv8 fundamentals, profiles, execution states, exception levels | 20 |
| 2 | [CPU Subsystem](./02_CPU_Subsystem_QA.md) | Pipeline, registers, instruction set, branch prediction, OoO | 20 |
| 3 | [Memory Subsystem](./03_Memory_Subsystem_QA.md) | MMU, page tables, TLB, memory model, ordering, barriers | 20 |
| 4 | [Cache Subsystem](./04_Cache_Subsystem_QA.md) | Cache hierarchy, coherency, MESI/MOESI, maintenance, PoC/PoU | 20 |
| 5 | [Interrupt Subsystem](./05_Interrupt_Subsystem_QA.md) | GIC, SGI/PPI/SPI/LPI, exception handling, ITS, priority | 20 |
| 6 | [Security Subsystem](./06_Security_Subsystem_QA.md) | TrustZone, Secure Boot, PAC, MTE, RME, crypto extensions | 20 |
| 7 | [Virtualization](./07_Virtualization_QA.md) | EL2, Stage-2, VHE, SMMU, nested virt, live migration | 20 |
| 8 | [Debug & Trace](./08_Debug_Trace_QA.md) | Breakpoints, watchpoints, PMU, ETM, CoreSight, SPE | 20 |
| 9 | [Interconnect & Bus](./09_Interconnect_QA.md) | AMBA, AXI, ACE, CHI, mesh topology, snoop filter | 20 |
| 10 | [Power Management](./10_Power_Management_QA.md) | PSCI, DVFS, WFI/WFE, idle states, power domains | 15 |
| 11 | [SIMD & Floating Point](./11_SIMD_FP_QA.md) | NEON, SVE/SVE2, SME, FP16/BF16, ML extensions | 15 |

**Total: ~210 Questions**

---

## How to Use

- **Interview Prep**: Read the question first, try to answer, then check.
- **Self-Assessment**: Cover the answer and score yourself.
- **Knowledge Gaps**: If an answer surprises you, refer to the corresponding subsystem docs in `../` for deeper context.

---

## Difficulty Levels

Each question is tagged:
- **[L1]** — Fundamental (every ARM engineer should know)
- **[L2]** — Intermediate (expected at 10+ years)
- **[L3]** — Advanced (differentiator at 15+ years, architect-level)

---

Back to [Main Documentation Index](../README.md)
