# SIMD & Floating-Point Subsystem

ARMv8 includes **Advanced SIMD (NEON)** and **Floating-Point (FP)** as mandatory features in AArch64, plus the scalable vector extensions **SVE** and **SVE2**.

```
SIMD/FP Architecture:

  ┌──────────────────────────────────────────────────────────────┐
  │  Register File:                                               │
  │                                                                │
  │  32 vector registers: V0-V31                                  │
  │  Each is 128 bits wide (NEON) or up to 2048 bits (SVE)       │
  │                                                                │
  │  ┌─────────────────────────────────────────────────────────┐  │
  │  │                     V0 (128-bit)                         │  │
  │  │  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────────┐│  │
  │  │  │ B[15]│ ...  │ B[0] │      │      │      │          ││  │
  │  │  │ H[7] │ ...  │ H[0] │      │      │      │          ││  │
  │  │  │ S[3] │      │ S[1] │      │ S[0] │      │          ││  │
  │  │  │      │ D[1] │      │      │ D[0] │      │          ││  │
  │  │  │      │      │      │ Q[0] │      │      │          ││  │
  │  │  └──────┴──────┴──────┴──────┴──────┴──────┴──────────┘│  │
  │  └─────────────────────────────────────────────────────────┘  │
  │                                                                │
  │  Register views:                                               │
  │    Bn = 8-bit  byte (B0 = V0[7:0])                            │
  │    Hn = 16-bit half (H0 = V0[15:0])                           │
  │    Sn = 32-bit single-precision float (S0 = V0[31:0])        │
  │    Dn = 64-bit double-precision float (D0 = V0[63:0])        │
  │    Qn = 128-bit full register (Q0 = V0[127:0])               │
  │    Vn = 128-bit SIMD vector                                   │
  └──────────────────────────────────────────────────────────────┘
```

## Documents

| # | Topic | File |
|---|-------|------|
| 1 | [NEON, SVE & SVE2](./01_NEON_SVE.md) | SIMD instructions, vector processing, scalable vectors |

---

Back to [Main Index](../README.md)
