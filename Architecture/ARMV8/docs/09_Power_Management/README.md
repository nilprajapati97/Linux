# Power Management

ARMv8 defines power management features at the architecture level, enabling aggressive power saving for mobile, embedded, and server platforms.

```
Power Management Layers:

  ┌──────────────────────────────────────────────────────────────┐
  │  Software (OS/Firmware)                                       │
  │  ┌────────────┐  ┌──────────┐  ┌──────────────────────┐     │
  │  │ CPUidle    │  │ CPUfreq  │  │ Runtime PM / devfreq │     │
  │  │ (idle      │  │ (frequency│  │ (peripheral power)   │     │
  │  │  states)   │  │  scaling) │  │                      │     │
  │  └─────┬──────┘  └────┬─────┘  └──────────┬───────────┘     │
  │        │              │                     │                  │
  │  ┌─────▼──────────────▼─────────────────────▼──────────┐     │
  │  │              PSCI (Power State Coordination          │     │
  │  │              Interface) — via SMC to ATF             │     │
  │  └─────────────────────────┬───────────────────────────┘     │
  │                            │                                   │
  │  Hardware                  │                                   │
  │  ┌─────────────────────────▼──────────────────────────────┐  │
  │  │  SoC Power Controller / PMIC                            │  │
  │  │  • Clock gating, power gating                           │  │
  │  │  • Voltage regulators                                   │  │
  │  │  • Retention RAM                                        │  │
  │  └────────────────────────────────────────────────────────┘  │
  └──────────────────────────────────────────────────────────────┘
```

## Documents

| # | Topic | File |
|---|-------|------|
| 1 | [DVFS & CPU Frequency](./01_DVFS.md) | Dynamic voltage/frequency scaling |
| 2 | [Power States](./02_Power_States.md) | Idle states, PSCI, WFI/WFE |

---

Back to [Main Index](../README.md)
