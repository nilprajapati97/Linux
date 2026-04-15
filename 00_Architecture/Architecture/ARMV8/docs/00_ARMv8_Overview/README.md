# ARMv8 Architecture — Complete Overview

## 1. What is ARM?

ARM (Advanced RISC Machines) is a family of Reduced Instruction Set Computing (RISC) architectures
for computer processors. ARM does not manufacture chips — it **licenses** the architecture and
core designs to other companies (Apple, Qualcomm, Samsung, etc.) who build the actual silicon.

### RISC vs CISC

| Feature | RISC (ARM) | CISC (x86) |
|---------|-----------|------------|
| Instruction Length | Fixed-length | Variable-length |
| Memory Access | Load/Store architecture | Memory-to-memory ops |
| Registers | Many general-purpose registers | Fewer registers |
| Execution | Simple instructions, 1 cycle | Complex multi-cycle |
| Hardware | Hardware is simpler | Hardware is complex |
| Compiler | Compiler does more work | Hardware does more |
| Power | Lower power consumption | Higher performance/W |

---

## 2. Evolution of ARM Architecture

```mermaid
timeline
    title Evolution of ARM Architecture
    1985 : ARMv1 — First ARM processor (ARM1), 26-bit address space
    1986 : ARMv2 — Multiply & coprocessor instructions
    1992 : ARMv3 — 32-bit address space, MMU support
    1994 : ARMv4 — Thumb (16-bit) instruction set, ARM7TDMI
    1999 : ARMv5 — DSP extensions, improved interworking
    2002 : ARMv6 — SIMD, unaligned access, ARM11
    2004 : ARMv7 — Profiles introduced (A/R/M), NEON, LPAE
    2011 : ARMv8 — 64-bit architecture (AArch64) ◄ CURRENT
    2021 : ARMv9 — Security (CCA), SVE2, confidential compute
```

---

## 3. ARMv8 Architecture Profiles

ARMv8 continues the three profile tradition from ARMv7:

### ARMv8-A (Application Profile)
- **Target**: Smartphones, tablets, servers, laptops
- **Features**: Full virtual memory (MMU), multiple exception levels, virtualization, security
- **Cores**: Cortex-A53, A55, A57, A72, A73, A75, A76, A77, A78, X1, X2, X3, X4
- **This documentation focuses on ARMv8-A**

### ARMv8-R (Real-Time Profile)
- **Target**: Automotive, industrial, storage controllers
- **Features**: Low-latency interrupt handling, optional MMU/MPU, deterministic behavior

### ARMv8-M (Microcontroller Profile)
- **Target**: IoT devices, sensors, embedded controllers
- **Features**: Simpler architecture, optional TrustZone-M, low power

---

## 4. ARMv8-A Key Architectural Features

### 4.1 Dual Execution States

ARMv8 defines **two execution states**:

```mermaid
block-beta
  columns 2
  block:aarch64["AArch64 (64-bit state)"]:1
    columns 1
    a64["A64 instruction set"]
    gpr64["31 × 64-bit GPRs"]
    pc64["64-bit PC, SP, LR"]
    el64["4 Exception Levels"]
    sp64["4 Stack Pointers"]
  end
  block:aarch32["AArch32 (32-bit state)"]:1
    columns 1
    a32["A32 / T32 instruction sets"]
    gpr32["15 × 32-bit GPRs"]
    compat["Compatible with ARMv7"]
    banked["Banked Registers"]
    thumb["Thumb-2 support"]
  end

  style aarch64 fill:#1a73e8,color:#fff,stroke:#0d47a1
  style aarch32 fill:#e65100,color:#fff,stroke:#bf360c
  style a64 fill:#4285f4,color:#fff
  style gpr64 fill:#4285f4,color:#fff
  style pc64 fill:#4285f4,color:#fff
  style el64 fill:#4285f4,color:#fff
  style sp64 fill:#4285f4,color:#fff
  style a32 fill:#ff9800,color:#fff
  style gpr32 fill:#ff9800,color:#fff
  style compat fill:#ff9800,color:#fff
  style banked fill:#ff9800,color:#fff
  style thumb fill:#ff9800,color:#fff
```
> **Note:** Switching between states happens **ONLY** on exception entry/return.

