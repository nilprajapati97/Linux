<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:0d1117,50:1a1a2e,100:16213e&height=200&section=header&text=Linux%20Kernel%20Internals&fontSize=48&fontColor=00d4ff&fontAlignY=38&desc=Deep%20Dive%20into%20the%20Heart%20of%20the%20OS&descAlignY=58&descSize=20&descColor=7fdbff&animation=fadeIn" width="100%"/>

[![Typing SVG](https://readme-typing-svg.demolab.com?font=Fira+Code&size=22&pause=1000&color=00D4FF&center=true&vCenter=true&multiline=true&width=750&height=80&lines=Exploring+the+Linux+Kernel+%F0%9F%90%A7;Memory+Management+%7C+Process+Scheduling+%7C+Device+Drivers;Syscalls+%7C+VFS+%7C+Networking+Stack+%7C+IPC)](https://git.io/typing-svg)

</div>

---

## 🧠 About This Repository

> **LKI_Explore** is a deep-dive technical reference into **Linux Kernel Internals** — from boot sequences to scheduler algorithms, memory subsystems to device drivers. This is built for systems programmers, embedded engineers, and OS enthusiasts who want to go beyond the surface.

---

## 📚 Topics Covered

<details>
<summary><b>🚀 Kernel Boot & Initialization</b></summary>

- BIOS/UEFI → Bootloader → Kernel handoff
- `start_kernel()` walkthrough
- Early memory setup (`memblock`, paging)
- SMP initialization & CPU bring-up
- `initcalls` and `__init` sections

</details>

<details>
<summary><b>🧵 Process Management & Scheduling</b></summary>

- `task_struct` anatomy
- Process creation: `fork()`, `clone()`, `exec()`
- Completely Fair Scheduler (CFS) — `sched_entity`, `vruntime`
- Real-Time scheduling classes (SCHED_FIFO, SCHED_RR)
- Context switching: `switch_to()`, `schedule()`
- Wait queues, signals, and preemption

</details>

<details>
<summary><b>🗄️ Memory Management</b></summary>

- Physical memory: zones, nodes, `page` struct
- Buddy allocator & SLAB/SLUB caches
- Virtual memory: `vm_area_struct`, `mm_struct`
- Page tables: PGD → PUD → PMD → PTE
- Page fault handling & demand paging
- `mmap()`, anonymous vs file-backed mappings
- OOM Killer, memory compaction & reclaim
- Huge Pages & THP (Transparent Huge Pages)

</details>

<details>
<summary><b>📂 Virtual File System (VFS)</b></summary>

- VFS layer architecture
- `inode`, `dentry`, `file`, `super_block` objects
- `file_operations` and `inode_operations`
- Page cache & buffer cache
- `read()`/`write()` syscall path through VFS
- `procfs`, `sysfs`, `debugfs` internals

</details>

<details>
<summary><b>🔌 Device Drivers & I/O</b></summary>

- Driver model: `platform_device`, `platform_driver`
- Character and block device drivers
- Interrupt handling: IRQ, `request_irq()`, threaded IRQs
- DMA: coherent vs streaming mappings
- I2C, SPI, UART subsystems
- Device Tree (DT) and `of_match_table`
- `regmap` framework

</details>

<details>
<summary><b>🔒 Synchronization & Concurrency</b></summary>

- Spinlocks, mutexes, semaphores
- RCU (Read-Copy-Update) mechanism
- Atomic operations & memory barriers
- Per-CPU variables
- Lock-free data structures in the kernel
- Deadlock detection with lockdep

</details>

<details>
<summary><b>🌐 Networking Stack</b></summary>

- `sk_buff` (skb) anatomy
- NIC driver → protocol layers → socket
- TCP/IP stack walkthrough
- Netfilter hooks & iptables
- `socket()` syscall path
- Network namespaces

</details>

<details>
<summary><b>📞 System Calls & User–Kernel Interface</b></summary>

- Syscall entry mechanism (x86_64 `SYSCALL` instruction)
- `SYSCALL_DEFINE` macros
- `ioctl()` interface design
- `seccomp` and syscall filtering
- `ptrace` internals
- vDSO and vsyscall

</details>

<details>
<summary><b>🔧 Kernel Debugging & Tracing</b></summary>

- `printk` log levels & `dmesg`
- `kgdb` / `kdb` kernel debuggers
- `ftrace`, `perf`, `eBPF` tracing
- `kprobes` and `uprobes`
- KASAN for memory error detection
- `slub_debug`, `memcheck`

</details>

---

## 🛠️ Tech Stack & Tools

<div align="center">

![Linux](https://img.shields.io/badge/Linux_Kernel-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Assembly](https://img.shields.io/badge/Assembly-525252?style=for-the-badge&logo=assemblyscript&logoColor=white)
![GDB](https://img.shields.io/badge/GDB-A8B9CC?style=for-the-badge&logo=gnu&logoColor=black)
![QEMU](https://img.shields.io/badge/QEMU-FF6600?style=for-the-badge&logo=qemu&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=for-the-badge&logo=git&logoColor=white)
![Bash](https://img.shields.io/badge/Bash-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white)
![Vim](https://img.shields.io/badge/Vim-019733?style=for-the-badge&logo=vim&logoColor=white)
![VS Code](https://img.shields.io/badge/VSCode-007ACC?style=for-the-badge&logo=visual-studio-code&logoColor=white)

</div>

---

## 🗺️ Kernel Internals Mind Map

```
Linux Kernel
├── 🚀 Boot
│   ├── BIOS/UEFI
│   ├── GRUB/U-Boot
│   └── start_kernel()
├── 🧵 Process
│   ├── task_struct
│   ├── Scheduler (CFS / RT)
│   └── Context Switch
├── 🗄️ Memory
│   ├── Physical (Buddy / SLAB)
│   ├── Virtual (VMAs / Page Tables)
│   └── Swap / OOM
├── 📂 File System
│   ├── VFS Layer
│   ├── ext4 / xfs / btrfs
│   └── Page Cache
├── 🔌 Drivers
│   ├── Platform / PCI / USB
│   ├── IRQ / DMA
│   └── Device Tree
├── 🌐 Networking
│   ├── sk_buff
│   ├── TCP/IP Stack
│   └── Netfilter
└── 🔧 Debug
    ├── ftrace / eBPF
    ├── KASAN / kprobes
    └── QEMU + GDB
```

---

## 📖 Reference Resources

| Resource | Description |
|---|---|
| 📘 [Linux Kernel Development – R. Love](https://www.oreilly.com/library/view/linux-kernel-development/9780768696974/) | Classic kernel internals book |
| 📗 [Understanding the Linux Kernel – Bovet & Cesati](https://www.oreilly.com/library/view/understanding-the-linux/0596005652/) | Deep architectural reference |
| 📙 [Linux Device Drivers – Corbet et al.](https://lwn.net/Kernel/LDD3/) | Free PDF, driver writing guide |
| 🌐 [kernel.org](https://www.kernel.org/) | Official Linux kernel source |
| 🌐 [LWN.net](https://lwn.net/) | Kernel news and deep articles |
| 🌐 [Bootlin Elixir Cross-Reference](https://elixir.bootlin.com/linux/latest/source) | Browsable kernel source |
| 🌐 [Linux Kernel Map](https://makelinux.github.io/kernel/map/) | Interactive kernel subsystem map |

---

## 📊 Kernel Subsystem Cheat Sheet

| Subsystem | Key Structs | Key Functions |
|---|---|---|
| Process | `task_struct`, `mm_struct` | `do_fork()`, `schedule()`, `switch_to()` |
| Memory | `page`, `vm_area_struct` | `alloc_pages()`, `handle_mm_fault()` |
| VFS | `inode`, `dentry`, `file` | `vfs_read()`, `vfs_write()`, `do_sys_open()` |
| Networking | `sk_buff`, `socket`, `sock` | `ip_rcv()`, `tcp_sendmsg()` |
| Drivers | `platform_device`, `cdev` | `request_irq()`, `ioremap()` |
| Sync | `spinlock_t`, `mutex` | `spin_lock_irqsave()`, `rcu_read_lock()` |

---

## 🤝 Contributing

Contributions are welcome! If you have notes, code samples, or corrections:

1. Fork the repository
2. Create a feature branch: `git checkout -b topic/memory-management`
3. Add your content with clear explanations and references
4. Submit a Pull Request

---

<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&color=0:16213e,50:1a1a2e,100:0d1117&height=120&section=footer&animation=fadeIn" width="100%"/>

*"Those who understand the kernel understand the soul of the machine."*

![Profile Views](https://komarev.com/ghpvc/?username=nilprajapati97&color=00d4ff&style=flat-square&label=Profile+Views)

</div>
