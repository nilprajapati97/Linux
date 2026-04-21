# Qualcomm Platform and Kernel Questions

## Q1. How would you approach Linux bring-up on a mobile SoC with complex firmware interaction?

### Answer

I would treat firmware interaction as part of the architecture contract, not as an implementation detail. The first priority is to confirm bootloader state, exception-level expectations, cache and MMU assumptions, and memory-description correctness. After that, I would validate power, clocks, interrupt routing, SCMI or vendor interfaces, and early console availability.

On Qualcomm-style platforms, sequencing and firmware coordination are often as important as the kernel code itself, so I would build a bring-up plan with checkpoints for each ownership handoff.

## Q2. What would you watch for in low-power and hotplug scenarios?

### Answer

I would watch whether secondary CPUs re-enter with the same architectural invariants assumed at initial boot. Reuse of low-level CPU setup logic is valuable because suspend, resume, and hotplug paths often fail when they diverge from the proven initial boot path.

## Q3. How would you discuss performance tuning in an interview?

### Answer

I would explain that performance tuning starts with correctness of the boot-time architecture baseline. After that, I would focus on scheduler behavior, idle states, memory latency, interconnect pressure, IOMMU cost, page-fault behavior, and driver initialization ordering. I would avoid claiming optimizations in low-level boot code unless measurement clearly shows that early boot itself is a meaningful part of the problem.

## Q4. What is a strong system-design answer for a Qualcomm-style role?

### Answer

A strong answer connects boot firmware, CPU initialization, power-management constraints, peripheral sequencing, and observability. It should show comfort with incomplete hardware visibility, firmware-owned resources, and the practical need to debug with narrow windows of evidence during early bring-up.
