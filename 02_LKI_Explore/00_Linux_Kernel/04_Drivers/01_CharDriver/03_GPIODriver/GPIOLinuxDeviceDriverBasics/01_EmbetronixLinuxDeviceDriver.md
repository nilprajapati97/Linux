Embetronix Linux Device Driver
===============================================================

Here’s your content reformatted into **clear step-by-step points** for accessing GPIO in the Linux Kernel:

---

### Accessing GPIO in Linux Kernel – Steps
====================================================================================
1. **Check validity**

   * Verify whether the GPIO number is valid.
   * API: `gpio_is_valid(gpio_num)`

2. **Request the GPIO**

   * If valid, request ownership from the GPIO subsystem.
   * API: `gpio_request(gpio_num, "label")`

3. **(Optional) Export to sysfs**

   * Export GPIO to userspace via sysfs for testing/debugging.
   * API: `gpio_export(gpio_num, true/false)`

4. **Set direction**

   * Configure the GPIO direction: input or output.
   * APIs:

     * `gpio_direction_input(gpio_num)`
     * `gpio_direction_output(gpio_num, value)`

5. **Control / Read GPIO**

   * If configured as **output** → set High/Low.

     * API: `gpio_set_value(gpio_num, value)`
   * If configured as **input** → read current state.

     * API: `gpio_get_value(gpio_num)`

6. **Debounce & Interrupts**

   * Configure debounce interval if needed.

     * API: `gpio_set_debounce(gpio_num, usecs)`
   * Enable IRQ for edge/level triggered interrupts.

     * API: `gpio_to_irq(gpio_num)` + `request_irq()`

7. **Release GPIO**

   * Free the GPIO when no longer required.
   * API: `gpio_free(gpio_num)`

---

👉 Do you want me to also prepare a **minimal GPIO kernel driver template** with these APIs (probe, set input/output, IRQ handler, cleanup) so you can test on real hardware?



Got it ✅ — here’s your content reformatted **point-wise** for clarity:

---

# GPIO APIs in Linux Kernel

Include the header file:

```c
#include <linux/gpio.h>
```

---

### 1. Validate GPIO

* **API:**

  ```c
  bool gpio_is_valid(int gpio_number);
  ```
* **Params:**

  * `gpio_number`: GPIO you want to use.
* **Return:**

  * `true` → valid
  * `false` → invalid (or temporarily unused on board).

---

### 2. Request GPIO

* **API:**

  ```c
  int gpio_request(unsigned gpio, const char *label);
  ```

* **Params:**

  * `gpio`: GPIO number.
  * `label`: string identifier (visible in `/sys/kernel/debug/gpio`).

* **Return:**

  * `0` on success, negative error on failure.

* **Variants:**

  * Request one GPIO:

    ```c
    int gpio_request_one(unsigned gpio, unsigned long flags, const char *label);
    ```
  * Request multiple GPIOs:

    ```c
    int gpio_request_array(struct gpio *array, size_t num);
    ```

---

### 3. Export GPIO (optional – for debugging in sysfs)

* **API:**

  ```c
  int gpio_export(unsigned int gpio, bool direction_may_change);
  ```
* **Params:**

  * `gpio`: GPIO to export.
  * `direction_may_change`:

    * `true` → user can change direction.
    * `false` → fixed direction.
* **Result:**

  * GPIO visible at `/sys/class/gpio/`.

---

### 4. Unexport GPIO

* **API:**

  ```c
  void gpio_unexport(unsigned int gpio);
  ```
* **Params:**

  * `gpio`: GPIO to unexport.

---

### 5. Set GPIO Direction

* **As Input:**

  ```c
  int gpio_direction_input(unsigned gpio);
  ```

  * Returns `0` on success.

* **As Output:**

  ```c
  int gpio_direction_output(unsigned gpio, int value);
  ```

  * `value`: initial state (0 = Low, 1 = High).
  * Returns `0` on success.

---

### 6. Change GPIO Value (output only)

* **API:**

  ```c
  void gpio_set_value(unsigned int gpio, int value);
  ```
* **Params:**

  * `value`: 0 = Low, 1 = High.

---

### 7. Read GPIO Value (input only)

* **API:**

  ```c
  int gpio_get_value(unsigned gpio);
  ```
* **Return:**

  * `0` = Low, `1` = High.

---

### 8. GPIO Interrupt (IRQ)

* Convert GPIO to IRQ line:

  ```c
  int gpio_to_irq(unsigned gpio);
  ```
* Typically followed by:

  ```c
  request_irq(irq, handler, flags, name, dev);
  ```

*(Detailed IRQ usage usually covered separately.)*

---

### 9. Release GPIO

* **API:**

  ```c
  void gpio_free(unsigned int gpio);
  ```

* **Params:**

  * `gpio`: GPIO to release.

* **Variant (multiple GPIOs):**

  ```c
  void gpio_free_array(struct gpio *array, size_t num);
  ```

---

👉 This makes a complete **step-by-step GPIO lifecycle** in the Linux kernel:
**Validate → Request → (Export) → Configure Direction → Set/Get Value → (IRQ) → Release.**

---

Do you also want me to prepare a **minimal kernel driver code** (with request, direction set, read/write, and cleanup) that you can directly build and load to test GPIO on hardware?

Yes 👍 that would be the next logical step.
I can prepare a **minimal kernel driver template** for GPIO that does:

* Request GPIO from kernel.
* Set direction (input/output).
* Read / Write GPIO value.
* Optionally enable IRQ for input pin.
* Proper cleanup on remove.

You’ll then be able to build and `insmod` it on your board to test GPIO access in a structured way.

👉 Do you want this driver based on the **new GPIO descriptor API (`gpiod_*`)** (preferred, modern kernels) or the **legacy `gpio_*` API** (still common in BSPs but deprecated)?


