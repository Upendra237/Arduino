# ESP32 Ultimate WiFi Toolkit

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-orange.svg)
![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D.svg)

A comprehensive WiFi management and testing toolkit for ESP32 development boards. Perfect for network diagnostics, connectivity testing, and WiFi development projects.

**Developed by:** [Upendra237](https://github.com/Upendra237)  
**Code Development Assisted by:** Claude AI Sonnet 4.5

---

## 📑 Table of Contents

- [Features](#-features)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Command Reference](#-command-reference)
- [Examples](#-examples)
- [Signal Strength Guide](#-signal-strength-guide)
- [Troubleshooting](#-troubleshooting)
- [Contributing](#-contributing)
- [License](#-license)
- [Author](#-author)
- [Acknowledgments](#-acknowledgments)

---

## ✨ Features

### 🔍 Network Scanning
- **Quick Scan**: Fast network discovery with signal strength indicators
- **Detailed Scan**: In-depth network information including BSSID, channel, encryption type
- **Real-time Signal Quality**: Visual signal strength ratings (★★★★★)
- **Smart Indicators**: Shows saved and currently connected networks

### 🌐 WiFi Management
- **Easy Connection**: Simple command-based WiFi connection with password support
- **Auto-Reconnect**: Automatic reconnection on connection loss
- **Saved Credentials**: Remember last connected network
- **Connection Status**: Comprehensive status monitoring with uptime tracking
- **Manual Disconnect**: Clean disconnection from networks
- **Quick Reconnect**: One-command reconnection to saved network

### 📊 Network Diagnostics
- **Signal Monitoring**: Real-time RSSI (Received Signal Strength Indicator) and quality percentage
- **Speed Estimation**: Connection speed estimates based on signal strength
- **Ping Test**: Gateway connectivity testing
- **IP Configuration**: Complete network configuration display (IP, Gateway, Subnet, DNS)
- **Channel Information**: Current WiFi channel display
- **Connection Uptime**: Track how long you've been connected

### 💻 System Information
- **Chip Details**: ESP32 model, revision, cores, frequency
- **Memory Stats**: Flash size, speed, and free heap monitoring
- **Uptime Tracking**: System and connection uptime
- **MAC Address**: Device identification and networking info

### 🛠️ Advanced Features
- **Power Management**: WiFi TX power and sleep mode information
- **Auto-Reconnect Toggle**: Enable/disable automatic reconnection
- **Interactive CLI**: User-friendly command-line interface with command history
- **Serial Communication Test**: Verify serial connection functionality
- **System Restart**: Remote ESP32 restart capability
- **Screen Clear**: Clean terminal interface

### 🎨 User Experience
- **Beautiful UI**: Box-drawing characters and symbols for professional look
- **Color Indicators**: ✓ and ✗ symbols for quick status recognition
- **Smart Prompts**: Clear command prompts and feedback
- **Error Messages**: Helpful error messages with solutions
- **Command Shortcuts**: Short aliases for frequently used commands

---

## 📋 Requirements

### Hardware
- **ESP32 Development Board** (any variant):
  - ESP32-WROOM-32
  - ESP32-DevKitC
  - ESP32-WROVER
  - NodeMCU-32S
  - Any other ESP32-based board
- **USB Cable** (for programming and serial communication)
- **Computer** with USB port

### Software
- **Arduino IDE** 1.8.x or later (or Arduino IDE 2.x)
- **ESP32 Board Support Package**
- **Serial Monitor** or any serial terminal (PuTTY, Tera Term, etc.)

### Recommended
- Stable power supply (USB or external)
- Good quality USB cable for reliable communication

---

## 🚀 Installation

### Step 1: Install Arduino IDE

1. Download Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install the IDE following the installer instructions
3. Launch Arduino IDE

### Step 2: Install ESP32 Board Support

1. Open Arduino IDE
2. Go to **File → Preferences**
3. In "Additional Board Manager URLs" field, add:
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Click **OK**
5. Go to **Tools → Board → Boards Manager**
6. Search for **"ESP32"**
7. Install **"esp32 by Espressif Systems"** (latest version)
8. Wait for installation to complete

### Step 3: Download the Code

**Option A: Clone the Repository**
```bash
git clone https://github.com/Upendra237/ESP32.git
cd "Ultimate WiFi Toolkit"
```

**Option B: Download ZIP**
1. Click the green "Code" button on GitHub
2. Select "Download ZIP"
3. Extract the ZIP file to your desired location

### Step 4: Configure Arduino IDE

1. Connect your ESP32 board to your computer via USB
2. In Arduino IDE:
   - Go to **Tools → Board → ESP32 Arduino**
   - Select your specific ESP32 board (e.g., "ESP32 Dev Module")
3. Go to **Tools → Port**
   - Select the COM port showing your ESP32 (e.g., COM3, COM4, or /dev/ttyUSB0 on Linux)
4. Set other parameters (if needed):
   - **Upload Speed**: 115200
   - **Flash Frequency**: 80MHz
   - **Flash Mode**: QIO
   - **Flash Size**: 4MB (or your board's size)

### Step 5: Upload the Code

1. Open the `.ino` file in Arduino IDE
2. Click the **Verify** button (✓) to compile and check for errors
3. Click the **Upload** button (→) to upload to your ESP32
4. Wait for "Done uploading" message

### Step 6: Open Serial Monitor

1. Go to **Tools → Serial Monitor** (or press Ctrl+Shift+M)
2. Set the baud rate to **115200** in the bottom-right corner
3. Set line ending to **"Both NL & CR"** or **"Newline"**
4. You should see the welcome screen:

```
╔══════════════════════════════════════════════╗
║    ESP32 Ultimate WiFi Toolkit v1.0.0      ║
║         Developed by Upendra237             ║
╚══════════════════════════════════════════════╝
```

---

## 📖 Usage

### Getting Started

After uploading the code and opening the Serial Monitor, you'll see a command prompt:

```
wifi>
```

Type any command and press Enter. Start with the `help` command to see all available options.

### Basic Workflow

1. **Scan for networks**: `scan`
2. **Connect to WiFi**: `connect YourSSID YourPassword`
3. **Check status**: `status`
4. **Test connection**: `ping` or `speed`

---

## 🎯 Command Reference

### Basic Commands

| Command | Shortcut | Description | Example |
|---------|----------|-------------|---------|
| `help` | `h`, `?` | Show help menu with all commands | `help` |
| `version` | `v` | Display version information | `version` |
| `info` | `i` | Show detailed system information | `info` |
| `test` | - | Test serial communication | `test` |
| `clear` | `cls` | Clear the screen | `clear` |
| `restart` | `reboot` | Restart the ESP32 | `restart` |

### Network Scanning

| Command | Shortcut | Description | Example |
|---------|----------|-------------|---------|
| `scan` | `s` | Quick scan showing nearby networks | `scan` |
| `scandetail` | `sd` | Detailed scan with full network info | `scandetail` |

### WiFi Connection

| Command | Format | Description | Example |
|---------|--------|-------------|---------|
| `connect` | `connect <ssid> <password>` | Connect to WiFi network | `connect MyWiFi password123` |
| | | Connect with spaces in SSID | `connect "My WiFi" pass123` |
| `disconnect` | `d` | Disconnect from current network | `disconnect` |
| `reconnect` | `r` | Reconnect to saved network | `reconnect` |
| `autoreconnect` | - | Toggle auto-reconnect feature | `autoreconnect on` |
| | | | `autoreconnect off` |

### Network Status & Information

| Command | Shortcut | Description | Example |
|---------|----------|-------------|---------|
| `status` | `st` | Full connection status with all details | `status` |
| `ip` | - | Display IP configuration (IP, Gateway, Subnet, DNS) | `ip` |
| `mac` | - | Show MAC address | `mac` |
| `signal` | `rssi` | Display signal strength and quality | `signal` |
| `channel` | - | Show current WiFi channel | `channel` |
| `power` | - | Display WiFi power settings | `power` |

### Network Testing

| Command | Description | Example |
|---------|-------------|---------|
| `ping` | Test connectivity to gateway | `ping` |
| `speed` | Estimate connection speed based on signal | `speed` |

---

## 💡 Examples

### Example 1: Scanning Networks

```
wifi> scan

→ Scanning WiFi networks...
  Found 5 networks:

  #  | Signal | Enc | SSID
  ---|--------|-----|--------------------------------
  1  | -42★★★ | Sec  | HomeNetwork
  2  | -55★★  | Sec  | OfficeWiFi
  3  | -67★   | Sec  | CafeWiFi
  4  | -73    | Open | GuestNetwork
  5  | -82    | Sec  | NeighborWiFi

wifi>
```

### Example 2: Detailed Network Scan

```
wifi> scandetail

→ Detailed WiFi Scan...
  Found 3 networks:

  ┌─────────────────────────────────────
  │ Network #1
  │ SSID: HomeNetwork
  │ BSSID: AA:BB:CC:DD:EE:FF
  │ Signal: -42 dBm (84%)
  │ Channel: 6
  │ Security: WPA2-PSK
  ┌─────────────────────────────────────
  │ Network #2
  │ SSID: OfficeWiFi
  │ BSSID: 11:22:33:44:55:66
  │ Signal: -55 dBm (70%)
  │ Channel: 11
  │ Security: WPA2-PSK
  └─────────────────────────────────────

wifi>
```

### Example 3: Connecting to WiFi

```
wifi> connect HomeNetwork MyPassword123

→ Attempting connection...
  SSID: 'HomeNetwork'
  Password length: 15

  Status: ..........

  Final Status: CONNECTED

╔════════════════════════════════════════════╗
║     ✓ Connected Successfully!             ║
╚════════════════════════════════════════════╝
  SSID: HomeNetwork
  IP: 192.168.1.150
  Gateway: 192.168.1.1
  Signal: -42 dBm
  Channel: 6
  Connection Time: 3847 ms

wifi>
```

### Example 4: Checking Connection Status

```
wifi> status

╔════════════════════════════════════════════╗
║         Connection Status                 ║
╚════════════════════════════════════════════╝

  Status: ✓ Connected
  SSID: HomeNetwork
  BSSID: AA:BB:CC:DD:EE:FF
  IP: 192.168.1.150
  Gateway: 192.168.1.1
  Subnet: 255.255.255.0
  DNS: 192.168.1.1
  Signal: -42 dBm (84%)
  Channel: 6
  MAC: AA:BB:CC:11:22:33
  Auto-Reconnect: ON
  Uptime: 2h 15m 30s

wifi>
```

### Example 5: Testing Connection

```
wifi> signal

  Signal Strength: -45 dBm
  Quality: 90%
  Rating: Excellent ★★★★★

wifi> ping

→ Pinging gateway...
  Gateway: 192.168.1.1
  ✓ Gateway reachable

wifi> speed

→ Connection Speed Test
  Signal: -45 dBm
  Channel: 6
  Estimated Speed: ~150 Mbps
  (Actual speed depends on router and network load)

wifi>
```

### Example 6: System Information

```
wifi> info

╔════════════════════════════════════════════╗
║         System Information                ║
╚════════════════════════════════════════════╝

  Chip: ESP32-D0WDQ6
  Revision: 1
  Cores: 2
  CPU Freq: 240 MHz
  Flash Size: 4 MB
  Flash Speed: 40 MHz
  Free Heap: 285 KB
  MAC Address: AA:BB:CC:11:22:33
  Uptime: 1h 23m 45s

  Developed by: Upendra237
  Version: 1.0.0

wifi>
```

### Example 7: Auto-Reconnect Feature

```
wifi> autoreconnect on
✓ Auto-reconnect enabled

wifi> disconnect
✓ Disconnected from WiFi

[After 5 seconds if connection drops]

✗ WiFi Disconnected!
→ Auto-reconnecting...

✓ WiFi Connected!

wifi>
```

---

## 🎯 Signal Strength Guide

Understanding your WiFi signal quality:

| RSSI (dBm) | Quality % | Rating | Symbol | Description |
|------------|-----------|--------|--------|-------------|
| -30 to -50 | 90-100% | Excellent | ★★★★★ | Perfect signal - ideal for all activities |
| -50 to -60 | 80-90% | Good | ★★★★ | Great signal - suitable for streaming & gaming |
| -60 to -70 | 60-80% | Fair | ★★★ | Decent signal - good for browsing & email |
| -70 to -80 | 40-60% | Weak | ★★ | Weak signal - may experience slowdowns |
| -80 to -90 | 20-40% | Very Weak | ★ | Very weak - connection issues likely |
| Below -90 | 0-20% | No Signal | - | Unusable - too weak to maintain connection |

### Tips for Better Signal:
- **Move closer to router** - Physical distance matters
- **Remove obstacles** - Walls and metal objects block signals
- **Change channels** - Less congested channels perform better
- **Update router firmware** - Latest firmware improves performance
- **Use 5GHz** - If available, 5GHz offers better speeds with less interference

---

## 🔧 Troubleshooting

### Connection Issues

#### Problem: "SSID NOT FOUND"
**Possible Causes:**
- SSID is spelled incorrectly (case-sensitive!)
- Network is out of range
- Network is hidden
- Router is turned off

**Solutions:**
1. Run `scan` to see available networks
2. Verify exact spelling and capitalization
3. Move closer to the router
4. Check if router is powered on
5. For hidden networks, ensure SSID is typed exactly

#### Problem: "CONNECTION FAILED (Wrong password?)"
**Possible Causes:**
- Incorrect password
- Extra spaces in password
- Wrong security type

**Solutions:**
1. Double-check password (case-sensitive)
2. Remove quotes unless SSID/password contains spaces
3. Ensure no extra spaces before/after password
4. Verify router security settings

#### Problem: Frequent Disconnections
**Possible Causes:**
- Weak signal
- Router issues
- Network congestion
- Power supply problems

**Solutions:**
1. Check signal strength with `signal` command
2. Move ESP32 closer to router
3. Enable auto-reconnect: `autoreconnect on`
4. Use better power supply
5. Try different WiFi channel

#### Problem: Auto-reconnect Not Working
**Solutions:**
1. Enable feature: `autoreconnect on`
2. Verify credentials are saved: `status`
3. Check if SSID is still available: `scan`
4. Restart ESP32: `restart`

---

### Serial Monitor Issues

#### Problem: Garbage Characters or Unreadable Text
**Solutions:**
1. Set baud rate to **115200**
2. Check USB cable quality
3. Try different USB port
4. Verify ESP32 is not in boot mode

#### Problem: No Output in Serial Monitor
**Solutions:**
1. Check USB cable connection
2. Verify correct COM port selected
3. Press **Reset** button on ESP32
4. Check if board is properly powered
5. Try different USB cable
6. Reinstall USB drivers

#### Problem: Commands Not Working
**Solutions:**
1. Check line ending setting (use "Both NL & CR" or "Newline")
2. Ensure caps lock is off (most commands are lowercase)
3. Type carefully - watch for typos
4. Use `test` command to verify communication

---

### Upload Issues

#### Problem: "Failed to connect to ESP32"
**Solutions:**
1. Press and hold **BOOT** button while uploading
2. Check USB cable and port
3. Lower upload speed (Tools → Upload Speed → 115200)
4. Install/update USB drivers (CP210x or CH340)
5. Try different USB port or cable

#### Problem: "Chip does not support flash size"
**Solutions:**
1. Go to **Tools → Flash Size**
2. Select correct size (usually 4MB)
3. Try "4MB (32Mb)" option

---

### Performance Issues

#### Problem: Slow Connection Speeds
**Causes & Solutions:**
1. **Weak signal** - Check with `signal`, move closer to router
2. **Network congestion** - Try different channel
3. **Router limitations** - Check router specifications
4. **Interference** - Remove obstacles, avoid 2.4GHz interference

#### Problem: High Memory Usage
**Solutions:**
1. Check free heap: `info` command
2. Restart ESP32 if heap is low: `restart`
3. Avoid very long scan sessions

---

## 🤝 Contributing

Contributions are welcome and appreciated! Here's how you can help:

### Ways to Contribute

1. **Report Bugs**
   - Use the GitHub Issues tab
   - Provide detailed description
   - Include steps to reproduce
   - Mention your ESP32 board model

2. **Suggest Features**
   - Open a feature request issue
   - Explain the use case
   - Provide examples if possible

3. **Submit Pull Requests**
   - Fork the repository
   - Create a feature branch
   - Make your changes
   - Test thoroughly
   - Submit PR with clear description

4. **Improve Documentation**
   - Fix typos or unclear sections
   - Add more examples
   - Translate to other languages

5. **Share Your Projects**
   - Show how you're using this toolkit
   - Share modifications or extensions
   - Help other users in discussions

### Development Guidelines

- Follow existing code style
- Comment your code
- Test on real hardware
- Update README if adding features
- Keep commits atomic and clear

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
- Project Link: [https://github.com/Upendra237/ESP32](https://github.com/Upendra237/ESP32)

---

## 🙏 Acknowledgments

### Special Thanks

- **Claude AI Sonnet 4.5** - Code development assistance and optimization
- **Espressif Systems** - For the amazing ESP32 platform and Arduino core
- **Arduino Community** - For continuous support and libraries
- **Open Source Contributors** - For inspiration and code examples
- **All Users and Testers** - For feedback and bug reports

### Technologies Used

- **ESP32 Arduino Core** - ESP32 framework for Arduino IDE
- **WiFi Library** - ESP32 WiFi functionality
- **Arduino IDE** - Development environment

### Inspiration

This project was created to provide an easy-to-use WiFi management tool for ESP32 developers, students, and hobbyists. It aims to make WiFi connectivity testing and debugging more accessible and user-friendly.

---

## 📝 Version History

### v1.0.0 (Current Release)
**Release Date:** December 2024

**Features:**
- ✅ Full-featured WiFi toolkit with interactive CLI
- ✅ Network scanning (quick and detailed modes)
- ✅ Easy WiFi connection with password support
- ✅ Auto-reconnect functionality
- ✅ Comprehensive connection status monitoring
- ✅ Network diagnostics tools (ping, speed test)
- ✅ System information display
- ✅ Signal strength monitoring with quality indicators
- ✅ Power management information
- ✅ Connection uptime tracking
- ✅ Command shortcuts for faster access
- ✅ Beautiful CLI with box-drawing characters
- ✅ Helpful error messages and troubleshooting

---

## 🔮 Future Enhancements

### Planned Features

- [ ] **Multiple Network Profiles** - Save and manage multiple WiFi credentials
- [ ] **WiFi Access Point Mode** - Turn ESP32 into WiFi hotspot
- [ ] **Web-based Configuration** - Configure via browser interface
- [ ] **JSON Configuration Files** - Import/export settings
- [ ] **Advanced Ping Statistics** - Detailed latency measurements
- [ ] **Network Packet Analysis** - Monitor network traffic
- [ ] **WPS Connection Support** - Push-button WiFi setup
- [ ] **MQTT Testing** - Test MQTT broker connectivity
- [ ] **HTTP Request Testing** - Test API endpoints
- [ ] **DNS Lookup Tool** - Resolve domain names
- [ ] **Port Scanner** - Scan for open ports
- [ ] **Network Speed Test** - Real bandwidth measurement
- [ ] **OTA Updates** - Over-the-air firmware updates
- [ ] **Data Logging** - Save connection history to SD card
- [ ] **Email Notifications** - Alert on connection issues
- [ ] **Mobile App** - Control via smartphone

### Community Requests

Have an idea? Open an issue on GitHub with the "enhancement" label!

---

## 📊 Project Stats

- **Language:** C++ (Arduino)
- **Platform:** ESP32
- **License:** MIT
- **Version:** 1.0.0
- **Status:** Active Development

---

## 🌟 Show Your Support

If you find this project helpful, please consider:

⭐ **Starring** the repository on GitHub  
🐛 **Reporting** bugs and issues  
💡 **Suggesting** new features  
🔧 **Contributing** code improvements  
📢 **Sharing** with others who might benefit

---

## 📞 Support

Need help? Here's how to get support:

1. **Check Documentation** - Read this README thoroughly
2. **Search Issues** - Someone might have had the same problem
3. **Troubleshooting Guide** - Check the troubleshooting section above
4. **Open an Issue** - Create a new issue on GitHub with details
5. **Community Discussions** - Join discussions on GitHub

### When Reporting Issues

Please include:
- ESP32 board model
- Arduino IDE version
- Error messages (full text)
- Steps to reproduce
- Serial Monitor output
- What you've already tried

---

## 🔗 Useful Links

- [ESP32 Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [ESP32 Official Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Arduino IDE Download](https://www.arduino.cc/en/software)
- [ESP32 Forum](https://esp32.com/)

---

<div align="center">

### Made with ❤️ by Upendra237

**Code Development Assisted by Claude AI Sonnet 4.5**

[⬆ Back to Top](#esp32-ultimate-wifi-toolkit)

</div>

---

**Last Updated:** December 2024  
**Repository:** [https://github.com/Upendra237/ESP32](hhttps://github.com/Upendra237/ESP32)