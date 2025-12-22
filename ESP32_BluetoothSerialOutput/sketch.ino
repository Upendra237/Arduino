#include "BluetoothSerial.h"

BluetoothSerial SerialBT; // Create Bluetooth Serial object

void setup() {
  Serial.begin(115200); // Initialize USB Serial at 115200 baud
  SerialBT.begin("ESP32_BT"); // Initialize Bluetooth with device name "ESP32_BT"
  
  // Print startup message to both Serial and Bluetooth
  Serial.println("Bluetooth Started");
  SerialBT.println("Bluetooth Started");
}

void loop() {
  Serial.println("Hello"); // Send "Hello" to USB Serial Monitor
  SerialBT.println("Hello"); // Send "Hello" to Bluetooth Serial
  
  delay(500); // Wait 500ms before next message
}