# Python Serial Monitor

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![Python](https://img.shields.io/badge/python-3.6%2B-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

A lightweight, easy-to-use command-line serial monitor for Arduino, ESP32, and other microcontrollers. Perfect alternative to the Arduino IDE Serial Monitor with added features like timestamps and color-coded output.

**Developed by:** [Upendra237](https://github.com/Upendra237)  
**Code Development Assisted by:** Claude AI Sonnet 4.5

---

## 📑 Table of Contents

- [Features](#-features)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Examples](#-examples)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [License](#-license)

---

## ✨ Features

- 🔌 **Auto Port Detection** - Automatically detects all available serial ports
- ⚡ **Multiple Baud Rates** - Supports 9600 to 921600 baud (and custom rates)
- 📝 **Two-Way Communication** - Send and receive data in real-time
- ⏰ **Optional Timestamps** - Add timestamps to received data
- 🎨 **Color-Coded Output** - Easy-to-read colored terminal output
- 💻 **Cross-Platform** - Works on Windows, Linux, and macOS
- 🚀 **Lightweight** - Minimal dependencies, fast startup
- 🔍 **Detailed Port Info** - Shows port descriptions and hardware IDs
- 🛡️ **Error Handling** - Robust error handling with helpful messages
- ⌨️ **Simple Interface** - Easy-to-use CLI with clear prompts

---

## 📋 Requirements

### Software Requirements

- **Python 3.6 or higher**
- **pyserial library**

### Hardware Requirements

- Any device with a serial port (USB-to-Serial, Arduino, ESP32, etc.)
- USB cable for connection

### Supported Devices

✅ Arduino (Uno, Mega, Nano, etc.)  
✅ ESP32 / ESP8266  
✅ Raspberry Pi Pico  
✅ STM32  
✅ Any USB-to-Serial adapter  
✅ Custom microcontroller boards

---

## 🚀 Installation

### Step 1: Install Python

If you don't have Python installed:

**Windows:**
1. Download from [python.org](https://www.python.org/downloads/)
2. Run installer and check "Add Python to PATH"

**Linux/Ubuntu:**
```bash
sudo apt update
sudo apt install python3 python3-pip
```

**macOS:**
```bash
brew install python3
```

### Step 2: Install pyserial

```bash
pip install pyserial
```

Or if you're using Python 3:

```bash
pip3 install pyserial
```

### Step 3: Download the Script

**Option A: Clone the Repository**
```bash
git clone https://github.com/Upendra237/Arduino.git
cd Arduino/python-serial-monitor
```

**Option B: Download Directly**
1. Download `serial_monitor.py` from this repository
2. Save it to your preferred location

### Step 4: Verify Installation

```bash
python --version
pip show pyserial
```

---

## 📖 Usage

### Basic Usage

1. Connect your device (Arduino/ESP32) to your computer via USB
2. Run the script:

```bash
python serial_monitor.py
```

3. Follow the on-screen prompts:
   - Select your serial port (1, 2, 3, etc.)
   - Select baud rate (4 for 115200 - ESP32 default)
   - Choose whether to show timestamps (y/n)

4. Start monitoring!
   - View incoming data in real-time
   - Type messages and press Enter to send
   - Press Ctrl+C to exit

### Command Line

```bash
# Basic usage
python serial_monitor.py

# On Linux/Mac, you might need Python 3 explicitly
python3 serial_monitor.py
```

---

## 💡 Examples

### Example 1: Connecting to ESP32

```
╔════════════════════════════════════════════════════════════════╗
║                                                                ║
║            Python Serial Monitor - CLI v1.0.0                  ║
║                    Developed by Upendra237                     ║
║                                                                ║
╚════════════════════════════════════════════════════════════════╝

================================================================
  Available Serial Ports:
================================================================
1. COM3
   Description: USB Serial Port (COM3)
   Hardware ID: USB VID:PID=10C4:EA60 SER=0001

2. COM5
   Description: Silicon Labs CP210x USB to UART Bridge (COM5)
   Hardware ID: USB VID:PID=10C4:EA60 SER=01234567

================================================================

Select port number: 2

Common Baud Rates:
  1. 9600      (Standard)
  2. 19200
  3. 57600
  4. 115200    (ESP32 Default) ⭐
  5. 230400
  6. 460800
  7. 921600

  Or enter custom baud rate

Select baud rate: 4

Show timestamps? (y/n): y

Connecting to COM5 at 115200 baud...
✓ Connected successfully!
✓ Port: COM5
✓ Baud Rate: 115200

================================================================
  Live Data Stream (Press Ctrl+C to exit)
================================================================

[14:23:45.123] WiFi connected!
[14:23:45.456] IP: 192.168.1.100
[14:23:46.789] Sensor value: 23.5°C

Commands:
  - Type message and press Enter to send
  - Press Ctrl+C to disconnect and exit
```

### Example 2: Arduino Communication

**Arduino Code:**
```cpp
void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(command);
  }
  
  Serial.println("Hello from Arduino!");
  delay(1000);
}
```

**Python Serial Monitor:**
```
Select port number: 1
Select baud rate: 1
Show timestamps? (n): n

✓ Connected successfully!

Hello from Arduino!
Hello from Arduino!

test message
→ Sent: test message
Received: test message
Hello from Arduino!
```

### Example 3: Custom Baud Rate

```
Select baud rate: 250000

Use custom baud rate 250000? (y/n): y

Connecting to COM3 at 250000 baud...
✓ Connected successfully!
```

---

## 🔧 Troubleshooting

### Common Issues

#### Issue 1: "No serial ports found!"

**Causes:**
- Device not connected
- USB drivers not installed
- Device not recognized

**Solutions:**
1. **Check physical connection**
   - Try a different USB cable
   - Try a different USB port
   - Check if device powers on

2. **Install USB drivers**
   - **CH340/CH341**: Download from manufacturer
   - **CP210x**: Download from Silicon Labs
   - **FTDI**: Download from FTDI website

3. **Check Device Manager (Windows)**
   - Open Device Manager
   - Look under "Ports (COM & LPT)"
   - If device shows with yellow warning, update driver

4. **Linux permissions**
   ```bash
   sudo usermod -a -G dialout $USER
   # Log out and back in
   ```

#### Issue 2: "Connection failed: [Errno 16] Device is busy"

**Cause:** Port is already in use (Arduino IDE, another program)

**Solutions:**
- Close Arduino IDE Serial Monitor
- Close any other serial programs
- Unplug and replug device
- Restart computer if needed

#### Issue 3: Garbage Characters / Unreadable Output

**Cause:** Wrong baud rate

**Solution:**
- Check your Arduino/ESP32 code for `Serial.begin(XXXX)`
- Use the same baud rate in the monitor
- Common rates: 9600 (Arduino), 115200 (ESP32)

#### Issue 4: Permission Denied (Linux/Mac)

**Solution:**
```bash
# Add user to dialout group
sudo usermod -a -G dialout $USER

# Or run with sudo (not recommended)
sudo python3 serial_monitor.py

# Or change port permissions
sudo chmod 666 /dev/ttyUSB0
```

#### Issue 5: ModuleNotFoundError: No module named 'serial'

**Solution:**
```bash
pip install pyserial
# NOT "pip install serial" - that's a different package!
```

---

## 🎯 Tips & Best Practices

### 1. Finding the Right Port

**Windows:**
- Usually COM3, COM4, COM5, etc.
- Check Device Manager → Ports (COM & LPT)

**Linux:**
- Usually `/dev/ttyUSB0` or `/dev/ttyACM0`
- List all: `ls /dev/tty*`

**macOS:**
- Usually `/dev/cu.usbserial-*` or `/dev/cu.usbmodem-*`
- List all: `ls /dev/cu.*`

### 2. Choosing Baud Rate

| Device | Common Baud Rate |
|--------|------------------|
| Arduino Uno/Nano | 9600 |
| ESP32 | 115200 |
| ESP8266 | 115200 |
| Raspberry Pi Pico | 115200 |
| Custom Projects | Check your code |

### 3. Timestamps

- Enable timestamps for debugging
- Useful for timing analysis
- Shows millisecond precision

### 4. Sending Commands

- Type and press Enter
- Newline character (`\n`) is automatically added
- Arduino: Use `Serial.readStringUntil('\n')`

---

## 🆚 Comparison with Arduino IDE Serial Monitor

| Feature | Python Serial Monitor | Arduino IDE Monitor |
|---------|----------------------|---------------------|
| Startup Speed | ⚡ Very Fast | Slower (IDE launch) |
| Timestamps | ✅ Built-in | ❌ No |
| Color Output | ✅ Yes | ❌ No |
| Cross-Platform | ✅ Yes | ✅ Yes |
| Custom Baud Rates | ✅ Easy | ⚠️ Limited |
| Port Auto-Detection | ✅ Yes | ⚠️ Manual |
| Lightweight | ✅ Yes | ❌ Full IDE |
| Plotter | ❌ No | ✅ Yes |
| Auto-Scroll | ✅ Yes | ✅ Yes |

---

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

### Ways to Contribute

1. **Report Bugs**
   - Open an issue with detailed description
   - Include error messages and steps to reproduce
   - Mention your OS and Python version

2. **Suggest Features**
   - Open a feature request
   - Explain the use case
   - Provide examples if possible

3. **Submit Pull Requests**
   - Fork the repository
   - Create a feature branch
   - Make your changes
   - Test thoroughly
   - Submit PR with clear description

4. **Improve Documentation**
   - Fix typos
   - Add examples
   - Improve explanations
   - Translate to other languages

### Development Setup

```bash
# Clone repository
git clone https://github.com/Upendra237/Arduino.git
cd Arduino/python-serial-monitor

# Create virtual environment (optional)
python -m venv venv
source venv/bin/activate  # Linux/Mac
venv\Scripts\activate     # Windows

# Install dependencies
pip install pyserial

# Make changes and test
python serial_monitor.py
```

---

## 📄 License

This project is licensed under the **MIT License**.

```
MIT License

Copyright (c) 2024 Upendra237

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

## 👨‍💻 Author

**Upendra237**

- GitHub: [@Upendra237](https://github.com/Upendra237)
- Repository: [Arduino/python-serial-monitor](https://github.com/Upendra237/Arduino/tree/main/python-serial-monitor)

---

## 🙏 Acknowledgments

- **Claude AI Sonnet 4.5** - Code development assistance and optimization
- **PySerial Team** - For the excellent serial communication library
- **Arduino/ESP32 Community** - For inspiration and support
- **All Contributors** - Thank you for your contributions!

---

## 🔮 Future Enhancements

Planned features for future releases:

- [ ] Data logging to file (CSV/TXT)
- [ ] Hex view mode
- [ ] Serial plotter functionality
- [ ] Multiple port monitoring
- [ ] Configuration file support
- [ ] Custom send/receive formatting
- [ ] Baud rate auto-detection
- [ ] Web interface option
- [ ] Plugin system for custom protocols
- [ ] Auto-reconnect on disconnect

Have a feature request? [Open an issue](https://github.com/Upendra237/Arduino/issues)!

---

## 📊 Project Stats

- **Language:** Python
- **Dependencies:** pyserial
- **Lines of Code:** ~250
- **Version:** 1.0.0
- **License:** MIT
- **Status:** Active Development

---

## 🔗 Related Projects

- [Arduino CLI](https://github.com/arduino/arduino-cli) - Arduino command line interface
- [PlatformIO](https://platformio.org/) - Professional development platform
- [ESP-IDF](https://github.com/espressif/esp-idf) - Official ESP32 framework

---

## ⭐ Show Your Support

If you find this project helpful, please consider:

- ⭐ Starring the repository
- 🐛 Reporting bugs
- 💡 Suggesting features
- 🔧 Contributing code
- 📢 Sharing with others

---

## 📞 Support

Need help? Here's how to get support:

1. **Read the Documentation** - Check this README thoroughly
2. **Troubleshooting Section** - Common issues and solutions above
3. **Search Issues** - Someone might have had the same problem
4. **Open an Issue** - Create a new issue with details

### When Reporting Issues

Please include:
- Operating System (Windows 10, Ubuntu 22.04, macOS 13, etc.)
- Python version (`python --version`)
- Error messages (full text)
- Steps to reproduce
- Device type (Arduino, ESP32, etc.)

---

<div align="center">

### Made with ❤️ by Upendra237

**Code Development Assisted by Claude AI Sonnet 4.5**

[⬆ Back to Top](#python-serial-monitor)

</div>

---

**Last Updated:** December 2024  
**Repository:** [https://github.com/Upendra237/Arduino/tree/main/python-serial-monitor](https://github.com/Upendra237/Arduino/tree/main/python-serial-monitor)