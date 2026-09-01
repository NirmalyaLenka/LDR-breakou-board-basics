# LDR-breakou-board-basics
# ESP32 + LDR Breakout Board 

Read **ambient light levels**, get a **light percentage**, classify **lighting conditions**, and detect **darkness** using an LDR (Light Dependent Resistor) breakout module with an ESP32.

----

##  Components Required

| Component | Quantity |
|-----------|----------|
| ESP32 Dev Board | 1 |
| LDR Breakout / Module | 1 |
| Jumper Wires | 4 |
| Breadboard (optional) | 1 |

> Most LDR breakout boards have an onboard potentiometer to adjust the digital threshold and two outputs: **AO (Analog)** and **DO (Digital)**.

--- <img width="408" height="306" alt="image" src="https://github.com/user-attachments/assets/c3b353e8-41d6-43f5-b6f8-75bc27d1c590" />  ESP32 Dev Board
    <img width="1080" height="1080" alt="image" src="https://github.com/user-attachments/assets/64bb2646-e391-4c5c-8575-309e6fe8bbda" /> LDR Breakout / Module
    <img width="133" height="133" alt="image" src="https://github.com/user-attachments/assets/1b1c78be-212f-4b89-814f-39b0ed08feda" />  
    Jumper Wires
    

##  Wiring Diagram

```
LDR Module      ESP32
----------      -----
VCC    ──────►  3.3V
GND    ──────►  GND
AO     ──────►  GPIO 34  (Analog reading)
DO     ──────►  GPIO 35  (Digital threshold trigger)
```

>  GPIO 34 and 35 are **input-only** pins on the ESP32 — perfect for analog and digital reading.  
>  Use **3.3V** power. Some LDR modules also support 5V, but keep the signal pins at 3.3V logic for ESP32.

---

##  Setup & Installation

