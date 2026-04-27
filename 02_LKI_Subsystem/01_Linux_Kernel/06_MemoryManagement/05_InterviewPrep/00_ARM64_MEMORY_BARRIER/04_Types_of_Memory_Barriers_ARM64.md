# Types of Memory Barriers (ARM64)

## ARM64 Barrier Instructions
- **DMB (Data Memory Barrier):** Ensures memory accesses before the barrier are globally observed before those after.
- **DSB (Data Synchronization Barrier):** Like DMB, but also waits for completion of memory accesses.
- **ISB (Instruction Synchronization Barrier):** Flushes the pipeline, ensures subsequent instructions are fetched anew.

## DMB Variants
- DMB SY (full barrier)
- DMB ST (store barrier)
- DMB LD (load barrier)

## When to Use Which?
- Use DMB SY for most kernel synchronization.
- Use DSB for device access or self-modifying code.
- Use ISB after changing code or control registers.

---

**Interview Tip:**
Know the difference between DMB, DSB, and ISB, and when to use each.
