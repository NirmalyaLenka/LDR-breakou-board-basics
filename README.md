# ESP32 LDR Breakout — Light-Level Monitor

An ESP32 learning project for reading the analog output of an LDR (light-dependent resistor) breakout and displaying an approximate light level, a coarse lighting category, and the module's digital comparator state in the Serial Monitor. The repository also includes offline HTML reference pages for board-specific wiring and code examples.

## What it does

- Reads the module's analog output on ESP32 GPIO 34
- Reads the digital comparator output on GPIO 35
- Prints raw ADC count, approximate voltage, an estimated percentage, a lighting label, and a serial bar graph
- Uses editable thresholds to classify readings as bright, normal, dim, or dark

**Important limitation:** An LDR module's analog-output polarity depends on its circuit. The current sketch assumes higher ADC values mean darker conditions and maps the percentage in reverse. Verify this with your own module before using the displayed percentage or labels as measurements. These values are relative indicators, not calibrated lux.

## Hardware and wiring

| LDR breakout | ESP32 |
| --- | --- |
| VCC | 3.3 V |
| GND | GND |
| AO | GPIO 34 |
| DO | GPIO 35 |

GPIO 34 and GPIO 35 are input-only on the classic ESP32 and are suitable for these input signals. Power the module from **3.3 V** for this example so its outputs stay within ESP32 input limits. Do not power a module from 5 V unless you have confirmed its output voltages cannot exceed the ESP32's safe input range.

The digital output's HIGH/LOW meaning depends on the module's comparator design and potentiometer setting. Confirm its polarity rather than assuming HIGH always means dark.

## Bill of materials

| Item | Quantity | Notes |
| --- | ---: | --- |
| ESP32 development board | 1 | Classic ESP32 pin mapping is used by the sketch |
| LDR breakout module | 1 | Prefer a module that works at 3.3 V |
| Jumper wires | 4 | VCC, GND, AO, DO |
| USB data cable | 1 | Upload and Serial Monitor |
| Breadboard | 1, optional | For prototyping |

This BOM matches the current ESP32 example. The multi-board HTML reference includes other targets, whose voltage requirements and pin mappings must be checked individually.

## Software setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 board support using Espressif's package URL:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Open `ldr_esp32.ino`.
4. Select the appropriate ESP32 board and serial port.
5. Compile and upload, then open Serial Monitor at **115200 baud**.

No extra Arduino library is required for the main sketch; it uses `analogRead()`, `digitalRead()`, and standard Arduino functions.

## Configuration

The main sketch uses these defaults:

```cpp
#define LDR_ANALOG_PIN   34
#define LDR_DIGITAL_PIN  35
#define THRESHOLD_BRIGHT 800
#define THRESHOLD_NORMAL 2000
#define THRESHOLD_DIM    3000
```

These thresholds assume a 12-bit ADC reading from 0 to 4095 and a module whose ADC value rises as the environment gets darker. Tune them from readings in your actual environment. The voltage conversion uses a simplified 3.3 V scale; ESP32 ADC behavior is not a precision voltmeter and can vary with attenuation, chip, and board.

## Offline reference pages

Open these files directly in a browser; they are intended to work locally without a server:

- [Interactive board wiring guide](./index.html) — board selector and pin guidance
- [Code reference](./codes.html) — board-specific example snippets
- [LDR datasheet/reference PDF](./LDR%20Datasheet.pdf)

The HTML pages contain examples for multiple boards. Treat them as reference material, not proof that every included snippet has been compiled or tested. Confirm the voltage limits, ADC resolution, pin availability, and board-core requirements for the exact target before wiring or uploading.

## Repository structure

```text
LDR-breakou-board-basics/
├── LDR Datasheet.pdf   # Sensor/module reference document
├── README.md           # Setup, wiring, BOM, limitations, and maintenance
├── codes.html          # Offline multi-board code reference
├── index.html          # Offline interactive wiring guide
└── ldr_esp32.ino       # Main ESP32 firmware sketch
```

## Troubleshooting

| Symptom | Check |
| --- | --- |
| ADC stays at 0 or 4095 | Check AO wiring and verify the selected GPIO is ADC-capable |
| Percentage seems inverted | Confirm whether your module's AO rises in light or darkness; adjust mapping accordingly |
| DO never changes | Adjust the module potentiometer and verify the comparator output polarity |
| ESP32 resets or pin gets hot | Disconnect power and check for 5 V signals reaching ESP32 GPIO |
| Readings jump around | Check ground/wiring and average multiple samples if needed |

## Potential extensions

- Calibrate the mapping against a known light meter if approximate lux is required
- Add sampling averaging or a small moving average filter
- Add a configurable threshold interface
- Use a transistor/MOSFET driver for a lamp or relay rather than powering a load from a GPIO

## Skills and technologies

`ESP32` · `Arduino C++` · `ADC` · `GPIO` · `Sensor interfacing` · `HTML/CSS/JavaScript`

## Maintenance & audit

- **Last updated:** 11 November 2026
- **Review scope:** Compared the README with the tracked sketch, HTML reference pages, PDF, and root file list.
- **Documentation changes:** Consolidated duplicated sections, updated the BOM and paths, and clarified ADC scaling, signal polarity, and 3.3 V input safety.
- **Firmware status:** No firmware change was made because the light-level mapping depends on the exact breakout circuit and has not been validated on hardware. No compile or physical test was run.
- **License:** No `LICENSE` file was found in the root listing; no specific reuse license is claimed here.
