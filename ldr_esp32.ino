
 * LDR (Light Dependent Resistor) Breakout Board with ESP32
 * Reads ambient light levels and classifies lighting conditions
 *
 * Wiring (Analog Module):
 *   LDR Module VCC  -> ESP32 3.3V
 *   LDR Module GND  -> ESP32 GND
 *   LDR Module AO   -> ESP32 GPIO 34 (Analog Output)
 *   LDR Module DO   -> ESP32 GPIO 35 (Digital Output - threshold trigger)
 *
 * Note: GPIO 34 and 35 are input-only pins on ESP32, perfect for analog reading.
 *
 * Required Library: None (uses built-in analogRead)
 */

// Pin Definitions
#define LDR_ANALOG_PIN   34   // Analog output from LDR module
#define LDR_DIGITAL_PIN  35   // Digital output (HIGH = dark, LOW = bright)

// ADC Configuration
#define ADC_RESOLUTION   4095  // ESP32 = 12-bit ADC (0–4095)
#define VOLTAGE_REF      3.3   // ESP32 reference voltage

// Light level thresholds (0–4095, higher = darker for most modules)
#define THRESHOLD_BRIGHT    800
#define THRESHOLD_NORMAL   2000
#define THRESHOLD_DIM      3000
// Above 3000 = Dark

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Set analog read resolution to 12-bit (ESP32 default)
  analogReadResolution(12);

  // Set digital pin as input
  pinMode(LDR_DIGITAL_PIN, INPUT);

  Serial.println("=================================");
  Serial.println("   ESP32 + LDR Breakout Demo     ");
  Serial.println("=================================");
  Serial.println("ADC Range   : 0 - 4095");
  Serial.println("Voltage Ref : 3.3V");
  Serial.println("---------------------------------");
  Serial.println("LDR initialized successfully!");
  Serial.println();
}

String getLightCondition(int rawValue) {
  if (rawValue < THRESHOLD_BRIGHT) {
    return "BRIGHT (Direct Light / Sunlight)";
  } else if (rawValue < THRESHOLD_NORMAL) {
    return "NORMAL (Indoor / Ambient Light)";
  } else if (rawValue < THRESHOLD_DIM) {
    return "DIM (Low Light / Evening)";
  } else {
    return "DARK (No Light / Night)";
  }
}

void loop() {
  // Read analog value (0–4095)
  int rawValue = analogRead(LDR_ANALOG_PIN);

  // Convert to voltage
  float voltage = (rawValue / (float)ADC_RESOLUTION) * VOLTAGE_REF;

  // Convert to percentage (0% = fully dark, 100% = fully bright)
  // Most LDR modules output HIGH voltage in dark, so invert
  int lightPercent = map(rawValue, 0, ADC_RESOLUTION, 100, 0);

  // Read digital pin (module threshold comparator output)
  bool darkDetected = digitalRead(LDR_DIGITAL_PIN);

  // Get light condition label
  String condition = getLightCondition(rawValue);

  // Print all readings
  Serial.println("--- LDR Sensor Readings ---");

  Serial.print("Raw ADC     : ");
  Serial.print(rawValue);
  Serial.print(" / ");
  Serial.println(ADC_RESOLUTION);

  Serial.print("Voltage     : ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  Serial.print("Light Level : ");
  Serial.print(lightPercent);
  Serial.println(" %");

  Serial.print("Condition   : ");
  Serial.println(condition);

  Serial.print("Digital Out : ");
  Serial.println(darkDetected ? "DARK (threshold exceeded)" : "BRIGHT (below threshold)");

  // Visual light bar
  Serial.print("Light Bar   : [");
  int bars = lightPercent / 10;
  for (int i = 0; i < 10; i++) {
    Serial.print(i < bars ? "█" : "░");
  }
  Serial.print("] ");
  Serial.print(lightPercent);
  Serial.println("%");

  Serial.println("---------------------------");
  Serial.println();

  delay(1000); // Read every 1 second
}
