SPL DDR bring-up
======================
Let's walk through both, tailored to **real U-Boot SPL bring-up**:

---

# ✅ A. Step-by-Step: **SPL DDR Initialization** (Example: TI AM335x or NXP i.MX6)

### 🎯 Goal:

Initialize DDR in SPL so that U-Boot proper can be loaded into DRAM.

---

## ✅ 1. SPL Entry Point: `board_init_f()`

In `spl/board/<vendor>/<board>/spl.c`:

```c
void board_init_f(ulong dummy)
{
    // Minimal init: clocks, pinmux
    prcm_init();
    sdram_init();   // <== DDR init happens here

    // Load U-Boot to DDR
    spl_load_image();
    jump_to_image_no_args(); // Jump to U-Boot proper in DDR
}
```

---

## ✅ 2. DDR Initialization Function

Example: `sdram_init()` for AM335x:

```c
void sdram_init(void)
{
    config_ddr(DDR_CLK_SPEED,
               &ioregs,   // DDR IO settings
               &ddr_data, // Read/write ratios
               &cmd_ctrl, // Command control timing
               &emif_reg); // EMIF controller config
}
```

---

## ✅ 3. Example DDR Parameters (AM335x):

Found in `board/ti/am335x/board.c`:

```c
static const struct ddr_data ddr3_data = {
    .datardsratio0 = 0x38,
    .datawdsratio0 = 0x38,
    .datafwsratio0 = 0x94,
    .datawrsratio0 = 0x94,
};

static const struct cmd_control cmd_ctrl = {
    .cmd0csratio = 0x80,
    .cmd0iclkout = 0x00,
};

static struct emif_regs emif_reg = {
    .sdram_config = 0x61C05332,
    .ref_ctrl = 0x00000C30,
    .sdram_tim1 = 0x0AAAD4DB,
    .zq_config = 0x50074BE4,
};
```

---

## ✅ 4. Register Programming in `config_ddr()`

From `arch/arm/mach-omap/ddr.c`:

```c
void config_ddr(unsigned int speed,
                const struct ddr_data *ddr,
                const struct cmd_control *cmd,
                const struct emif_regs *regs)
{
    // Configure IO controls
    config_io_ctrl(ddr);
    
    // Setup EMIF controller
    writel(regs->sdram_config, EMIF_SDRAM_CONFIG);
    writel(regs->ref_ctrl, EMIF_REF_CTRL);
    ...
}
```

---

## ✅ 5. Validation

After this, SPL loads U-Boot proper using:

```c
spl_load_image();
```

Which typically reads `u-boot.img` from MMC or NAND and places it in DDR.

---

# ✅ B. Early UART Bring-Up in SPL (for Debug)

### 🎯 Goal:

Enable UART in SPL before DDR works, using `CONFIG_DEBUG_UART`.

---

## ✅ 1. Enable in Kconfig:

In `configs/<board>_defconfig`:

```text
CONFIG_DEBUG_UART=y
CONFIG_DEBUG_UART_BASE=0x44E09000  # AM335x UART0 base
CONFIG_DEBUG_UART_CLOCK=48000000
CONFIG_DEBUG_UART_OMAP=y
```

---

## ✅ 2. Early Print Example

At the top of `board_init_f()` or `sdram_init()`:

```c
#include <debug_uart.h>

void board_init_f(ulong dummy)
{
    debug_uart_init();         // Sets baud, clock, UART regs

    printascii(">> SPL start...\n");
    
    prcm_init();
    sdram_init();

    printascii(">> DDR init done\n");
}
```

📌 `debug_uart_init()` uses MMIO — no driver required!

---

## ✅ 3. Optional: Manual UART Register Access (Without debug UART)

You can use direct MMIO for even earlier debug:

```c
#define UART0_BASE 0x44E09000

static inline void uart_putc(char c)
{
    volatile uint32_t *thr = (uint32_t *)(UART0_BASE + 0x00);
    volatile uint32_t *lsr = (uint32_t *)(UART0_BASE + 0x14);

    while (!(*lsr & (1 << 5)));  // Wait for THR empty
    *thr = c;
}
```

---

## ✅ Summary

| Component      | Key Function                  | File                             |
| -------------- | ----------------------------- | -------------------------------- |
| DDR init       | `sdram_init()`                | `board/<vendor>/<board>/board.c` |
| UART init      | `debug_uart_init()` or manual | `board_init_f()` or SPL          |
| Load U-Boot    | `spl_load_image()`            | SPL core                         |
| Jump to U-Boot | `jump_to_image_no_args()`     | SPL core                         |

---

Would you like:

* DDR bring-up logs from UART output?
* Custom board SPL bring-up checklist?
* Device tree + RAM overlay example?
