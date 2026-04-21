# Linux Kernel Memory Allocation API Selection Guide

---

## Overview

Memory allocation in the Linux kernel is **not one-size-fits-all**.
Different APIs exist because of constraints like:

* Physical vs virtual contiguity
* Allocation size
* Performance requirements
* Execution context (sleep vs atomic)
* Hardware/DMA requirements

This guide explains:

* Which API to use
* When to use it
* Matching free APIs
* Decision flow

---

## Core Concepts

### Physical vs Virtual Memory

| Type     | Description                                      |
| -------- | ------------------------------------------------ |
| Physical | Actual RAM, contiguous in hardware               |
| Virtual  | Kernel mapping, may not be physically contiguous |

---

### Allocation Constraints

| Constraint  | Impact                             |
| ----------- | ---------------------------------- |
| Size        | kmalloc (small) vs vmalloc (large) |
| Contiguity  | Hardware may require physical      |
| Context     | GFP flags matter                   |
| Performance | kmalloc faster than vmalloc        |

---

## GFP Flags

| Flag         | Use Case                   |
| ------------ | -------------------------- |
| `GFP_KERNEL` | Normal context (can sleep) |
| `GFP_ATOMIC` | Interrupt/atomic context   |
| `GFP_DMA`    | DMA-capable memory         |

---

## Allocation API Summary

| API                  | Use Case           | Contiguity | Free API            |
| -------------------- | ------------------ | ---------- | ------------------- |
| `kmalloc`            | Small allocations  | Physical   | `kfree`             |
| `kzalloc`            | Zeroed memory      | Physical   | `kfree`             |
| `krealloc`           | Resize buffer      | Physical   | `kfree`             |
| `kvmalloc`           | Large-safe alloc   | Virtual    | `kvfree`            |
| `kvzalloc`           | Large + zeroed     | Virtual    | `kvfree`            |
| `vmalloc`            | Large memory       | Virtual    | `vfree`             |
| `vzalloc`            | Large + zeroed     | Virtual    | `vfree`             |
| `alloc_pages`        | Page-level control | Physical   | `__free_pages`      |
| `__get_free_pages`   | Pages + VA         | Physical   | `free_pages`        |
| `devm_kmalloc`       | Device-managed     | Physical   | Auto                |
| `dma_alloc_coherent` | DMA buffers        | Physical   | `dma_free_coherent` |

---

## Primary Decision Flow

```mermaid
flowchart TD
    A["Need kernel memory"] --> B{"Is this for DMA/device?"}

    B -->|Yes| C["dma_alloc_coherent"]
    C --> C1["dma_free_coherent"]

    B -->|No| D{"Device-managed lifecycle?"}

    D -->|Yes| E{"Zeroed?"}
    E -->|Yes| F["devm_kzalloc"]
    E -->|No| G["devm_kmalloc"]

    D -->|No| H{"Can sleep?"}

    H -->|Yes| I["GFP_KERNEL"]
    H -->|No| J["GFP_ATOMIC"]

    I --> K{"Need physical contiguity?"}
    J --> K

    K -->|Yes| L{"Small or pages?"}
    K -->|No| M{"Large allocation?"}

    L -->|Small| N["kmalloc / kzalloc"]
    L -->|Pages| O["alloc_pages / __get_free_pages"]

    M -->|Yes| P["kvmalloc / kvzalloc"]
    M -->|No| N

    P --> Q["kvfree"]
    N --> R["kfree"]
    O --> S["free_pages / __free_pages"]
```

---

## Detailed Allocation Flow

```mermaid
flowchart TD

    A["Start allocation"] --> B{"DMA required?"}

    B -->|Yes| DMA["dma_alloc_coherent"]
    DMA --> DMAFREE["dma_free_coherent"]

    B -->|No| C{"Device managed?"}

    C -->|Yes| DEV{"Zeroed?"}
    DEV -->|Yes| DEVZ["devm_kzalloc"]
    DEV -->|No| DEVN["devm_kmalloc"]

    C -->|No| D{"Context allows sleep?"}

    D -->|Yes| G1["GFP_KERNEL"]
    D -->|No| G2["GFP_ATOMIC"]

    G1 --> E{"Need physical contiguity?"}
    G2 --> E

    E -->|Yes| F{"Type of allocation"}
    E -->|No| V{"Large allocation?"}

    F -->|Small| KM["kmalloc"]
    F -->|Zeroed| KZ["kzalloc"]
    F -->|Resize| KR["krealloc"]

    KM --> KFREE["kfree"]
    KZ --> KFREE
    KR --> KFREE

    F -->|Pages| PG{"Page API"}
    PG --> AP["alloc_pages"]
    PG --> GFP["__get_free_pages"]

    AP --> APF["__free_pages"]
    GFP --> GPF["free_pages"]

    V -->|Yes| KV{"Prefer kvmalloc family?"}
    V -->|No| KM

    KV -->|Yes| KVZ{"Zeroed?"}
    KV -->|No| VM{"Use vmalloc family directly?"}

    KVZ -->|Yes| KVZALLOC["kvzalloc"]
    KVZ -->|No| KVM["kvmalloc"]

    KVM --> KVF["kvfree"]
    KVZALLOC --> KVF

    VM -->|Yes| VMZ{"Zeroed?"}
    VM -->|No| KVM
    VMZ -->|Yes| VZ["vzalloc"]
    VMZ -->|No| VMN["vmalloc"]

    VZ --> VF["vfree"]
    VMN --> VF
```

---

## Matching Free APIs

```mermaid
flowchart LR
    A["kmalloc / kzalloc / krealloc"] --> B["kfree"]
    C["kvmalloc / kvzalloc"] --> D["kvfree"]
    E["vmalloc / vzalloc"] --> F["vfree"]
    G["alloc_pages"] --> H["__free_pages"]
    I["__get_free_pages"] --> J["free_pages"]
    K["dma_alloc_coherent"] --> L["dma_free_coherent"]
    M["devm_kmalloc"] --> N["auto cleanup"]
```

---

## Common Mistakes

* ❌ Using `vmalloc` when physical contiguity is required
* ❌ Using `kfree` on `vmalloc` memory
* ❌ Using `GFP_KERNEL` in interrupt context
* ❌ Using `kmalloc` for large allocations (> few MB)
* ❌ Using `dma_alloc_coherent` unnecessarily

---

## Rules of Thumb

```text
Small + fast + contiguous      → kmalloc / kzalloc
Resize buffer                  → krealloc
Large but flexible             → kvmalloc / kvzalloc
Very large                     → vmalloc / vzalloc
Need page control              → alloc_pages
Driver lifecycle memory        → devm_kmalloc
Hardware DMA                   → dma_alloc_coherent
```

---

## Conclusion

There is no single “best” allocation API in the Linux kernel.

Each exists to solve a specific constraint combination:

- Performance -> `kmalloc`
- Size -> `vmalloc`
- Flexibility -> `kvmalloc`
- Control -> `alloc_pages`
- Hardware -> `dma_alloc_coherent`
- Lifecycle -> `devm_*`

Choosing the right API is about understanding requirements, not just syntax.
