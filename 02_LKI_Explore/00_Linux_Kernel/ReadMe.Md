<div align="center">

```
██╗     ██╗  ██╗██╗    ███████╗██╗  ██╗██████╗ ██╗      ██████╗ ██████╗ ███████╗
██║     ██║ ██╔╝██║    ██╔════╝╚██╗██╔╝██╔══██╗██║     ██╔═══██╗██╔══██╗██╔════╝
██║     █████╔╝ ██║    █████╗   ╚███╔╝ ██████╔╝██║     ██║   ██║██████╔╝█████╗
██║     ██╔═██╗ ██║    ██╔══╝   ██╔██╗ ██╔═══╝ ██║     ██║   ██║██╔══██╗██╔══╝
███████╗██║  ██╗██║    ███████╗██╔╝ ██╗██║     ███████╗╚██████╔╝██║  ██║███████╗
╚══════╝╚═╝  ╚═╝╚═╝    ╚══════╝╚═╝  ╚═╝╚═╝     ╚══════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝
```

# 🐧 Linux Kernel Internals — Deep Dive

> **A structured, interview-grade knowledge base covering Linux kernel internals from first principles to advanced system design.**
> Built for senior engineers, embedded/kernel developers, and anyone preparing for FAANG/Qualcomm/NVIDIA-level kernel interviews.

