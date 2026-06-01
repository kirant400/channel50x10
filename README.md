# 50-Channel LED Controller using 74HC595 Shift Registers

**Microcontroller:** Nuvoton N76E003  
**Compiler:** SDCC  
**Language:** C  

A compact and expandable 50-channel LED controller built using 7x 74HC595 shift registers.

---

## Features

- Controls up to **50 individual LEDs**
- Uses only **3 GPIO pins** (Data, Clock, Latch)
- Daisy-chained 74HC595 shift registers
- Smooth chasing / Knight Rider style demo pattern
- Easily expandable up to 56 channels (7 registers)
- SDCC compatible
- Clean, well-commented code

---

## Hardware Requirements

| Component           | Quantity |
|---------------------|----------|
| Nuvoton N76E003     | 1        |
| 74HC595             | 7        |
| LEDs                | 50       |
| Current limiting resistors (220Ω–330Ω) | 50 |

### Pin Connections

| N76E003 Pin | Function     | Connected to          |
|-------------|--------------|-----------------------|
| P1.0        | DATA         | Pin 14 (DS) of first 595 |
| P1.1        | CLK          | Pin 11 (SHCP) all 595 |
| P1.2        | LATCH        | Pin 12 (STCP) all 595 |

**Daisy Chain Connection:**
- Connect **Q7' (Pin 9)** of each 595 to **DS (Pin 14)** of the next 595.

**Power:**
- Connect OE (Pin 13) of all 595 to GND (always enabled)
- Connect MR (Pin 10) of all 595 to VCC

---

## Software Setup

1. Clone or copy the project files
2. Make sure you have:
   - SDCC compiler
   - N76E003 include files (`N76E003.h`, `SFR_Macro.h`, etc.)
3. Build the project:

```bash
make