### 1. Install Arduino IDE
Download from [arduino.cc](https://www.arduino.cc/en/software)

### 2. Add ESP32 Board Support
1. Open **Arduino IDE** → **File** → **Preferences**
2. Add this URL to *Additional Boards Manager URLs*:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools** → **Board** → **Boards Manager**
4. Search for `esp32` and click **Install**

### 3. No Extra Libraries Needed! 
This project uses only the **built-in** `analogRead()` and `digitalRead()` functions — no additional libraries required.

### 4. Upload the Sketch
1. Open `ldr_esp32.ino` in Arduino IDE
2. Select your board: **Tools** → **Board** → **ESP32 Dev Module**
3. Select the correct **Port** under **Tools** → **Port**
4. Click **Upload** 

---

##  Serial Monitor Output

Open Serial Monitor at **115200 baud** to see live readings:

```
=================================
   ESP32 + LDR Breakout Demo     
=================================
ADC Range   : 0 - 4095
Voltage Ref : 3.3V
--------------------------------
LDR initialized successfully!

--- LDR Sensor Readings ---
Raw ADC     : 512 / 4095
Voltage     : 0.413 V
Light Level : 87 %
Condition   : BRIGHT (Direct Light / Sunlight)
Digital Out : BRIGHT (below threshold)
Light Bar   : [████████░░] 87%
---------------------------
```
# 💡 LDR Breakout Board — Multi-Platform Wiring & Code Reference

> **⚠️ IMPORTANT FOR ALL USERS — READ BEFORE CONNECTING ANYTHING**
>
> This library supports **15 development boards**. Before you wire your LDR module
> or upload any sketch, please visit the official reference website to get the
> **correct wiring diagram and verified code** for your specific board.
>
> Skipping this step and guessing pin numbers is the #1 cause of burnt ADC pins,
> incorrect readings, and damaged boards.

---

## 🌐 Official Reference Website

### 👉 [Open Wiring Guide → `index.html`](./index.html)
### 👉 [Browse All Codes → `codes.html`](./codes.html)

Open these HTML files in any browser — **no internet connection required.**

| Page | What you get |
|---|---|
| `index.html` | Interactive board selector · Wiring table · Pin labels · Board specs |
| `codes.html` | Full sketches for all 15 boards · Syntax highlighted · Copy & Download buttons |

---

## ⚠️ Why the Website Reference Matters

Every board in this library has **different rules**:

| Risk | Example boards affected |
|---|---|
| **Wrong voltage will destroy your board** | Arduino Due, STM32 Blue Pill, Teensy 4.0, MKR WiFi — all 3.3V ONLY, not 5V tolerant |
| **Wrong analog pin will give no reading** | ESP8266 has only 1 analog pin (A0), max 1.0V input |
| **ADC resolution varies — thresholds differ** | Uno/Nano = 10-bit (0–1023) · ESP32/Pico = 12-bit (0–4095) · Portenta H7 = 16-bit (0–65535) |
| **Strapping pins cause boot failures** | ESP32-C3: avoid GPIO 5 at boot; ESP32: avoid GPIO 0/2/15 |
| **ADC2 conflicts with Wi-Fi** | ESP32 / ESP32-S3: use ADC1 pins only when radio is active |
| **No hardware Serial on tiny boards** | ATtiny85/Digispark: USB HID only — no standard Serial.println() |

**The website shows all of this per board, with the correct pin numbers and warnings highlighted in orange.**

---

## 🔌 LDR Module Pins (Quick Reference)

All boards in this project use the standard 4-pin LDR breakout module:

```
LDR Module          →   Your Board
──────────────────────────────────────────
VCC                 →   3.3V or 5V  (check your board!)
GND                 →   GND
AO  (Analog Out)    →   ADC-capable pin  (check website for which one)
DO  (Digital Out)   →   Any digital input pin
```

> **Never assume the pin number.** Open `index.html`, click your board, and read
> the wiring table. It takes 30 seconds and saves you from irreversible damage.

---

## 🗂️ Files in This Project

```
📁 project/
├── 📄 README.md            ← You are here
├── 🌐 index.html           ← Interactive wiring guide (open in browser)
├── 🌐 codes.html           ← All 15 board sketches (open in browser)
└── 📁 sketches/            ← Individual .ino / .py files (optional)
    ├── esp32_ldr.ino
    ├── uno_ldr.ino
    ├── nano_ldr.ino
    ├── mega_ldr.ino
    ├── esp8266_ldr.ino
    ├── pico_ldr.py          ← MicroPython
    ├── stm32_bluepill_ldr.ino
    ├── due_ldr.ino
    ├── esp32s3_ldr.ino
    ├── teensy40_ldr.ino
    ├── mkr_wifi_ldr.ino
    ├── attiny85_ldr.ino
    ├── portenta_h7_ldr.ino
    ├── micro_ldr.ino
    └── esp32c3_ldr.ino
```

---

## 🛒 Supported Boards at a Glance

| # | Board | MCU | Voltage | ADC |
|---|---|---|---|---|
| 1 | ESP32 DevKit V1 | Xtensa LX6 240 MHz | 3.3V | 12-bit |
| 2 | Arduino Uno R3 | ATmega328P 16 MHz | 5V | 10-bit |
| 3 | Arduino Nano | ATmega328P 16 MHz | 5V | 10-bit |
| 4 | Arduino Mega 2560 | ATmega2560 16 MHz | 5V | 10-bit |
| 5 | NodeMCU ESP8266 | Xtensa L106 80 MHz | 3.3V | 10-bit (1 ch) |
| 6 | Raspberry Pi Pico | RP2040 Dual M0+ 133 MHz | 3.3V | 12-bit |
| 7 | STM32 Blue Pill | STM32F103C8 72 MHz | 3.3V | 12-bit |
| 8 | Arduino Due | AT91SAM3X8E 84 MHz | **3.3V ONLY** | 12-bit |
| 9 | ESP32-S3 | Xtensa LX7 240 MHz | 3.3V | 12-bit |
| 10 | Teensy 4.0 | ARM Cortex-M7 600 MHz | 3.3V | 10/12-bit |
| 11 | Arduino MKR WiFi 1010 | SAMD21 M0+ 48 MHz | 3.3V | 12-bit |
| 12 | ATtiny85 / Digispark | ATtiny85 16.5 MHz | 5V | 10-bit |
| 13 | Arduino Portenta H7 | STM32H747 Dual 480 MHz | 3.3V | **16-bit** |
| 14 | Arduino Micro | ATmega32U4 16 MHz | 5V | 10-bit |
| 15 | ESP32-C3 SuperMini | RISC-V 160 MHz | 3.3V | 12-bit |

---

## 🚦 Light Level Classification

All sketches use this 4-zone classification (thresholds are for 12-bit ADC; see code for 10-bit and 16-bit equivalents):

```
ADC Value (12-bit)    Classification
──────────────────────────────────────────────────
0    – 799            BRIGHT  (direct sunlight / lamp)
800  – 1999           NORMAL  (indoor ambient)
2000 – 2999           DIM     (evening / shade)
3000 – 4095           DARK    (night / covered)
```

> Note: Most LDR modules output **higher voltage when darker** (resistor divider logic).
> The code inverts this: `lightPercent = map(raw, 0, 4095, 100, 0)` so 100% = full brightness.

---

## 📋 How to Use This Project

```
Step 1 → Open index.html in your browser
Step 2 → Click your board from the grid
Step 3 → Read the wiring table — connect VCC, GND, AO, DO
Step 4 → Open codes.html, find your board, click Copy or Download
Step 5 → Open Arduino IDE (or Thonny for Pico), paste the code
Step 6 → Select the correct board and COM port, then upload
Step 7 → Open Serial Monitor at the baud rate shown in the code
```

---

## 🔧 Required Libraries

| Board | Library needed | Install via |
|---|---|---|
| All Arduino boards | None (built-in `analogRead`) | — |
| Raspberry Pi Pico | `machine` (built-in MicroPython) | — |
| ATtiny85 / Digispark | `DigiUSB` | Digistump board package |
| STM32 Blue Pill | STM32duino core | Arduino Board Manager |
| Teensy 4.0 | Teensyduino add-on | [pjrc.com/teensy/td_download.html](https://www.pjrc.com/teensy/td_download.html) |

---

## 🐛 Troubleshooting

**Serial Monitor shows nothing / garbled text**
→ Check baud rate matches the code (`115200` for most, `9600` for Uno/Nano/Mega)

**ADC always reads 0 or 4095**
→ Wrong analog pin selected — open `index.html` and verify the AO pin for your board

**Board crashes or won't boot after connecting**
→ You may have connected to a strapping pin — check the warning box in `index.html`

**ESP8266 A0 always reads very low**
→ Normal — A0 has an internal divider; maximum input voltage at the pin is 1.0V

**`while (!Serial)` hangs forever**
→ Only affects USB-CDC boards (Micro, Portenta, Leonardo). Open Serial Monitor in IDE.

**Raspberry Pi Pico — no output**
→ Use Thonny IDE with MicroPython firmware flashed. REPL must be active.

---

## ⚖️ License

All code in this project is released under the **MIT License** — free to use,
modify, and distribute in personal and commercial projects.

---

*Generated reference for LDR Breakout Module · 15 Development Boards · Analog + Digital output*
---

## Configuration

### Adjust Light Level Thresholds
Modify these values in the code to match your environment:

```cpp
#define THRESHOLD_BRIGHT    800   // Below this = Bright
#define THRESHOLD_NORMAL   2000   // Below this = Normal
#define THRESHOLD_DIM      3000   // Below this = Dim
                                  // Above 3000  = Dark
```

> Higher raw ADC value = darker environment (for most LDR modules).

### Adjust Digital Threshold
Rotate the **onboard potentiometer** on your LDR module to set the sensitivity point where the **DO pin** switches from HIGH to LOW.

---

##  Features

| Feature | Description |
|---------|-------------|
| Raw ADC Value | 12-bit reading from 0 to 4095 |
| Voltage Output | Converted voltage from ADC reading |
| Light Percentage | 0% = fully dark, 100% = fully bright |
| Condition Label | Bright / Normal / Dim / Dark |
| Digital Detection | Module comparator output via DO pin |
| Visual Light Bar | ASCII bar graph in Serial Monitor |

---

# Light Condition Reference

| Condition | Raw ADC Range | Description |
|-----------|---------------|-------------|
| BRIGHT | 0 – 800 | Direct sunlight or strong light |
| NORMAL | 801 – 2000 | Indoor ambient / office lighting |
| DIM | 2001 – 3000 | Evening light / low lamp |
| DARK | 3001 – 4095 | Night / no light source |

---

##  Troubleshooting

| Problem | Solution |
|--------|----------|
| Always reads 0 or 4095 | Check AO pin is connected to GPIO 34 |
| DO pin never changes | Adjust the onboard potentiometer |
| Readings unstable | Add a 100nF capacitor between VCC and GND near module |
| Board not detected | Install CP210x or CH340 USB driver |
| Wrong light % values | Adjust threshold constants in the code |

---

##  Project Structure

```
esp32-ldr/
│
├── ldr_esp32.ino   # Main Arduino sketch
└── README.md       # This file
```

---

## Project Ideas

- Automatic street light (turn LED on when dark)
- Auto screen brightness controller
-  Plant light monitor — alert when plant needs more sun
-  Day/night cycle detector for IoT systems
-  Flashlight or torch detector
-  Smart home ambient light sensor

---

##  Resources

- [ESP32 ADC Reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/adc.html)
- [Arduino analogRead()](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)
- [LDR / Photoresistor Basics](https://en.wikipedia.org/wiki/Photoresistor)

---

##  License

This project is open source and available under the [MIT License](LICENSE).

---

##  Contributing

Pull requests are welcome! Feel free to open an issue for bugs or feature requests.

---