[![Linux Kernel](https://img.shields.io/badge/Linux-Kernel_Internals-FCC624?style=for-the-badge&logo=linux&logoColor=black)](https://kernel.org)
[![Topics](https://img.shields.io/badge/Topics-Memory_|_IRQ_|_Sync_|_Threads-blue?style=for-the-badge)](#-repository-map)
[![Level](https://img.shields.io/badge/Level-Senior_Engineer-red?style=for-the-badge)](#)
[![Interviews](https://img.shields.io/badge/Interview_Prep-NVIDIA_|_Qualcomm_|_Google-success?style=for-the-badge)](#-interview-deep-dives)

</div>

---

## 📚 Table of Contents

| # | Domain | Files | Description |
|---|--------|:-----:|-------------|
| 1 | [🧠 Memory Management](#-memory-management) | 26 | Virtual memory, allocators, paging, DMA, OOM |
| 2 | [⚡ Interrupt Handling](#-interrupt-handling) | 22 | IRQ subsystem, top/bottom halves, threaded IRQs |
| 3 | [🔒 Kernel Synchronization](#-kernel-synchronization) | 22 | Locks, RCU, barriers, deadlock, priority inversion |
| 4 | [🧵 Kernel Threads](#-kernel-threads) | 5 | kthreads, processes vs threads, interview prep |
| 5 | [🚀 Bringup](#-bringup) | 3 | Boot sequence, CPU design, kernel panic/oops |
| 6 | [🔌 Driver Development](#-driver-development) | — | Device driver foundations |
| 7 | [🔍 Explore](#-explore) | 1 | Deep-dive topics: spinlocks in interrupt context |

---

## 🧠 Memory Management

> Linux memory management spans from physical page frames all the way to user-space virtual address spaces. This section covers every layer.

<details>
<summary><b>📂 Click to expand all 26 topics</b></summary>

### Core Allocators
| File | Topic |
|------|-------|
| [01 — Virtual Memory & Paging](MemoryManagement/01_Virtual_Memory_and_Paging.md) | Page tables, TLB, virtual address translation |
| [02 — Slab Allocator / kmalloc / kmem_cache](MemoryManagement/02_Slab_Allocator_kmalloc_kmem_cache.md) | Object caching, SLAB/SLUB/SLOB |
| [03 — Buddy System & Page Allocator](MemoryManagement/03_Buddy_System_Page_Allocator.md) | Physical page allocation, fragmentation |
| [06 — vmalloc vs kmalloc](MemoryManagement/06_vmalloc_vs_kmalloc.md) | Contiguous vs virtually contiguous memory |
| [13 — GFP Flags & Allocation Context](MemoryManagement/13_GFP_Flags_and_Allocation_Context.md) | `GFP_KERNEL`, `GFP_ATOMIC`, allocation contexts |

### Mapping & DMA
| File | Topic |
|------|-------|
| [04 — Memory Mapping: mmap & ioremap](MemoryManagement/04_Memory_Mapping_mmap_ioremap.md) | File-backed and anonymous mappings |
| [05 — DMA Memory Management](MemoryManagement/05_DMA_Memory_Management.md) | Coherent/streaming DMA, IOMMU |

### Advanced Topics
| File | Topic |
|------|-------|
| [07 — OOM Killer & Memory Reclaim](MemoryManagement/07_OOM_Killer_and_Memory_Reclaim.md) | `oom_badness`, reclaim, swap |
| [08 — Kernel Memory Debugging](MemoryManagement/08_Kernel_Memory_Debugging.md) | KASAN, valgrind, memcheck, kmemleak |
| [09 — Memory Barriers & Cache Coherency](MemoryManagement/09_Memory_Barriers_and_Cache_Coherency.md) | `mb()`, `rmb()`, `wmb()`, MESI protocol |
| [10 — Process Address Space / mm_struct](MemoryManagement/10_Process_Address_Space_mm_struct.md) | VMA, `mm_struct`, `vm_area_struct` |
| [11 — Huge Pages & THP](MemoryManagement/11_Huge_Pages_and_THP.md) | 2MB/1GB pages, Transparent Huge Pages |
| [12 — Page Faults, COW & Demand Paging](MemoryManagement/12_Page_Faults_COW_Demand_Paging.md) | Minor/major faults, Copy-on-Write |
| [14 — Memory Zones: DMA / Normal / HighMem](MemoryManagement/14_Memory_Zones_DMA_Normal_HighMem.md) | Zone architecture, watermarks |
| [15 — Per-CPU Variables & Memory](MemoryManagement/15_Per_CPU_Variables_and_Memory.md) | `DEFINE_PER_CPU`, `this_cpu_*` |
| [23 — Page Table Walk Deep Dive](MemoryManagement/23_Page_Table_Walk_Complete_Deep_Dive.md) | PGD→PUD→PMD→PTE walk |
| [24 — Virtual-to-Physical Translation & Mapping](MemoryManagement/24_Virtual_to_Physical_Memory_Translation_and_Mapping.md) | `virt_to_phys`, page-frame numbers |
| [25 — Kernel/User Memory Split & Overcommit](MemoryManagement/25_Kernel_User_Memory_Split_and_Overcommit.md) | 3G/1G split, overcommit policy |
| [malloc Internals](MemoryManagement/Linux_malloc_Memory_Allocation_Internals.md) | glibc malloc, brk, mmap allocation path |

### 🏢 Interview Deep Dives
| File | Company |
|------|---------|
| [NVIDIA — System Design: Memory Management](MemoryManagement/16_NVIDIA_System_Design_Memory_Management.md) | NVIDIA |
| [NVIDIA — System Design Part 2](MemoryManagement/18_NVIDIA_System_Design_Part2.md) | NVIDIA |
| [NVIDIA — 15yr Deep Interview](MemoryManagement/20_NVIDIA_15yr_System_Design_Deep_Interview.md) | NVIDIA |
| [Qualcomm — System Design: Memory Management](MemoryManagement/17_Qualcomm_System_Design_Memory_Management.md) | Qualcomm |
| [Qualcomm — System Design Part 2](MemoryManagement/19_Qualcomm_System_Design_Part2.md) | Qualcomm |
| [Qualcomm — 15yr Deep Interview](MemoryManagement/21_Qualcomm_15yr_System_Design_Deep_Interview.md) | Qualcomm |
| [Google — 15yr Deep Interview](MemoryManagement/22_Google_15yr_System_Design_Deep_Interview.md) | Google |

</details>

---

## ⚡ Interrupt Handling

> Covers the entire Linux IRQ subsystem — from hardware signal to ISR execution — including advanced topics like threaded IRQs, NMIs, and IPI.

<details>
<summary><b>📂 Click to expand all 22 topics</b></summary>

### Fundamentals
| File | Topic |
|------|-------|
| [01 — Hardware vs Software Interrupts](Interrupt/01_Hardware_vs_Software_Interrupts.md) | IRQ vs exception, signal differences |
| [02 — Interrupt Descriptor Table](Interrupt/02_Interrupt_Descriptor_Table.md) | IDT structure, gate descriptors |
| [03 — Interrupt Context vs Process Context](Interrupt/03_Interrupt_Context_vs_Process_Context.md) | Stack, scheduling rules, constraints |
| [09 — IRQ API & Registration](Interrupt/09_IRQ_API_and_Registration.md) | `request_irq`, `free_irq`, `irq_desc` |
| [10 — Shared Interrupts](Interrupt/10_Shared_Interrupts.md) | `IRQF_SHARED`, chaining |

### Top Half / Bottom Half
| File | Topic |
|------|-------|
| [04 — Top Half & Bottom Half](Interrupt/04_Top_Half_and_Bottom_Half.md) | Design philosophy, latency tradeoff |
| [05 — Softirqs](Interrupt/05_Softirqs.md) | `NET_RX_SOFTIRQ`, `TASKLET_SOFTIRQ` |
| [06 — Tasklets](Interrupt/06_Tasklets.md) | `tasklet_schedule`, single-CPU serialization |
| [07 — Workqueues](Interrupt/07_Workqueues.md) | `schedule_work`, `alloc_workqueue` |
| [08 — Threaded IRQs](Interrupt/08_Threaded_IRQs.md) | `IRQF_ONESHOT`, RT kernels |
| [21 — Bottom Half Mechanisms Complete Guide](Interrupt/21_Bottom_Half_Mechanisms_Complete_Deep_Guide.md) | Comparison & decision flowchart |
| [Bottom Halves Overview](Interrupt/Linux_Bottom_Halves_Interrupt_Handling.md) | Consolidated reference |

### Advanced & SMP
| File | Topic |
|------|-------|
| [11 — Spinlocks in Interrupt Context](Interrupt/11_Spinlocks_in_Interrupt_Context.md) | `spin_lock_irqsave`, `irq_disable` |
| [12 — Interrupt Affinity & SMP](Interrupt/12_Interrupt_Affinity_SMP.md) | `/proc/irq/N/smp_affinity`, balancing |
| [13 — Edge vs Level Triggered](Interrupt/13_Edge_vs_Level_Triggered.md) | APIC modes, ACPI |
| [14 — IPI: Inter-Processor Interrupts](Interrupt/14_IPI_Inter_Processor_Interrupts.md) | TLB shootdowns, cross-CPU signaling |
| [15 — Device Tree Interrupt Mapping](Interrupt/15_Device_Tree_Interrupt_Mapping.md) | `interrupts` property, GIC |
| [16 — Interrupt Debugging via /proc](Interrupt/16_Interrupt_Debugging_proc.md) | `/proc/interrupts`, `irqbalance` |
| [17 — NMI: Non-Maskable Interrupts](Interrupt/17_NMI_Non_Maskable_Interrupts.md) | Watchdog, MCE, NMI handler |
| [18 — irq_domain Framework](Interrupt/18_irq_domain_Framework.md) | Virtual IRQ mapping, hierarchical domains |
| [19 — Interrupt Storms & Handling](Interrupt/19_Interrupt_Storms_Handling.md) | Mitigation, NAPI, coalescing |
| [20 — Full Interrupt Flow: ARM & x86](Interrupt/20_Full_Interrupt_Flow_ARM_x86.md) | End-to-end architecture comparison |

</details>

---

## 🔒 Kernel Synchronization

> Every primitive from spinlocks to RCU, with real-world deadlock scenarios, lock ordering rules, and the full synchronization decision matrix.

<details>
<summary><b>📂 Click to expand all 22 topics</b></summary>

### Primitives
| File | Topic |
|------|-------|
| [01 — Race Conditions & Critical Sections](Kernel_Synchronization/01_Race_Conditions_and_Critical_Sections.md) | Data races, TOCTOU |
| [02 — Atomic Operations](Kernel_Synchronization/02_Atomic_Operations.md) | `atomic_t`, `atomic64_t`, CAS |
| [03 — Spinlocks](Kernel_Synchronization/03_Spinlocks.md) | `spin_lock`, `spin_unlock`, ticket locks |
| [04 — Mutexes](Kernel_Synchronization/04_Mutexes.md) | `mutex_lock`, sleeping locks |
| [05 — Semaphores](Kernel_Synchronization/05_Semaphores.md) | Counting semaphores, `down`/`up` |
| [06 — RWLocks & SeqLocks](Kernel_Synchronization/06_RWLocks_and_SeqLocks.md) | Reader/writer fairness, seqcount |
| [07 — RCU (Read-Copy-Update)](Kernel_Synchronization/07_RCU.md) | Grace periods, `rcu_read_lock`, `call_rcu` |
| [08 — Completions](Kernel_Synchronization/08_Completions.md) | `wait_for_completion`, `complete` |
| [09 — Memory Barriers](Kernel_Synchronization/09_Memory_Barriers.md) | Compiler + CPU reordering |
| [10 — Per-CPU Variables](Kernel_Synchronization/10_Per_CPU_Variables.md) | Lock-free per-CPU access |
| [11 — Preemption Control](Kernel_Synchronization/11_Preemption_Control.md) | `preempt_disable`, preempt count |
| [12 — Waitqueues](Kernel_Synchronization/12_Waitqueues.md) | `wait_event`, `wake_up` |
| [17 — Spinlock Variants: BH & IRQ](Kernel_Synchronization/17_Spinlock_Variants_BH_IRQ.md) | `spin_lock_bh`, `spin_lock_irq` |
| [18 — Lock-Free Algorithms](Kernel_Synchronization/18_Lock_Free_Algorithms.md) | CAS loops, hazard pointers |

### Debugging & Design
| File | Topic |
|------|-------|
| [13 — Lockdep Debugging](Kernel_Synchronization/13_Lockdep_Debugging.md) | `CONFIG_LOCKDEP`, dependency graph |
| [14 — Priority Inversion & RT Mutexes](Kernel_Synchronization/14_Priority_Inversion_RT_Mutexes.md) | Priority inheritance, PI-futex |
| [15 — Lock Ordering & Deadlock](Kernel_Synchronization/15_Lock_Ordering_Deadlock.md) | Circular dependency, ABBA deadlock |
| [16 — Futex: User-Kernel Sync](Kernel_Synchronization/16_Futex_User_Kernel_Sync.md) | Fast path, kernel upcall |
| [19 — Sync in Interrupt Context](Kernel_Synchronization/19_Sync_in_Interrupt_Context.md) | Which primitives are safe where |
| [20 — Full Sync Decision Matrix](Kernel_Synchronization/20_Full_Sync_Decision_Matrix.md) | When to use what — reference chart |
| [Mutex vs Semaphore Guide](Kernel_Synchronization/Linux_Mutex_vs_Semaphore_Complete_Guide.md) | Complete comparison |

</details>

---

## 🧵 Kernel Threads

> Process/thread lifecycle, `kthread` API, and senior-level interview questions from NVIDIA, Qualcomm, and Google.

<details>
<summary><b>📂 Click to expand all 5 topics</b></summary>

| File | Topic |
|------|-------|
| [Process vs Thread Complete Guide](Kernel_Thread/Linux_Process_vs_Thread_Complete_Guide.md) | `fork`, `clone`, `task_struct`, namespaces |
| [NVIDIA — 15yr Kernel Thread Interview](Kernel_Thread/01_NVIDIA_15yr_Kernel_Thread_Deep_Interview.md) | NVIDIA senior-level interview Q&A |
| [Qualcomm — 15yr Kernel Thread Interview](Kernel_Thread/02_Qualcomm_15yr_Kernel_Thread_Deep_Interview.md) | Qualcomm senior-level interview Q&A |
| [Google — 15yr Kernel Thread Interview](Kernel_Thread/03_Google_15yr_Kernel_Thread_Deep_Interview.md) | Google senior-level interview Q&A |

</details>

---

## 🚀 Bringup

> Early boot, platform initialization, and post-mortem analysis of kernel panics and oopses.

<details>
<summary><b>📂 Click to expand all topics</b></summary>

| File | Topic |
|------|-------|
| [Designing a Single-Threaded CPU — Complete Guide](Bringup/02_Designing_Single_Threaded_CPU_Complete_Guide.md) | CPU microarchitecture, fetch-decode-execute |
| [Linux Kernel Panic vs Oops](Bringup/Linux_Kernel_Panic_vs_Oops.md) | Panic vs oops differences, decoding stack traces |

</details>

---

## 🔌 Driver Development

> Platform and character device drivers, device tree bindings, and kernel module infrastructure. *(Actively expanding)*

---

## 🔍 Explore

> Standalone deep dives on tricky, interview-favourite kernel topics.

| File | Topic |
|------|-------|
| [Why Spinlock in Interrupt (Not Mutex)](Explore/Why_Spinlock_in_Interrupt_Not_Mutex_Complete_Guide.md) | Sleeping-lock prohibition in atomic context |

---

## 🏢 Interview Deep Dives

Dedicated senior-engineer (10–15 yr) interview sessions covering system design and kernel internals questions asked at:

| Company | Domain | Link |
|---------|--------|------|
| 🟢 NVIDIA | Memory Management | [Part 1](MemoryManagement/16_NVIDIA_System_Design_Memory_Management.md) · [Part 2](MemoryManagement/18_NVIDIA_System_Design_Part2.md) · [15yr](MemoryManagement/20_NVIDIA_15yr_System_Design_Deep_Interview.md) |
| 🔵 Qualcomm | Memory Management | [Part 1](MemoryManagement/17_Qualcomm_System_Design_Memory_Management.md) · [Part 2](MemoryManagement/19_Qualcomm_System_Design_Part2.md) · [15yr](MemoryManagement/21_Qualcomm_15yr_System_Design_Deep_Interview.md) |
| 🔴 Google | Memory Management | [15yr](MemoryManagement/22_Google_15yr_System_Design_Deep_Interview.md) |
| 🟢 NVIDIA | Kernel Threads | [15yr](Kernel_Thread/01_NVIDIA_15yr_Kernel_Thread_Deep_Interview.md) |
| 🔵 Qualcomm | Kernel Threads | [15yr](Kernel_Thread/02_Qualcomm_15yr_Kernel_Thread_Deep_Interview.md) |
| 🔴 Google | Kernel Threads | [15yr](Kernel_Thread/03_Google_15yr_Kernel_Thread_Deep_Interview.md) |

---

## 🗺️ Repository Map

```
LKI_Explore/
├── 🧠 MemoryManagement/        # 26 files — allocators, paging, DMA, debugging
├── ⚡ Interrupt/               # 22 files — IRQ subsystem, bottom halves, SMP
├── 🔒 Kernel_Synchronization/  # 22 files — locks, RCU, barriers, lockdep
├── 🧵 Kernel_Thread/           #  5 files — kthreads, process model, interviews
├── 🚀 Bringup/                 #  3 files — boot, CPU design, panic/oops
├── 🔌 Driver/                  # (growing) — device drivers
└── 🔍 Explore/                 #  1 file  — deep-dive standalone topics
```

---

## 🧭 Learning Path

```
Beginner ──────────────────────────────────────────────────── Expert
   │                                                             │
   ▼                                                             ▼
Virtual Memory         Memory Zones          RCU Deep Dive
Buddy Allocator  ───►  Slab/SLUB       ───►  Page Table Walk
IRQ Basics             Top/Bottom Half        IRQ Domains
Spinlocks              Mutex / RWLock         Lock-Free Algorithms
Process vs Thread      kthread API            System Design Interviews
```

---

## 🤝 Contributing

1. Pick a topic from the roadmap or open an issue.
2. Follow the existing document structure (Overview → API → Internals → Interview Q&A).
3. Open a pull request with your addition.

---

<div align="center">

**⭐ Star this repo if it helped you crack a kernel interview!**

*Built with ❤️ for the Linux kernel community*

[![GitHub stars](https://img.shields.io/github/stars/nilprajapati97/LKI_Explore?style=social)](https://github.com/nilprajapati97/LKI_Explore)

</div>
