# Arduino Folder Naming Guide

**Curated by:** [Upendra237](https://github.com/Upendra237)

In this Arduino collection, each folder is named using a clear, consistent format that helps you quickly understand the purpose, scope, and target hardware of the code.

## Folder Structure Example

```
Arduino/
├── BlinkLED_snippet/
├── Ultrasonic_component/
├── LEDPatterns_example/
├── WiFiScanner_esp32_program/
├── SmartHome_project/
└── MyServo_library/
```

## Naming Convention

### Basic Format:
```
<FolderName>_<Category>
```

### With Board-Specific Code:
```
<FolderName>_<BoardType>_<Category>
```

**When to specify board type:**
- If your code is specifically designed for or only works with a particular Arduino board
- Use lowercase board names: `esp32`, `nano`, `uno`, `mega`, `mkr1000`, `due`, etc.

**Examples:**
- `BlinkLED_snippet` → Works on any Arduino
- `WiFiSetup_esp32_snippet` → ESP32 specific
- `BLEScanner_nano33iot_program` → Arduino Nano 33 IoT specific

---

## The 6 Categories

### 1. `_snippet`

**Definition:** Tiny, focused code demonstrating one concept, function, or Arduino feature with minimal comments.

**Purpose:** Quick learning, experimenting, or testing small ideas.

**Characteristics:**
- 10-30 lines of code
- Bare minimum implementation
- Single concept focus

**Example Folder Names:**
- `BlinkLED_snippet` → Blinks an LED
- `ReadButton_snippet` → Reads a button press
- `AnalogRead_snippet` → Reads a sensor value
- `PWM_LED_snippet` → Controls LED brightness using PWM
- `SerialPrint_snippet` → Prints to serial monitor
- `DigitalWrite_snippet` → Basic digital output
- `Tone_snippet` → Generates sound with buzzer
- `Millis_snippet` → Uses millis() for timing
- `Interrupt_snippet` → Demonstrates interrupt usage
- `EEPROM_Write_snippet` → Writes to EEPROM

---

### 2. `_component`

**Definition:** Complete, ready-to-use code for controlling one sensor, actuator, or hardware device.

**Purpose:** Reusable building blocks that can be integrated into larger programs or projects.

**Characteristics:**
- 30-100 lines of code
- Single hardware device focus
- Can run standalone to test the device
- Ready to copy into other projects

**Example Folder Names:**
- `Ultrasonic_component` → HC-SR04 distance sensor
- `DHT11_component` → Temperature and humidity sensor
- `Servo_component` → Servo motor control
- `Relay_component` → Relay module switching
- `LCD_I2C_component` → I2C LCD display
- `MotorDriver_component` → L298N motor driver
- `RFID_component` → RFID reader module
- `PIR_component` → Motion sensor
- `Joystick_component` → Analog joystick
- `Keypad_component` → Matrix keypad
- `RGB_LED_component` → RGB LED control
- `Stepper_component` → Stepper motor control
- `SoilMoisture_component` → Soil moisture sensor
- `LDR_component` → Light dependent resistor

---

### 3. `_example`

**Definition:** Tutorial-style learning projects with detailed explanations, extensive comments, and step-by-step guidance.

**Purpose:** Educational projects designed to teach concepts, best practices, or techniques.

**Characteristics:**
- 50-200 lines of code
- Heavy commenting and explanations
- May include circuit diagrams
- Teaching-focused structure

**Example Folder Names:**
- `LEDPatterns_example` → Different LED blinking patterns explained
- `ButtonDebounce_example` → Proper button debouncing techniques
- `PullupResistor_example` → Understanding pullup resistors
- `PWMBasics_example` → PWM concepts with LED dimming
- `SerialCommunication_example` → Serial communication tutorial
- `InterruptTiming_example` → Hardware vs software interrupts
- `StateManagement_example` → Managing program states
- `SensorCalibration_example` → Sensor reading and calibration
- `PowerSaving_example` → Low power techniques
- `MultiTasking_example` → Using millis() for multitasking
- `I2CCommunication_example` → I2C protocol explained
- `SPICommunication_example` → SPI protocol tutorial

---

### 4. `_program`

**Definition:** Small, standalone code that performs one complete task, possibly combining multiple components.

**Purpose:** Solve a specific problem independently with a focused goal.

**Characteristics:**
- 100-300 lines of code
- Single `.ino` file (usually)
- 1-3 components/sensors
- One primary function or task
- Self-contained solution

**Example Folder Names:**
- `WiFiScanner_esp32_program` → Scans and displays WiFi networks
- `SoilMoistureLogger_program` → Logs soil moisture with timestamps
- `TemperatureMonitor_program` → Monitors and alerts on temperature
- `MotorSpeedControl_program` → Controls motor based on sensor input
- `DistanceAlert_program` → Alerts when object is too close
- `LightSwitch_program` → Automatic light control based on LDR
- `ServoTester_program` → Tests servo motor range
- `DataLogger_program` → Logs sensor data to SD card
- `SimpleThermostat_program` → Basic temperature control system
- `ParkingSensor_program` → Ultrasonic parking distance indicator
- `WaterLevelMonitor_program` → Monitors and displays water level
- `TimerRelay_program` → Time-based relay switching

---

### 5. `_project`

**Definition:** Full applications or systems combining multiple programs, components, and functions into an integrated solution.

**Purpose:** Real-world solutions, complex Arduino applications, or complete systems.

**Characteristics:**
- 300+ lines of code
- Multiple files and folders
- 3+ components/sensors
- Multiple integrated functions
- May include external communication (WiFi, Bluetooth, etc.)
- Often has user interface

**Example Folder Names:**
- `AutomatedPlantWatering_project` → Monitors soil, controls pump, logs data
- `HomeAutomation_project` → Controls lights, fans, temperature via WiFi
- `WeatherStation_project` → Multi-sensor weather monitoring system
- `SmartDoorLock_project` → RFID + keypad + servo security system
- `RobotCar_project` → Motor control + sensors + remote control
- `SecuritySystem_project` → PIR + camera + alarm + notifications
- `GarageController_project` → Door control + sensors + mobile app
- `SmartGreenhouse_project` → Climate control + lighting + irrigation
- `EnergyMonitor_project` → Current sensing + data logging + display
- `AquariumController_project` → Temperature + lighting + feeding automation
- `SmartMirror_project` → Display + sensors + weather + calendar
- `BikeSpeedometer_project` → Speed + distance + display + data logging

---

### 6. `_library`

**Definition:** Reusable custom code libraries with `.h` and `.cpp` files that can be imported into other projects.

**Purpose:** Create modular, reusable code that simplifies complex functionality.

**Characteristics:**
- Contains `.h` (header) and `.cpp` (implementation) files
- Used with `#include` statements
- Abstracts complex operations
- Can be shared across projects

**Example Folder Names:**
- `MyServo_library` → Custom servo control library
- `SimpleLCD_library` → Simplified LCD functions
- `SensorFilter_library` → Noise filtering for sensors
- `EasyWiFi_library` → Simplified WiFi connection handling
- `TimerUtils_library` → Timer and scheduling utilities
- `DataBuffer_library` → Circular buffer implementation
- `PIDControl_library` → PID controller implementation
- `EasyEEPROM_library` → Simplified EEPROM operations
- `MovingAverage_library` → Moving average calculations
- `SimpleProtocol_library` → Custom communication protocol

---

## What to Include in Each Folder

Every folder should contain:

```
FolderName_category/
├── sketch.ino              # Main Arduino file (always named sketch.ino)
├── README.md               # Description, wiring, usage instructions
├── circuit.png             # Wiring diagram or circuit photo (if applicable)
├── libraries.txt           # List of required libraries with versions
└── additional files...     # Any supporting files
```

**README.md should include:**
- Brief description
- Required hardware
- Wiring diagram or connection details
- Required libraries (if any)
- Upload and usage instructions
- Expected behavior

---

## Quick Reference Table

| Category   | Complexity | Typical Lines | Components | Files | Purpose |
|------------|-----------|---------------|------------|-------|---------|
| snippet    | Very Low  | 10-30         | 0-1        | 1     | Learn one concept |
| component  | Low       | 30-100        | 1          | 1     | Control one device |
| example    | Low-Med   | 50-200        | 1-2        | 1     | Tutorial/teaching |
| program    | Medium    | 100-300       | 1-3        | 1-2   | Solve one task |
| project    | High      | 300+          | 3+         | 3+    | Complete system |
| library    | Varies    | 50-500+       | N/A        | 2+    | Reusable code |

---

## Finding Code Quickly

**Search by category:**
- Search `_snippet` → Find learning examples
- Search `_component` → Find reusable device code
- Search `_example` → Find tutorials
- Search `_program` → Find standalone solutions
- Search `_project` → Find complete systems
- Search `_library` → Find importable libraries

**Search by board:**
- Search `_esp32_` → ESP32-specific code
- Search `_nano_` → Arduino Nano code
- Search `_uno_` → Arduino Uno code

---

## Contributing

When adding new code to this collection:

1. **Choose the appropriate category** based on complexity and purpose
2. **Follow the naming convention**: `FolderName_[board]_category`
3. **Name your main file** `sketch.ino`
4. **Include a README.md** with:
   - Hardware requirements
   - Wiring instructions
   - Required libraries
   - Usage guide
5. **Add `libraries.txt`** listing all dependencies
6. **Include circuit diagrams** when helpful
7. **Use consistent style**: `BlinkLED_snippet` (PascalCase for folder name)

---

## Examples of Good Folder Names

✅ **Good:**
- `BlinkLED_snippet`
- `Ultrasonic_component`
- `WiFiSetup_esp32_example`
- `TemperatureLogger_nano_program`
- `SmartHome_project`
- `MyServo_library`

❌ **Avoid:**
- `blink` (no category)
- `LED-Blink_snippet` (use underscore, not hyphen in folder name)
- `wifi_scanner_program` (use PascalCase)
- `esp32WiFi_program` (board type should be separate: `WiFi_esp32_program`)

---

## Tips

- **Start small:** Begin with `_snippet` and `_component` folders to learn
- **Build up:** Combine components into `_program` folders
- **Create projects:** Integrate multiple programs into `_project` folders
- **Extract libraries:** When you reuse code, move it to `_library` folders
- **Document everything:** Future you will thank present you
- **Version libraries:** Note library versions in `libraries.txt` to avoid compatibility issues

---

**Happy coding! 🚀**
