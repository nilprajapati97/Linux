# 01 Boot Flow

This section explains the full boot context around `bl __cpu_setup`.

## Documents

1. [01_boot_overview.md](01_boot_overview.md)
2. [02_bootloader_contract_and_entry_state.md](02_bootloader_contract_and_entry_state.md)
3. [03_el_transition_el1_vs_el2.md](03_el_transition_el1_vs_el2.md)
4. [04_idmap_ttbr_and_early_page_tables.md](04_idmap_ttbr_and_early_page_tables.md)
5. [05_tlb_cache_barriers_and_mmu_enable.md](05_tlb_cache_barriers_and_mmu_enable.md)

## What this section covers

- bootloader to kernel handoff on ARMv8/AArch64
- why Linux first creates an identity map
- why `__cpu_setup` is called before `__enable_mmu`
- what changes in the CPU at EL1 or EL2 before the kernel enters normal C code
- how primary and secondary CPU paths differ
