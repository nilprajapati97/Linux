# EL Transition: EL1 vs EL2 Before __cpu_setup

Before `__cpu_setup` runs, `init_kernel_el` ensures the kernel is executing with a known exception-level state.

## Why this exists

ARMv8 systems may hand control to Linux in either EL1 or EL2. Linux must therefore normalize the execution environment before programming memory-management registers for the final kernel world.

## If the kernel enters at EL1

`init_kernel_el`:

- writes a known `INIT_SCTLR_EL1_MMU_OFF`
- executes an `ISB`
- programs `SPSR_EL1` with `INIT_PSTATE_EL1`
- programs `ELR_EL1` with the return address
- returns with `ERET`

### CPU behavior

The processor remains in EL1, but now with a controlled, kernel-chosen initial state rather than whatever firmware happened to leave behind.

## If the kernel enters at EL2

`init_kernel_el`:

- preserves the return address in `ELR_EL2`
- optionally cleans hyp text if the MMU had been on
- writes `INIT_SCTLR_EL2_MMU_OFF`
- sets up EL2 control state using helper macros
- installs temporary EL2 vectors
- prepares an EL1 `SCTLR` value
- may use `SCTLR_EL12` when VHE is present
- writes `SPSR_EL2` so that execution can continue in EL1h-compatible state
- returns with `ERET`

### CPU behavior

The processor may still be exploiting EL2 capabilities during setup, but the path prepares the kernel to run in the highest supported and intended configuration without inheriting ambiguous firmware state.

## Why __cpu_setup is called after init_kernel_el

`__cpu_setup` is focused on translation and memory-system control. It assumes the broader exception-level context is already normalized.

That separation is deliberate:

- `init_kernel_el` handles privilege and execution level setup
- `__cpu_setup` handles translation attributes and stage-1 control programming
- `__enable_mmu` performs the actual MMU-on transition

## Key takeaway

The branch `bl __cpu_setup` only makes sense after Linux has decided what EL context it is going to use and after it has installed a safe, MMU-off control baseline. Otherwise, later register programming could be interpreted differently or applied in the wrong architectural context.
