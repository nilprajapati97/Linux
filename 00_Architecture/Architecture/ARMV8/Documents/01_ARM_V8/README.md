# ARMv8 Architecture & CPU Subsystem — Complete Documentation Index

This repository provides a structured, end-to-end exploration of the **ARMv8 architecture**, covering everything from high-level concepts to deep internal CPU execution flows, coherency protocols, and boot sequences.

---

# 📘 1. ARMv8 Architecture Fundamentals

## Overview

* **0000_ARMv8_Architecture_Overview.md**

  * Introduction to ARMv8
  * Key architectural features
  * Evolution from ARMv7

## CPU Structure & Subsystems

* **0001_ARMv8_CPU_Block_Diagram.md**

  * High-level CPU block diagram
* **0002_ARMv8_CPU_Subsystem_Overview.md**

  * CPU subsystem components overview
* **0003_ARMv8_CPU_Internal_Block_Details.md**

  * Internal CPU blocks and their roles

---

# 🧠 2. CPU Subsystem Deep Dive

## Components & Architecture

* **0004_CPU_Subsystem_Component_Description.md**

  * Detailed explanation of each subsystem component
* **0005_CPU_Subsystem_Data_Flow.md**

  * Data movement within subsystem
* **0006_CPU_Subsystem_Architecture.md**

  * Structural design of CPU subsystem

## Cache Coherency

* **0007_CPU_Subsystem_MESI_Cache_Coherency.md**

  * MESI protocol explanation
* **0008_CPU_Subsystem_MOESI_Cache_Coherency.md**

  * MOESI protocol (extended MESI)

## Practice & Validation

* **0009_CpuSubsystem_Questions.md**

  * Interview / revision questions

---

# ⚙️ 3. CPU Core Architecture

* **0010_CPU_Core_Architecture_Details.md**

  * Core-level architecture
* **0011_CpuMainSubsystem.md**

  * Integration of cores into main subsystem

---

# 🔗 4. Interconnect & Multi-Cluster Communication

* **0012_ARMv8_Snoop_Based_Coherency_Flow.md**

  * Snoop-based coherency mechanism
* **0015_Multi_Cluster_CHI_Interconnect_Flow.md**

  * ARM CHI protocol flow
* **0015_MultiClusterCHIFlow.md**

  * Sequence diagrams for CHI
* **0016_Multi_Cluster_Communication_Flow.md**

  * Communication across clusters

---

# 🔄 5. CPU Execution Pipeline & Flows

## Core Execution Flow

* **0017_CPU_Core_Pipeline_Execution_Flow.md**

  * End-to-end pipeline stages

## Instruction Lifecycle

* **0018_Instruction_Fetch_Decode_Flow.md**

  * Fetch & decode stages
* **0019_Instruction_Execute_Writeback_Flow.md**

  * Execution & writeback stages

## Advanced Execution

* **0020_Branch_Prediction_Execution_Flow.md**

  * Branch prediction techniques

---

# ⚡ 6. System-Level Flows

## Interrupts & DMA

* **0021_GIC_Interrupt_Handling_Sequence.md**

  * Interrupt handling via GIC
* **0022_DMA_Data_Transfer_Flow.md**

  * DMA transaction flow

## End-to-End Transactions

* **0023_Single_Core_End_To_End_Transaction_Flow.md**
* **0025_Multi_Core_End_To_End_Transaction_Flow.md**

---

# 🔐 7. Boot & Security Flows

## Secure Boot

* **0024_ARMv8_Secure_Boot_Sequence_Flow.md**

  * Secure boot architecture

## Boot Execution States

* **0100_ARMv8_AArch32_AArch64_Execution_States.md**

  * AArch32 vs AArch64

## Register Model

* **0101_AArch64_Register_Model_And_Features.md**

  * Register layout and features

---

# 🚀 8. Boot Flow (Detailed Sequence)

## High-Level Boot

* **0102_ARMv8_Booting_Flow.Md**

  * Complete boot overview

## BootROM & Initial Execution

* **0103_ARMV8_PrimaryCore_BootROM.Md**

  * Primary core startup
* **0104_Primary core → BootROM.Md**

  * Transition to BootROM

## Bootloader Stages

* **0105_BootROM → Load BL1.MD**

  * BootROM loads BL1
* **0106_BL1_BL2.Md**

  * BL1 and BL2 stages
* **0106_ARMv8_EndToEnd_BootFlow_PC_BootRoam_BL1_BL2_BL3_Bootloader.Md**

  * Full boot chain (PC → BootROM → BL1 → BL2 → BL3 → OS)

---

# 🧩 9. Key Concepts Covered

### Architecture

* ARMv8 design principles
* AArch32 vs AArch64 execution

### CPU Microarchitecture

* Pipelines
* Instruction lifecycle
* Branch prediction

### Memory System

* Cache hierarchy
* MESI / MOESI coherency

### Interconnect

* CHI protocol
* Multi-cluster communication

### System Features

* Interrupt handling (GIC)
* DMA transfers

### Boot & Security

* Secure boot chain
* Bootloader stages (BL1, BL2, BL3)

---

# 📈 10. Learning Path Recommendation

1. Start with:

   * 0000 → 0003 (Basics)
2. Move to:

   * 0004 → 0008 (Subsystem + coherency)
3. Then:

   * 0010 → 0020 (Core + execution flows)
4. Follow with:

   * 0021 → 0025 (System flows)
5. Finish with:

   * 0100 → 0106 (Boot & architecture states)

---

# 🎯 11. Purpose of This Repository

This documentation is designed for:

* SoC / Embedded engineers
* Firmware developers
* Computer architecture learners
* Interview preparation (ARM, CPU design roles)

---

# ✅ 12. Summary

This repository provides a **complete ARMv8 journey**, covering:

* Architecture → Microarchitecture → Execution → System → Boot

It bridges **concepts + real hardware flows**, making it useful for both:

* Learning
* Practical system design understanding

---

If you want, I can also:

* Turn this into a **GitHub README with badges & diagrams**
* Add **visual architecture diagrams**
* Or create a **study roadmap with timelines**
