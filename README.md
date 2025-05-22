# ⚙️ Embedded C Drivers for Simulated Embedded Projects

This repository contains modular and reusable **C code** for embedded systems projects, structured in a layered architecture to separate low-level hardware access from high-level application logic.

The drivers are used in Proteus simulations covering various components like LCDs, motors, keypads, EEPROM, etc.

---

## 🧱 Layered Architecture

The codebase follows a clean separation of concerns using 3 main layers:

---

### 🧩 1. MCAL (Microcontroller Abstraction Layer)

**Purpose:** Low-level register-level access to the microcontroller hardware.

**Examples:**
- `GPIO.c / GPIO.h` — Digital I/O pin control (Set, Clear, Toggle)
- `PORT.c / PORT.h` — Port initialization and configuration
- `ADC.c / ADC.h` — Analog-to-digital converter setup
- `Timer.c / Timer.h` — Timer configurations and interrupts

📂 Folder: `MCAL/`

---

### 🔌 2. ECU Layer (Electronic Control Unit Drivers)

**Purpose:** Mid-level drivers that directly manage specific peripherals using MCAL functions.

**Examples:**
- `LED.c / LED.h` — LED on/off/toggle using DIO
- `Button.c / Button.h` — Read and debounce button states
- `Relay.c / Relay.h` — Relay module control via digital pins

📂 Folder: `ECU/`

---

### 🖥️ 3. Drivers (Application-Level Drivers)

**Purpose:** Higher-level, user-facing drivers built on top of ECU and MCAL.

**Examples:**
- `LCD.c / LCD.h` — 16x2 Character LCD interface
- `Keypad.c / Keypad.h` — 4x4 matrix keypad scanning
- `DCMotor.c / DCMotor.h` — Direction and speed control
- `EEPROM.c / EEPROM.h` — I2C or SPI EEPROM read/write

📂 Folder: `Drivers/`

---

## 🧪 How to Use

1. Clone the repo and include the required driver folders in your project.
2. Include headers like `#include "LCD.h"` in your `main.c`.
3. Initialize components (e.g., `LCD_init()`) and start using functions.

> ✅ All drivers are written in standard C and are compatible with AVR microcontrollers like ATmega32.

---

## 📚 Example File Usage

```c
#include "LCD.h"
#include "Keypad.h"

int main(void) {
    LCD_init();
    Keypad_init();

    while (1) {
        char key = Keypad_getKey();
        LCD_displayChar(key);
    }
}