### 4.2 Exception Levels (Privilege Model)

```mermaid
flowchart TB
    EL3["🔒 EL3 — Secure Monitor\nARM Trusted Firmware / TF-A\nManages Secure ↔ Non-Secure"]
    EL2["🖥️ EL2 — Hypervisor\nKVM / Xen\nHardware Virtualization"]
    EL1["⚙️ EL1 — OS Kernel\nLinux / Windows / RTOS\nPrivileged System Software"]
    EL0["📱 EL0 — User Applications\nUnprivileged Code"]

    EL3 --> EL2 --> EL1 --> EL0

    style EL3 fill:#b71c1c,color:#fff,stroke:#880e0e,stroke-width:2px
    style EL2 fill:#e65100,color:#fff,stroke:#bf360c,stroke-width:2px
    style EL1 fill:#1a73e8,color:#fff,stroke:#0d47a1,stroke-width:2px
    style EL0 fill:#2e7d32,color:#fff,stroke:#1b5e20,stroke-width:2px
```
> ⬆️ **Highest Privilege (EL3)** → ⬇️ **Lowest Privilege (EL0)**

### 4.3 System Components Overview

```mermaid
flowchart TB
    subgraph CLUSTER["CPU Cluster"]
        direction LR
        subgraph CORE0["CPU Core 0"]
            P0["Pipeline\nRegisters"]
            L1I0["L1 I-Cache"]
            L1D0["L1 D-Cache"]
            MMU0["MMU + TLB"]
        end
        subgraph CORE1["CPU Core 1"]
            P1["Pipeline\nRegisters"]
            L1I1["L1 I-Cache"]
            L1D1["L1 D-Cache"]
            MMU1["MMU + TLB"]
        end
        subgraph COREN["CPU Core N"]
            PN["Pipeline\nRegisters"]
            L1IN["L1 I-Cache"]
            L1DN["L1 D-Cache"]
            MMUN["MMU + TLB"]
        end
    end

    CORE0 --> L2
    CORE1 --> L2
    COREN --> L2
    CORE0 --> SCU
    CORE1 --> SCU
    COREN --> SCU

    L2["L2 Cache (Unified)"]
    SCU["Snoop Control Unit (SCU)"]
    L2 --> L3
    SCU --> L3
    L3["L3 Cache / System Level Cache"]
    L3 --> NOC
    NOC["Interconnect (NoC)\nCCI / CCN / CMN\nAMBA / CHI / AXI"]
    NOC --> GIC["GIC\n(Interrupt Controller)"]
    NOC --> SMMU["SMMU\n(IOMMU)"]
    NOC --> MEMCTRL["Memory Controller"]
    MEMCTRL --> DDR["DDR / LPDDR\nMain Memory"]

    style CLUSTER fill:#e3f2fd,stroke:#1565c0,stroke-width:2px,color:#0d47a1
    style CORE0 fill:#bbdefb,stroke:#1976d2,color:#0d47a1
    style CORE1 fill:#bbdefb,stroke:#1976d2,color:#0d47a1
    style COREN fill:#bbdefb,stroke:#1976d2,color:#0d47a1
    style P0 fill:#1a73e8,color:#fff
    style P1 fill:#1a73e8,color:#fff
    style PN fill:#1a73e8,color:#fff
    style L1I0 fill:#42a5f5,color:#fff
    style L1D0 fill:#42a5f5,color:#fff
    style MMU0 fill:#5c6bc0,color:#fff
    style L1I1 fill:#42a5f5,color:#fff
    style L1D1 fill:#42a5f5,color:#fff
    style MMU1 fill:#5c6bc0,color:#fff
    style L1IN fill:#42a5f5,color:#fff
    style L1DN fill:#42a5f5,color:#fff
    style MMUN fill:#5c6bc0,color:#fff
    style L2 fill:#7e57c2,color:#fff,stroke-width:2px
    style SCU fill:#ab47bc,color:#fff,stroke-width:2px
    style L3 fill:#6a1b9a,color:#fff,stroke-width:2px
    style NOC fill:#e65100,color:#fff,stroke-width:2px
    style GIC fill:#2e7d32,color:#fff
    style SMMU fill:#2e7d32,color:#fff
    style MEMCTRL fill:#f57f17,color:#fff
    style DDR fill:#bf360c,color:#fff,stroke-width:2px
```

