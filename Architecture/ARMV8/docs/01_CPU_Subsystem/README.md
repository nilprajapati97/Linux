# CPU Subsystem — ARMv8-A

## Overview

The CPU subsystem is the heart of the ARMv8-A architecture. It encompasses the processing
elements (PEs) that execute instructions, manage privilege levels, handle exceptions,
and coordinate with the rest of the SoC.

```mermaid
flowchart TB
    subgraph CORE["CPU Core"]
        direction TB
        subgraph FETCH["Instruction Fetch"]
            direction LR
            BP["Branch\nPredictor"] --> IFU["Instruction\nFetch Unit"]
            L1I["L1 I-Cache\n(32-64 KB)"] --> IFU
        end
        subgraph DECODE["Decode & Rename"]
            direction LR
            IDEC["Instruction\nDecode"] --> RREN["Register\nRename"] --> UOQ["Micro-Op\nQueue"]
        end
        subgraph EXEC["Execution (Out-of-Order)"]
            direction LR
            ALU0["ALU 0\n(Int)"] 
            ALU1["ALU 1\n(Int)"]
            MUL["MUL\nDIV"]
            FP["FP /\nNEON"]
            LSU["Load /\nStore"]
        end
        subgraph RETIRE["Retire / Commit"]
            ROB["Reorder Buffer (ROB)\nIn-order commit"]
        end
        FETCH --> DECODE --> EXEC --> RETIRE
        L1D["L1 D-Cache\n(32-64 KB)"]
        MMU["MMU\n+ TLB"]
        SYSREG["System Regs\n(EL0-EL3)"]
    end

    style CORE fill:#e3f2fd,stroke:#1565c0,stroke-width:2px,color:#0d47a1
    style FETCH fill:#bbdefb,stroke:#1976d2,color:#0d47a1
    style DECODE fill:#c8e6c9,stroke:#388e3c,color:#1b5e20
    style EXEC fill:#fff3e0,stroke:#e65100,color:#bf360c
    style RETIRE fill:#f3e5f5,stroke:#7b1fa2,color:#4a148c
    style BP fill:#1a73e8,color:#fff
    style IFU fill:#1a73e8,color:#fff
    style L1I fill:#42a5f5,color:#fff
    style IDEC fill:#43a047,color:#fff
    style RREN fill:#43a047,color:#fff
    style UOQ fill:#43a047,color:#fff
    style ALU0 fill:#e65100,color:#fff
    style ALU1 fill:#e65100,color:#fff
    style MUL fill:#e65100,color:#fff
    style FP fill:#ff6f00,color:#fff
    style LSU fill:#ff6f00,color:#fff
    style ROB fill:#7b1fa2,color:#fff
    style L1D fill:#42a5f5,color:#fff
    style MMU fill:#5c6bc0,color:#fff
    style SYSREG fill:#5c6bc0,color:#fff
```

## Documents in This Section

| # | Document | Description |
|---|----------|-------------|
| 1 | [Execution States](./01_Execution_States.md) | AArch64 vs AArch32, state transitions |
| 2 | [Exception Levels](./02_Exception_Levels.md) | EL0–EL3, privilege model, routing |
| 3 | [Registers](./03_Registers.md) | GPRs, system registers, special registers |
| 4 | [Instruction Set](./04_Instruction_Set.md) | A64 ISA, encoding, instruction categories |
| 5 | [Pipeline Architecture](./05_Pipeline.md) | In-order vs out-of-order, pipeline stages |
| 6 | [Branch Prediction](./06_Branch_Prediction.md) | BHT, BTB, RAS, speculative execution |

---

## Key Concepts

### What is a Processing Element (PE)?

A **Processing Element** is ARM's term for a CPU core — the hardware unit that fetches,
decodes, and executes instructions. A multi-core SoC contains multiple PEs, each with
its own register file, pipeline, L1 caches, and MMU.

### Microarchitecture vs Architecture

- **Architecture** (ISA): Defines WHAT the CPU can do — registers, instructions, behavior
- **Microarchitecture**: Defines HOW the CPU implements it — pipeline depth, cache sizes, etc.

ARMv8 is the **architecture**. Cortex-A53, Cortex-A72, Cortex-A78 are different
**microarchitectures** that implement ARMv8.

```mermaid
flowchart TD
    ARCH["ARMv8-A Architecture\n(the 'rules')"] --> A53["Cortex-A53\nIn-order · Low power"]
    ARCH --> A72["Cortex-A72\nOoO, 3-wide · Mid-range"]
    ARCH --> A78["Cortex-A78\nOoO, 4-wide · High perf"]
    ARCH --> N2["Neoverse N2\nServer · Data center"]

    style ARCH fill:#1a73e8,color:#fff,stroke:#0d47a1,stroke-width:2px
    style A53 fill:#2e7d32,color:#fff
    style A72 fill:#e65100,color:#fff
    style A78 fill:#b71c1c,color:#fff
    style N2 fill:#6a1b9a,color:#fff
```
