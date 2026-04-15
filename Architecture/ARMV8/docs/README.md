# ARMv8 Architecture Documentation

## Complete Reference Guide — From Scratch

This documentation set provides an in-depth, beginner-friendly exploration of the ARMv8 architecture.
Every subsystem is explained from the ground up, including protocols, mechanisms, and internal workings.

---

## Table of Contents

| #  | Subsystem                        | Directory                          | Description                                                       |
|----|----------------------------------|------------------------------------|-------------------------------------------------------------------|
| 00 | ARMv8 Overview                   | [00_ARMv8_Overview](./00_ARMv8_Overview/)           | High-level introduction to ARMv8, history, and key concepts       |
| 01 | CPU Subsystem                    | [01_CPU_Subsystem](./01_CPU_Subsystem/)             | Execution states, exception levels, registers, pipeline, ISA      |
| 02 | Memory Subsystem                 | [02_Memory_Subsystem](./02_Memory_Subsystem/)       | Virtual memory, MMU, TLB, memory model, ordering rules            |
| 03 | Cache Subsystem                  | [03_Cache_Subsystem](./03_Cache_Subsystem/)         | Cache hierarchy, coherency protocols (MESI/MOESI), maintenance    |
| 04 | Interrupt Subsystem              | [04_Interrupt_Subsystem](./04_Interrupt_Subsystem/) | GIC architecture, exception handling, IRQ/FIQ/SError              |
| 05 | Security Subsystem               | [05_Security_Subsystem](./05_Security_Subsystem/)   | TrustZone, secure boot, cryptographic extensions                  |
| 06 | Virtualization Subsystem         | [06_Virtualization_Subsystem](./06_Virtualization_Subsystem/) | Hypervisor support, stage-2 translation, VHE              |
| 07 | Debug & Trace Subsystem          | [07_Debug_Trace_Subsystem](./07_Debug_Trace_Subsystem/)     | Debug architecture, CoreSight, ETM, breakpoints             |
| 08 | Interconnect & Bus Subsystem     | [08_Interconnect_Subsystem](./08_Interconnect_Subsystem/)   | AMBA, AXI, ACE, CHI protocols                               |
| 09 | Power Management                 | [09_Power_Management](./09_Power_Management/)       | DVFS, power states, big.LITTLE, DynamIQ                          |
| 10 | SIMD & Floating-Point            | [10_SIMD_FloatingPoint](./10_SIMD_FloatingPoint/)   | NEON, SVE/SVE2, floating-point unit                               |

---

## How to Use This Documentation

1. **Start with `00_ARMv8_Overview`** to understand the big picture.
2. **Follow each subsystem** in order (01 → 10) for a structured learning path.
3. Each subsystem directory has a **README.md** (overview) and numbered topic files for deep dives.
4. Diagrams are provided in ASCII art for portability.

## Key Terminology

| Term        | Meaning                                                                 |
|-------------|-------------------------------------------------------------------------|
| **AArch64** | The 64-bit execution state of ARMv8                                     |
| **AArch32** | The 32-bit execution state (backward compatible with ARMv7)             |
| **EL0–EL3** | Exception Levels (privilege levels, 0 = user, 3 = highest)             |
| **PE**      | Processing Element (a single CPU core)                                  |
| **ISA**     | Instruction Set Architecture                                            |
| **AMBA**    | Advanced Microcontroller Bus Architecture                               |
| **GIC**     | Generic Interrupt Controller                                            |
| **MMU**     | Memory Management Unit                                                  |
| **TLB**     | Translation Lookaside Buffer                                            |
| **SMMU**    | System Memory Management Unit (IOMMU equivalent)                        |

---

*This documentation is for educational purposes and covers the ARMv8-A application profile architecture.*
