# ESP32 Robust WiFi Connection

![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)
![Platform](https://img.shields.io/badge/platform-ESP32-orange.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Arduino](https://img.shields.io/badge/Arduino-Compatible-00979D.svg)

Ultra-reliable WiFi connection manager for ESP32 that **never gives up**. Perfect for IoT projects requiring persistent internet connectivity with automatic reconnection and comprehensive monitoring.

**Developed by:** [Upendra237](https://github.com/Upendra237)  
**Code Development Assisted by:** Claude AI Sonnet 4.5

---

## ✨ Features

🔌 **Auto-Connect** - Connects to WiFi automatically on startup  
🔄 **Auto-Reconnect** - Reconnects automatically when connection drops  
💡 **LED Indicator** - Visual status (solid=connected, blink=disconnected)  
📊 **Detailed Monitoring** - Signal strength, uptime, connection stats  
🛡️ **Error Handling** - Comprehensive error detection and diagnosis  
⏱️ **Never Gives Up** - Keeps trying to connect indefinitely  
🎯 **Production Ready** - Optimized for reliability and stability  

---

## 📋 Requirements

### Hardware
- ESP32 Development Board (any variant)
- USB Cable
- WiFi Network (2.4GHz)

### Software
- Arduino IDE 1.8.x+ or Arduino IDE 2.x
- ESP32 Board Support Package

---

## 🚀 Quick Start

### 1. Install Arduino IDE & ESP32 Support

**Install ESP32 Board Support:**
1. Open Arduino IDE → **File** → **Preferences**
2. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to **Tools** → **Board** → **Boards Manager**
4. Search "ESP32" and install "esp32 by Espressif Systems"

### 2. Configure WiFi Credentials

Open the code and change these lines:

```cpp
const char* WIFI_SSID = "YOUR_WIFI_SSID";        // Your WiFi name
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD"; // Your WiFi password
```

### 3. Upload

1. Select your ESP32 board: **Tools** → **Board** → **ESP32 Arduino** → [Your Board]
2. Select COM port: **Tools** → **Port** → [Your Port]
3. Click **Upload** button
4. Open Serial Monitor: **Tools** → **Serial Monitor** (115200 baud)

---

## 💡 Usage

### Serial Monitor Output

```
╔════════════════════════════════════════════╗
║   ESP32 Robust WiFi Connection v1.0.0     ║
║         Developed by Upendra237           ║
╚════════════════════════════════════════════╝

SYSTEM INFORMATION
  Chip Model: ESP32-D0WDQ6
  CPU Frequency: 240 MHz
  MAC Address: AA:BB:CC:DD:EE:FF

WiFi CONFIGURATION
  Target SSID: MyHomeWiFi
  Auto-Reconnect: ENABLED ✓

→ Connecting to MyHomeWiFi...

╔════════════════════════════════════════════╗
║     ✓✓✓ CONNECTED SUCCESSFULLY! ✓✓✓      ║
╚════════════════════════════════════════════╝

📡 Network Information:
   IP Address: 192.168.1.100
   Gateway: 192.168.1.1
   Signal Strength: -45 dBm (90% Excellent ★★★★★)

🌐 WiFi is ONLINE and READY!
```

### LED Indicator

| LED Status | Meaning |
|------------|---------|
| **Solid ON** | Connected to WiFi ✓ |
| **Slow Blink** (1 Hz) | Disconnected, attempting to reconnect |
| **Fast Blink** | Connection failed, retrying soon |

---

## 🔧 Configuration

Adjust these settings in the code:

```cpp
#define CONNECTION_TIMEOUT 20000    // Max wait per attempt (20s)
#define CHECK_INTERVAL 5000         // Check connection every 5s
#define RETRY_DELAY 3000            // Wait before retry (3s)
#define LED_BUILTIN 2               // LED pin (GPIO 2)
```

---

## 📊 What It Displays

### On Connection Success:
- ✅ IP Address, Gateway, Subnet, DNS
- ✅ MAC Address, BSSID, Channel
- ✅ Signal Strength with quality rating (★★★★★)
- ✅ Connection time and attempt count
- ✅ Uptime tracking

### On Connection Failure:
- ❌ Error diagnosis (SSID not found, wrong password, etc.)
- ❌ Troubleshooting suggestions
- ❌ Automatic retry countdown

### Periodic Updates (Every 5s):
- Status line with IP, signal strength, and uptime

---

## 🎯 How It Works

1. **Startup** → Initializes WiFi with optimal settings
2. **Connect** → Attempts connection with timeout
3. **Monitor** → Checks connection every 5 seconds
4. **Detect** → Detects disconnection immediately
5. **Reconnect** → Automatically reconnects on failure
6. **Repeat** → Never stops trying to maintain connection

### Connection Flow

```
[Start] → [Connect] → [Success?] 
                          ↓ Yes
                    [Monitor] → [Still Connected?]
                          ↓ No         ↓ Yes
                    [Reconnect] ← [Continue Monitoring]
```

---

## 🔍 Troubleshooting

### Connection Fails: "SSID NOT FOUND"

**Solutions:**
- ✓ Check SSID spelling (case-sensitive!)
- ✓ Ensure router is powered on
- ✓ Move ESP32 closer to router
- ✓ ESP32 only supports 2.4GHz WiFi (not 5GHz)

### Connection Fails: "WRONG PASSWORD"

**Solutions:**
- ✓ Verify password is correct
- ✓ Check for extra spaces in password
- ✓ Ensure security type is WPA/WPA2 (not WPA3 only)

### Frequent Disconnections

**Solutions:**
- ✓ Check signal strength (aim for > -70 dBm)
- ✓ Use stable power supply (not weak USB port)
- ✓ Update router firmware
- ✓ Change WiFi channel to less congested one

### Serial Monitor Shows Garbage

**Solutions:**
- ✓ Set baud rate to **115200**
- ✓ Check USB cable quality
- ✓ Press ESP32 reset button

---

## 📱 Example Projects

Perfect for:
- 🌡️ IoT Temperature Monitors
- 📹 Security Cameras
- 🏡 Home Automation
- 📊 Data Loggers
- 🔔 Smart Notifications
- 🌐 Web Servers
- 📡 MQTT Clients

---

## 🆚 Why Use This?

| Feature | This Code | Basic WiFi.begin() |
|---------|-----------|-------------------|
| Auto-reconnect | ✅ Always | ❌ Manual |
| Error diagnosis | ✅ Detailed | ❌ None |
| Status monitoring | ✅ Continuous | ❌ Manual |
| LED indicator | ✅ Built-in | ❌ Manual |
| Connection stats | ✅ Full details | ❌ Limited |
| Never gives up | ✅ Yes | ❌ No |

---

## 🤝 Contributing

Contributions welcome! Feel free to:
- 🐛 Report bugs
- 💡 Suggest features
- 🔧 Submit pull requests
- 📖 Improve documentation

---

## 📄 License

MIT License - see [LICENSE](LICENSE) file for details.

---

## 👨‍💻 Author

**Upendra237**
- GitHub: [@Upendra237](https://github.com/Upendra237)
- Repository: [Arduino/esp32-robust-wifi-connection](https://github.com/Upendra237/Arduino/tree/main/esp32-robust-wifi-connection)

---

## 🙏 Acknowledgments

- **Claude AI Sonnet 4.5** - Code development assistance
- **Espressif Systems** - ESP32 platform and libraries
- **Arduino Community** - Continuous support

---

## 🔮 Future Enhancements

- [ ] Web-based configuration portal
- [ ] Multiple WiFi credentials support
- [ ] OTA firmware updates
- [ ] MQTT integration example
- [ ] Deep sleep management
- [ ] Connection quality logging

---

## 📞 Support

Need help? 
1. Check [Troubleshooting](#-troubleshooting) section
2. Review code comments
3. Open an issue on GitHub

---

<div align="center">

### Made with ❤️ by Upendra237

**Code Development Assisted by Claude AI Sonnet 4.5**

⭐ Star this repo if you find it helpful!

[⬆ Back to Top](#esp32-robust-wifi-connection)

</div>

---

**Last Updated:** December 2024