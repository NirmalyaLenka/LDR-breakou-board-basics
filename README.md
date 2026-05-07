# LDR-breakou-board-basics
# ESP32 + LDR Breakout Board 

Read **ambient light levels**, get a **light percentage**, classify **lighting conditions**, and detect **darkness** using an LDR (Light Dependent Resistor) breakout module with an ESP32.

---

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
---------------------------------
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

