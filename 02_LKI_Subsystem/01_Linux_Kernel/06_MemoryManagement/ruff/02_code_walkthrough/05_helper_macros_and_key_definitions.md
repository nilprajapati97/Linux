# Helper Macros and Key Definitions

`__cpu_setup` is compact because much of its logic is expressed through helper macros and symbolic definitions.

## Key macros that shape the path

### set_sctlr_el1

Used later in `__enable_mmu`.

Purpose:

- write `SCTLR_EL1`
- execute an `ISB`
- invalidate the local I-cache
- execute final synchronization barriers

This macro is one reason MMU-on is treated as a controlled architectural transition rather than a single ordinary register write.

### load_ttbr1

Used in `__enable_mmu`.

Purpose:

- format the page-table root address appropriately for `TTBR1_EL1`
- apply any needed offset logic for supported VA modes
- write the register with the right ordering behavior

### phys_to_ttbr

Purpose:

- convert a physical page-table root into the form expected by a TTBR register
- handle 52-bit physical-address formatting when configured

### tcr_compute_pa_size

Purpose:

- read the CPU's physical-address-range capability
- set the proper `TCR_EL1.IPS` field value

### tcr_set_t1sz

Purpose:

- update the kernel-side address-space size field in `TCR_EL1`
- used when VA52 support is active

## Key symbolic definitions

### INIT_SCTLR_EL1_MMU_ON

This is the target `SCTLR_EL1` value for turning the MMU on in Linux's preferred baseline configuration.

It includes the key policy bits for:

- MMU enable
- data and instruction cache enable
- stack alignment checks
- exception-related safety behavior
- endianness configuration

### MAIR_EL1_SET

This definition encodes the memory-type attributes Linux wants page-table descriptors to refer to.

### TCR_* flags

These definitions construct the translation-control configuration:

- granule size
- cacheability of page-table walks
- shareability
- KASLR behavior
- top-byte-ignore behavior
- MTE and software tagging options

## Why the macro layer matters

When studying early boot, it is easy to focus only on the local assembly function body and miss the real behavior hidden behind macros. In ARM64 low-level code, many of the most important architectural decisions are expressed through these helpers.

A good reading pattern is:

1. read the call site
2. read `__cpu_setup`
3. read the macro definitions it uses or feeds into
4. then return to the call path to understand the full state transition
