# Security Subsystem

ARMv8 provides hardware-enforced security through **TrustZone**, **Secure Boot**, and **Cryptographic Extensions**.

```
Security Architecture Overview:

  ┌─────────────────────────────────────────────────────────────────┐
  │                        ARMv8 SoC                                │
  │                                                                  │
  │  ┌─────────────── Secure World ───────────────┐                │
  │  │                                              │                │
  │  │  EL3: Secure Monitor (ATF / TF-A)           │                │
  │  │    • World switch between Secure ↔ Normal   │                │
  │  │    • SMC call handler                        │                │
  │  │    • PSCI (CPU on/off/suspend)               │                │
  │  │                                              │                │
  │  │  S-EL1: Secure OS (OP-TEE, Trusty)          │                │
  │  │    • Trusted Applications (TAs)              │                │
  │  │    • Secure storage, key management          │                │
  │  │    • DRM, payment processing                 │                │
  │  │                                              │                │
  │  │  S-EL0: Secure Applications                  │                │
  │  │    • Run inside Secure OS                    │                │
  │  │                                              │                │
  │  └──────────────────────────────────────────────┘                │
  │                         ↕ SMC                                    │
  │  ┌─────────────── Normal World ───────────────┐                │
  │  │                                              │                │
  │  │  EL2: Hypervisor (optional)                  │                │
  │  │  EL1: OS Kernel (Linux, etc.)                │                │
  │  │  EL0: User Applications                      │                │
  │  │                                              │                │
  │  └──────────────────────────────────────────────┘                │
  │                                                                  │
  │  ┌─────────────── Bus Fabric ─────────────────┐                │
  │  │  TZASC (TrustZone Address Space Controller)  │                │
  │  │  TZPC  (TrustZone Protection Controller)     │                │
  │  │  TZMA  (TrustZone Memory Adapter)            │                │
  │  └──────────────────────────────────────────────┘                │
  └─────────────────────────────────────────────────────────────────┘
```

## Documents

| # | Topic | File |
|---|-------|------|
| 1 | [TrustZone Architecture](./01_TrustZone.md) | Hardware security extension details |
| 2 | [Secure Boot Chain](./02_Secure_Boot.md) | Boot flow, chain of trust, ATF |
| 3 | [Cryptographic Extensions](./03_Crypto_Extensions.md) | AES, SHA, CRC instructions |

---

Back to [Main Index](../README.md)
