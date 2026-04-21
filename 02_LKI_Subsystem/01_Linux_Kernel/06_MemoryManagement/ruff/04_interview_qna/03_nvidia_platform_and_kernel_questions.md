# NVIDIA Platform and Kernel Questions

## Q1. How would you design kernel bring-up for a heterogeneous SoC with accelerators?

### Answer

I would separate CPU bring-up correctness from accelerator enablement. The CPU complex must first reach a fully stable kernel environment with correct translation, interrupt routing, coherency assumptions, and per-CPU initialization. Only then should GPU, multimedia, or AI accelerators be brought online.

For NVIDIA-style platforms, I would focus on memory-sharing models, IOMMU configuration, coherent and non-coherent device behavior, boot dependencies across CPU and accelerator firmware, and strong instrumentation for early platform failures.

## Q2. Why is early CPU setup still important on accelerator-heavy systems?

### Answer

Because the CPU still establishes the control plane for everything else. If the CPU memory model, exception handling, or SMP state is unstable, every later subsystem inherits that instability. Accelerator complexity increases the importance of a correct base kernel environment rather than reducing it.

## Q3. What design tradeoff would you discuss for shared memory between CPU and accelerator blocks?

### Answer

I would discuss latency versus isolation, cacheability versus coherence complexity, and how page-table policy, IOMMU setup, and driver ownership boundaries affect both performance and debuggability. A strong answer should mention how early boot choices influence later memory-map consistency and DMA correctness.

## Q4. How would you answer a question about debugging intermittent early boot failures on a graphics SoC?

### Answer

I would start with the CPU boot chain because it is the root dependency. Then I would validate clocks, resets, interconnect, coherency setup, and firmware sequencing for dependent engines. If the failure happens before or near MMU-on, I would prioritize low-level CPU and page-table validation before suspecting higher-level driver code.
