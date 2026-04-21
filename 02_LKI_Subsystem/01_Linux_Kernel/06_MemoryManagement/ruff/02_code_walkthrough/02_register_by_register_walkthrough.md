# Register-by-Register Walkthrough of __cpu_setup

This walkthrough follows the order of the function body in `arch/arm64/mm/proc.S`.

## 1. Invalidate TLB state

The function starts with `tlbi vmalle1` and `dsb nsh`.

### Meaning

- all local EL1 stage-1 translations are invalidated
- the barrier ensures completion before later translation-control writes matter

### Why Linux does this

The kernel is about to install a fresh translation regime. Carrying old TLB state into that regime would be unsafe.

## 2. Reset CPACR_EL1

`msr cpacr_el1, xzr`

### Meaning

Coprocessor access policy is reset to a strict baseline. Linux does not assume any FP, SIMD, or other advanced access control state left by firmware is acceptable.

## 3. Reset MDSCR_EL1

`mdscr_el1` is written with `MDSCR_EL1_TDCC`.

### Meaning

The debug communications channel is disabled from EL0 and the debug state starts from a kernel-chosen baseline.

## 4. Disable PMU access from EL0

The helper macro checks if a PMU exists and, if it does, clears `PMUSERENR_EL0`.

### Meaning

User space does not get inherited PMU access during boot.

## 5. Disable AMU access from EL0

The helper macro checks if AMU exists and clears `AMUSERENR_EL0`.

### Meaning

Architectural activity monitor access is also reset to a secure baseline.

## 6. Build MAIR_EL1

The code loads `MAIR_EL1_SET` into the register named `mair`.

### Meaning

Linux defines the memory attribute encodings for:

- device nGnRnE
- device nGnRE
- normal non-cacheable
- normal cacheable
- normal tagged placeholder

These encodings are later referenced indirectly by page-table entries.

## 7. Build TCR_EL1

The code loads a composed value into the register named `tcr`.

### Major fields included

- `T0SZ` for the idmap side
- `T1SZ` for the kernel side
- inner and outer cacheability of table walks
- inner shareable behavior
- translation granule size
- ASID behavior
- top-byte-ignore and tagging-related options
- optional KASLR and MTE related flags

### Meaning

This is the core translation regime specification for EL1 stage-1 address translation.

## 8. Build TCR2_EL1 baseline

`tcr2` starts at zero.

### Meaning

Linux only turns on extended translation-control features if the CPU explicitly reports support.

## 9. Clear errata-sensitive TCR bits

The macro `tcr_clear_errata_bits` is invoked.

### Meaning

The translation-control value is adjusted for known CPU errata. This is one point where real silicon behavior overrides the clean architectural ideal.

## 10. Handle VA52 and LPA2 cases

If the kernel is built with VA52 support and the CPU supports it, Linux adjusts the kernel-side size and may set the `DS` bit for LPA2.

### Meaning

A single kernel image can adapt to hardware with different supported address-space widths.

## 11. Compute physical address size

`tcr_compute_pa_size` reads `ID_AA64MMFR0_EL1` and sets the TCR physical-address-size field.

### Meaning

The MMU must know how many physical address bits are valid for this CPU.

## 12. Enable hardware Access Flag support if present

Linux checks `ID_AA64MMFR1_EL1` and sets `TCR_EL1.HA` when supported.

### Meaning

The hardware can update access flags automatically instead of relying only on software page-fault paths.

## 13. Write MAIR_EL1 and TCR_EL1

The function writes `mair_el1` and `tcr_el1`.

### Meaning

The CPU now knows how the future translation regime should behave, but translation is still not active because `SCTLR_EL1.M` is not set yet.

## 14. Handle permission indirection and TCR2 extensions

Linux checks `ID_AA64MMFR3_EL1` and may program indirection registers and `TCR2_EL1`.

### Meaning

Newer architectural features are enabled only when the CPU advertises them.

## 15. Prepare SCTLR_EL1 return value

The function loads `INIT_SCTLR_EL1_MMU_ON` into `x0` and returns.

### Meaning

The caller receives the MMU-on control value to be installed a few instructions later in `__enable_mmu`.

## Most important takeaway

The function is entirely about preparing the CPU's translation policy. It is not about walking into normal kernel code. It is the last major setup phase before the hardware translation engine is actually activated.
