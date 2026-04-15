# Interrupt Subsystem — ARMv8-A

## Overview

The interrupt subsystem handles asynchronous events from hardware devices, timers,
and inter-processor interrupts. ARM uses the **GIC (Generic Interrupt Controller)**
as the standard interrupt controller architecture.

```
┌─────────────────────────────────────────────────────────────────────┐
│                    Interrupt Flow                                    │
│                                                                      │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐           │
│  │  UART    │  │  Timer   │  │  GPIO    │  │  PCIe    │  Devices  │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬─────┘           │
│       │              │              │              │                 │
│       └──────────────┴──────────────┴──────────────┘                 │
│                              │                                       │
│                    ┌─────────▼──────────┐                           │
│                    │    GIC             │  Generic Interrupt         │
│                    │  (Distributor +    │  Controller                │
│                    │   Redistributors + │                            │
│                    │   CPU Interfaces)  │                            │
│                    └───┬───────────┬────┘                           │
│                        │           │                                 │
│                        ▼           ▼                                 │
│                   ┌────────┐  ┌────────┐                            │
│                   │ Core 0 │  │ Core 1 │  IRQ/FIQ signals          │
│                   └────────┘  └────────┘                            │
└─────────────────────────────────────────────────────────────────────┘
```

## Documents in This Section

| # | Document | Description |
|---|----------|-------------|
| 1 | [GIC Architecture](./01_GIC_Architecture.md) | GIC versions, components, interrupt flow |
| 2 | [Exception Handling](./02_Exception_Handling.md) | How interrupts enter the CPU, handler flow |
| 3 | [Interrupt Types & Routing](./03_Interrupt_Types.md) | SGI, PPI, SPI, LPI, affinity routing |
