# ARM64 __cpu_setup Documentation Set

This learning set explains what happens when the ARM64 Linux kernel executes `bl __cpu_setup` during early boot, why that branch matters, how the processor behaves before and after it, and how the kernel transitions from firmware-owned machine state into normal kernel execution.

The content is organized from conceptual flow to code walkthrough to system-design reasoning and interview preparation.

## Learning path

1. [01_boot_flow/README.md](01_boot_flow/README.md)
2. [02_code_walkthrough/README.md](02_code_walkthrough/README.md)
3. [03_deep_understanding/README.md](03_deep_understanding/README.md)
4. [04_interview_qna/README.md](04_interview_qna/README.md)

## Core question answered by this set

When `primary_entry` in `arch/arm64/kernel/head.S` executes `bl __cpu_setup`, the kernel is still in the early boot phase:

- the MMU is still off
- Linux is still executing from identity-mapped boot code
- the kernel has not yet entered `start_kernel()`
- the CPU is about to be programmed with translation and memory-attribute state needed for turning on the MMU

`__cpu_setup` prepares the processor for virtual memory but does not enable the MMU by itself. It builds the register state that `__enable_mmu` consumes immediately afterward.

## Main source files behind these notes

- `arch/arm64/kernel/head.S`
- `arch/arm64/mm/proc.S`
- `arch/arm64/include/asm/assembler.h`
- `arch/arm64/include/asm/sysreg.h`
- `arch/arm64/include/asm/kernel-pgtable.h`
- `arch/arm64/kernel/pi/map_range.c`
- `arch/arm64/kernel/pi/map_kernel.c`
- `Documentation/arch/arm64/booting.rst`
- `Documentation/arch/arm64/memory.rst`

## Recommended reading order

Start with the boot flow overview if your goal is to understand execution order. Jump to the code walkthrough if you want to understand every register write in `__cpu_setup`. Use the deep-understanding section if you want to reason about design tradeoffs, scalability, platform bring-up, or debug failures in early boot. Use the interview section for system-design preparation.
