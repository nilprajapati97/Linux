# Translation Design Tradeoffs

`__cpu_setup` is small, but it reflects several large design choices in the ARM64 kernel.

## Tradeoff 1: staged mapping instead of immediate final mapping

Linux uses an early identity map first and a fuller kernel mapping later.

### Benefits

- lower risk during MMU-on
- simpler reasoning about the instruction stream during transition
- easier portability across relocation and early boot configurations

### Cost

- more stages to understand
- more temporary state to keep consistent

## Tradeoff 2: per-CPU setup function reused by primary and secondary CPUs

The same `__cpu_setup` logic is used in multiple bring-up flows.

### Benefits

- consistent translation policy on all CPUs
- less duplicated assembly
- easier feature and errata management

### Cost

- the function must stay generic and architecture-oriented rather than primary-CPU specific

## Tradeoff 3: capability-driven setup rather than fixed hardcoded policy

`__cpu_setup` reads feature registers and adapts.

### Benefits

- one kernel image can run across more hardware
- hardware-managed access flags and newer features can be used automatically
- VA52 and LPA2 style configurations are handled safely

### Cost

- more conditional behavior in an already delicate boot path
- harder reasoning during debug if the exact CPU capability set is unknown

## Tradeoff 4: macro-heavy assembly

Much of the real behavior is carried by macros and symbolic definitions.

### Benefits

- shared implementation of delicate architectural sequences
- configuration-aware code generation
- reuse across multiple low-level paths

### Cost

- harder for newcomers to read linearly
- easy to underestimate what the function is really doing

## System-design lesson

The code around `bl __cpu_setup` is a good example of a disciplined low-level interface:

- inputs are minimal
- responsibilities are focused
- state changes are sequenced tightly
- activation is delayed until all prerequisites exist

That pattern appears repeatedly in high-quality kernel and firmware design.
