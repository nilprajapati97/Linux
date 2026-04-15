# Virtualization Subsystem

ARMv8 provides hardware virtualization support at **EL2** (Hypervisor Exception Level), enabling efficient virtual machine execution.

```
Virtualization Architecture:

  ┌──────────────────────────────────────────────────────────────┐
  │                        Hardware                               │
  │  ┌──────────────────────────────────────────────────────┐    │
  │  │  EL2: Hypervisor (KVM, Xen, Hafnium)                 │    │
  │  │  • Controls Stage-2 page tables                       │    │
  │  │  • Traps privileged guest operations                  │    │
  │  │  • Virtual interrupt injection                        │    │
  │  │  • Virtual timer management                           │    │
  │  └───────────────┬─────────────────┬─────────────────────┘    │
  │                  │                 │                           │
  │   ┌──────────────▼───┐  ┌─────────▼──────────┐              │
  │   │ VM 1 (Guest)     │  │ VM 2 (Guest)       │              │
  │   │                  │  │                     │              │
  │   │ EL1: Guest OS    │  │ EL1: Guest OS      │              │
  │   │     (Linux)      │  │     (Windows)      │              │
  │   │                  │  │                     │              │
  │   │ EL0: Guest Apps  │  │ EL0: Guest Apps    │              │
  │   └──────────────────┘  └─────────────────────┘              │
  │                                                               │
  │  Key: Guest OS thinks it's at EL1 (it is!) but its           │
  │       memory accesses go through Stage-2 translation         │
  │       and privileged operations can be trapped to EL2.       │
  └──────────────────────────────────────────────────────────────┘
```

## Documents

| # | Topic | File |
|---|-------|------|
| 1 | [Hypervisor Support (EL2)](./01_Hypervisor.md) | Trap & emulate, HCR_EL2, VHE |
| 2 | [Stage-2 Translation](./02_Stage2_Translation.md) | IPA→PA, VTTBR, VMID |

---

Back to [Main Index](../README.md)