---

## 5. ARMv8 Extensions (Versions)

ARMv8 has been extended over time:

| Version    | Year | Key Features                                              |
|------------|------|-----------------------------------------------------------|
| ARMv8.0-A  | 2011 | Base 64-bit architecture, AES/SHA crypto                  |
| ARMv8.1-A  | 2014 | Atomic instructions (LSE), VHE, PAN                      |
| ARMv8.2-A  | 2016 | FP16, Statistical profiling, SVE, RAS                     |
| ARMv8.3-A  | 2016 | Pointer authentication (PAC), nested virtualization       |
| ARMv8.4-A  | 2017 | Secure EL2, MPAM, Activity monitors                      |
| ARMv8.5-A  | 2018 | MTE (memory tagging), BTI (branch target identification)  |
| ARMv8.6-A  | 2019 | BFloat16, fine-grained traps, WFE enhancements            |
| ARMv8.7-A  | 2020 | PCIe/ACPI enhancements, WFI/WFE timeout                  |
| ARMv8.8-A  | 2021 | NMI support, HPMN0, TIDCP                                |
| ARMv8.9-A  | 2022 | Permission indirection, GCS (shadow stack)                |

---

## 6. Registers Quick Summary

### AArch64 Register File

**General Purpose Registers (31 × 64-bit):**

| 64-bit (Xn) | 32-bit (Wn) | Purpose |
|:---:|:---:|---|
| X0–X7 | W0–W7 | 🟦 Arguments & return values |
| X8 | W8 | 🟦 Indirect result location |
| X9–X15 | W9–W15 | 🟨 Temporary (caller-saved) |
| X16–X17 | W16–W17 | 🟧 Intra-procedure-call (IP0/IP1) |
| X18 | W18 | 🟧 Platform register |
| X19–X28 | W19–W28 | 🟩 Callee-saved |
| X29 | W29 | 🟪 Frame Pointer (FP) |
| X30 | W30 | 🟪 Link Register (LR) |
| SP | WSP | 🟥 Stack Pointer (per exception level) |
| PC | — | 🟥 Program Counter (not directly accessible) |
| XZR | WZR | ⬜ Zero Register (reads 0, writes discarded) |

> `Xn` = 64-bit view &nbsp;|&nbsp; `Wn` = lower 32-bit view of the same register

---

## 7. What Makes ARMv8 Special?

1. **Power Efficiency**: ARM achieves high performance-per-watt, enabling battery-powered devices
2. **Scalability**: Same architecture scales from embedded (Cortex-A35) to server (Neoverse N2/V2)
3. **Security Built-In**: TrustZone, PAC, MTE, BTI are architectural features, not bolted on
4. **Virtualization Native**: Hardware hypervisor support at EL2
5. **Backward Compatible**: AArch32 mode runs legacy ARMv7 code
6. **Ecosystem**: Massive software ecosystem (Linux, Android, iOS, Windows on ARM)

---

## Next Steps

Continue to **[01_CPU_Subsystem](../01_CPU_Subsystem/)** to learn about the core processing engine.
