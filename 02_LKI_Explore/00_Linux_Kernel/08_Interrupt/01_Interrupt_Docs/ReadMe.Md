# 🔴 Linux Kernel Interrupts — Complete Interview Guide

> Deep-dive into every interrupt topic asked in Linux Kernel / Embedded / Driver interviews.  
> Each file contains **colored Mermaid diagrams**, **code examples**, and **tough interview Q&A**.

---

## 📂 Topic Index

| # | Topic | File |
|---|-------|------|
| 01 | Hardware vs Software Interrupts | [01_Hardware_vs_Software_Interrupts.md](01_Hardware_vs_Software_Interrupts.md) |
| 02 | Interrupt Descriptor Table (IDT) | [02_Interrupt_Descriptor_Table.md](02_Interrupt_Descriptor_Table.md) |
| 03 | Interrupt Context vs Process Context | [03_Interrupt_Context_vs_Process_Context.md](03_Interrupt_Context_vs_Process_Context.md) |
| 04 | Top Half and Bottom Half Overview | [04_Top_Half_and_Bottom_Half.md](04_Top_Half_and_Bottom_Half.md) |
| 05 | Softirqs | [05_Softirqs.md](05_Softirqs.md) |
| 06 | Tasklets | [06_Tasklets.md](06_Tasklets.md) |
| 07 | Workqueues | [07_Workqueues.md](07_Workqueues.md) |
| 08 | Threaded IRQs | [08_Threaded_IRQs.md](08_Threaded_IRQs.md) |
| 09 | IRQ API and Registration | [09_IRQ_API_and_Registration.md](09_IRQ_API_and_Registration.md) |
| 10 | Shared Interrupts | [10_Shared_Interrupts.md](10_Shared_Interrupts.md) |
| 11 | Spinlocks in Interrupt Context | [11_Spinlocks_in_Interrupt_Context.md](11_Spinlocks_in_Interrupt_Context.md) |
| 12 | Interrupt Affinity and SMP | [12_Interrupt_Affinity_SMP.md](12_Interrupt_Affinity_SMP.md) |
| 13 | Edge-Triggered vs Level-Triggered | [13_Edge_vs_Level_Triggered.md](13_Edge_vs_Level_Triggered.md) |
| 14 | IPI — Inter-Processor Interrupts | [14_IPI_Inter_Processor_Interrupts.md](14_IPI_Inter_Processor_Interrupts.md) |
| 15 | Device Tree Interrupt Mapping (ARM) | [15_Device_Tree_Interrupt_Mapping.md](15_Device_Tree_Interrupt_Mapping.md) |
| 16 | Interrupt Debugging & /proc/interrupts | [16_Interrupt_Debugging_proc.md](16_Interrupt_Debugging_proc.md) |
| 17 | NMI — Non-Maskable Interrupts | [17_NMI_Non_Maskable_Interrupts.md](17_NMI_Non_Maskable_Interrupts.md) |
| 18 | irq_domain Framework | [18_irq_domain_Framework.md](18_irq_domain_Framework.md) |
| 19 | Interrupt Storms and Mitigation | [19_Interrupt_Storms_Handling.md](19_Interrupt_Storms_Handling.md) |
| 20 | Full Interrupt Flow — ARM & x86 | [20_Full_Interrupt_Flow_ARM_x86.md](20_Full_Interrupt_Flow_ARM_x86.md) |

---

## 🎯 How to Use

1. **Sequential Reading** — Topics are ordered from fundamentals → advanced
2. **Each file** has: Concept → Diagrams → Code → Tough Q&A
3. **Interview Prep** — Jump to the Q&A section at the bottom of each file
4. **Diagrams** — Use a Mermaid-compatible viewer (GitHub, VS Code extension, etc.)

---

## 🏢 Companies That Ask These Topics

| Company | Focus Areas |
|---------|-------------|
| **Qualcomm** | GIC, Device Tree, Threaded IRQs, SMP affinity |
| **NVIDIA** | Top/Bottom half, Workqueues, IRQ domain |
| **Intel** | IDT, APIC, NMI, x86 interrupt flow |
| **Samsung** | Shared IRQs, Tasklets, Edge/Level trigger |
| **MediaTek** | DT mapping, Softirqs, Interrupt storms |
| **Texas Instruments** | Full ARM interrupt flow, GIC configuration |
