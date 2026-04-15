# Interconnect & Bus Subsystem

ARM defines the **AMBA** (Advanced Microcontroller Bus Architecture) family of bus protocols. These are the protocols that connect CPU cores, memory controllers, peripherals, and accelerators together on an SoC.

```
AMBA Protocol Evolution:

  AMBA 1 (1996): ASB (Advanced System Bus)
  AMBA 2 (1999): AHB (Advanced High-performance Bus)
  AMBA 3 (2003): AXI3 (Advanced eXtensible Interface)
                 APB3 (Advanced Peripheral Bus)
                 ATB  (Advanced Trace Bus)
  AMBA 4 (2010): AXI4, AXI4-Lite, AXI4-Stream
                 ACE  (AXI Coherency Extensions)
                 ACE-Lite
  AMBA 5 (2013): CHI  (Coherent Hub Interface)
  AMBA 5+ (2021): CHI Issue E, F

Typical SoC Interconnect:

  ┌──────┐ ┌──────┐ ┌──────┐ ┌──────┐
  │Core 0│ │Core 1│ │Core 2│ │Core 3│
  └──┬───┘ └──┬───┘ └──┬───┘ └──┬───┘
     │  ACE/CHI│        │        │
  ┌──▼────────▼────────▼────────▼──┐
  │     Coherent Interconnect       │
  │     (CCI/CCN/CMN/DSU)          │
  └──┬──────────┬──────────┬───────┘
     │ AXI      │ AXI      │ AXI
  ┌──▼────┐ ┌───▼───┐ ┌───▼───────┐
  │Memory │ │ GPU   │ │ NIC/Bridge│──► APB ──► Peripherals
  │Ctrl   │ │       │ │           │            (UART, SPI,
  │(DDR)  │ │       │ │           │             I2C, GPIO)
  └───────┘ └───────┘ └───────────┘
```

## Documents

| # | Topic | File |
|---|-------|------|
| 1 | [AMBA Bus Overview](./01_AMBA_Bus.md) | AHB, APB, protocol family |
| 2 | [AXI Protocol](./02_AXI_Protocol.md) | Channels, bursts, handshake, ordering |
| 3 | [ACE Protocol](./03_ACE_Protocol.md) | Coherency extensions, snoop channels |
| 4 | [CHI Protocol](./04_CHI_Protocol.md) | Coherent Hub Interface, mesh interconnect |

---

Back to [Main Index](../README.md)
