/*
 * ═══════════════════════════════════════════════════════════════
 *  ESP32 Ultimate WiFi Toolkit
 * ═══════════════════════════════════════════════════════════════
 *  Version: 1.0.0
 *  Developed by: Upendra237
 *  GitHub: https://github.com/Upendra237
 * 
 *  Description:
 *  Complete WiFi management and testing toolkit for ESP32.
 *  Features network scanning, connection management, diagnostics,
 *  and real-time monitoring with an interactive CLI.
 * 
 *  Hardware Required:
 *  - ESP32 Development Board (any variant)
 *  - USB Cable
 * 
 *  Serial Monitor Settings:
 *  - Baud Rate: 115200
 *  - Line Ending: Both NL & CR (or Newline)
 * ═══════════════════════════════════════════════════════════════
 */

#include <WiFi.h>

// ═══════════════════════════════════════════════════════════════
// CONFIGURATION
// ═══════════════════════════════════════════════════════════════

#define VERSION "1.0.0"
#define SERIAL_BAUD 115200

// Connection timeout and check intervals (milliseconds)
const int MAX_CONNECT_TIME = 10000;   // Maximum time to wait for connection
const int CHECK_INTERVAL = 5000;      // Interval to check connection status

// ═══════════════════════════════════════════════════════════════
// GLOBAL VARIABLES
// ═══════════════════════════════════════════════════════════════

String savedSSID = "";                // Last connected SSID
String savedPassword = "";            // Last used password
String inputBuffer = "";              // Command input buffer

unsigned long lastCheck = 0;          // Last connection check time
unsigned long connectionStartTime = 0; // Connection start timestamp

bool wasConnected = false;            // Previous connection state
bool autoReconnect = true;            // Auto-reconnect flag

// ═══════════════════════════════════════════════════════════════
// SETUP
// ═══════════════════════════════════════════════════════════════

void setup() {
  // Initialize serial communication
  Serial.begin(SERIAL_BAUD);
  while(!Serial) {
    delay(10);
  }
  
  delay(1000);
  
  // Clear screen
  for(int i = 0; i < 5; i++) {
    Serial.println();
  }
  
  // Display welcome banner
  Serial.println("╔══════════════════════════════════════════════╗");
  Serial.println("║    ESP32 Ultimate WiFi Toolkit v" VERSION "      ║");
  Serial.println("║         Developed by Upendra237              ║");
  Serial.println("╚══════════════════════════════════════════════╝");
  Serial.println();
  
  // Display system information
  Serial.print("Chip: ");
  Serial.print(ESP.getChipModel());
  Serial.print(" | Cores: ");
  Serial.print(ESP.getChipCores());
  Serial.print(" | Freq: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");
  
  Serial.print("Flash: ");
  Serial.print(ESP.getFlashChipSize() / 1024 / 1024);
  Serial.print(" MB | Free Heap: ");
  Serial.print(ESP.getFreeHeap() / 1024);
  Serial.println(" KB");
  
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
  
  // Configure WiFi
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  WiFi.setAutoReconnect(autoReconnect);
  WiFi.persistent(false);
  
  Serial.println();
  Serial.println("Type 'help' or '?' for available commands");
  printPrompt();
}

// ═══════════════════════════════════════════════════════════════
// MAIN LOOP
// ═══════════════════════════════════════════════════════════════

void loop() {
  // Handle serial input
  handleSerialInput();
  
  // Periodic connection check
  checkConnectionStatus();
  
  delay(10);
}

// ═══════════════════════════════════════════════════════════════
// INPUT HANDLING
// ═══════════════════════════════════════════════════════════════

void handleSerialInput() {
  while (Serial.available() > 0) {
    char c = Serial.read();
    
    // Process newline (command complete)
    if (c == '\n' || c == '\r') {
      if (inputBuffer.length() > 0) {
        Serial.println();
        handleCommand(inputBuffer);
        inputBuffer = "";
        printPrompt();
      }
    }
    // Process backspace
    else if (c == 8 || c == 127) {
      if (inputBuffer.length() > 0) {
        inputBuffer.remove(inputBuffer.length() - 1);
        Serial.print("\b \b");
      }
    }
    // Process printable characters
    else if (c >= 32 && c <= 126) {
      inputBuffer += c;
      Serial.print(c);
    }
  }
}

// ═══════════════════════════════════════════════════════════════
// CONNECTION STATUS MONITORING
// ═══════════════════════════════════════════════════════════════

void checkConnectionStatus() {
  if (millis() - lastCheck > CHECK_INTERVAL) {
    lastCheck = millis();
    
    if (WiFi.status() == WL_CONNECTED) {
      if (!wasConnected) {
        wasConnected = true;
        Serial.println();
        Serial.println("✓ WiFi Connected!");
        printPrompt();
      }
    } else {
      if (wasConnected) {
        Serial.println();
        Serial.println("✗ WiFi Disconnected!");
        wasConnected = false;
        
        // Auto-reconnect if enabled
        if (autoReconnect && savedSSID.length() > 0) {
          Serial.println("→ Auto-reconnecting...");
          WiFi.begin(savedSSID.c_str(), savedPassword.c_str());
        }
        printPrompt();
      }
    }
  }
}

// ═══════════════════════════════════════════════════════════════
// COMMAND HANDLER
// ═══════════════════════════════════════════════════════════════

void handleCommand(String cmd) {
  cmd.trim();
  String originalCmd = cmd;
  cmd.toLowerCase();
  
  // Help commands
  if (cmd == "help" || cmd == "h" || cmd == "?") {
    showHelp();
  }
  // Network scanning
  else if (cmd == "scan" || cmd == "s") {
    scanNetworks();
  }
  else if (cmd == "scandetail" || cmd == "sd") {
    scanNetworksDetailed();
  }
  // Connection management
  else if (cmd.startsWith("connect ")) {
    String params = originalCmd.substring(8);
    connectCommand(params);
  }
  else if (cmd == "disconnect" || cmd == "d") {
    WiFi.disconnect();
    savedSSID = "";
    savedPassword = "";
    Serial.println("✓ Disconnected from WiFi");
  }
  else if (cmd == "reconnect" || cmd == "r") {
    reconnectWiFi();
  }
  // Status and information
  else if (cmd == "status" || cmd == "st") {
    showStatus();
  }
  else if (cmd == "ip") {
    showIP();
  }
  else if (cmd == "mac") {
    Serial.print("MAC Address: ");
    Serial.println(WiFi.macAddress());
  }
  else if (cmd == "signal" || cmd == "rssi") {
    showSignal();
  }
  else if (cmd == "channel") {
    showChannel();
  }
  else if (cmd == "power") {
    showPowerInfo();
  }
  // Network testing
  else if (cmd == "speed" || cmd == "speedtest") {
    testSpeed();
  }
  else if (cmd == "ping") {
    pingTest();
  }
  // Configuration
  else if (cmd.startsWith("autoreconnect ")) {
    String param = cmd.substring(14);
    if (param == "on" || param == "1" || param == "true") {
      autoReconnect = true;
      WiFi.setAutoReconnect(true);
      Serial.println("✓ Auto-reconnect enabled");
    } else {
      autoReconnect = false;
      WiFi.setAutoReconnect(false);
      Serial.println("✓ Auto-reconnect disabled");
    }
  }
  // System commands
  else if (cmd == "info" || cmd == "i") {
    showSystemInfo();
  }
  else if (cmd == "clear" || cmd == "cls") {
    clearScreen();
  }
  else if (cmd == "restart" || cmd == "reboot") {
    Serial.println("Restarting ESP32 in 2 seconds...");
    delay(2000);
    ESP.restart();
  }
  else if (cmd == "test") {
    Serial.println("✓ Serial communication working perfectly!");
    Serial.print("✓ Free heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
  }
  else if (cmd == "version" || cmd == "v") {
    Serial.println("ESP32 Ultimate WiFi Toolkit v" VERSION);
    Serial.println("Developed by: Upendra237");
  }
  // Unknown command
  else if (cmd != "") {
    Serial.print("Unknown command: '");
    Serial.print(originalCmd);
    Serial.println("'");
    Serial.println("Type 'help' for available commands");
  }
}

// ═══════════════════════════════════════════════════════════════
// HELP SCREEN
// ═══════════════════════════════════════════════════════════════

void showHelp() {
  Serial.println();
  Serial.println("╔══════════════════════════════════════════════════════════╗");
  Serial.println("║           ESP32 Ultimate WiFi Toolkit - Help            ║");
  Serial.println("╚══════════════════════════════════════════════════════════╝");
  Serial.println();
  Serial.println("┌─ BASIC COMMANDS ─────────────────────────────────────┐");
  Serial.println("│ help (h, ?)      - Show this help                    │");
  Serial.println("│ version (v)      - Show version info                 │");
  Serial.println("│ info (i)         - Show system information           │");
  Serial.println("│ test             - Test serial communication         │");
  Serial.println("└──────────────────────────────────────────────────────┘");
  Serial.println();
  Serial.println("┌─ WIFI SCANNING ──────────────────────────────────────┐");
  Serial.println("│ scan (s)         - Quick scan for networks           │");
  Serial.println("│ scandetail (sd)  - Detailed network scan             │");
  Serial.println("└──────────────────────────────────────────────────────┘");
  Serial.println();
  Serial.println("┌─ WIFI CONNECTION ────────────────────────────────────┐");
  Serial.println("│ connect <ssid> <password>                            │");
  Serial.println("│   Example: connect MyWiFi mypassword                 │");
  Serial.println("│   Example: connect \"My WiFi\" pass123                 │");
  Serial.println("│                                                      │");
  Serial.println("│ disconnect (d)   - Disconnect from WiFi              │");
  Serial.println("│ reconnect (r)    - Reconnect to saved WiFi           │");
  Serial.println("│ autoreconnect <on|off> - Toggle auto-reconnect       │");
  Serial.println("└──────────────────────────────────────────────────────┘");
  Serial.println();
  Serial.println("┌─ NETWORK STATUS ─────────────────────────────────────┐");
  Serial.println("│ status (st)      - Full connection status            │");
  Serial.println("│ ip               - Show IP configuration             │");
  Serial.println("│ mac              - Show MAC address                  │");
  Serial.println("│ signal (rssi)    - Show signal strength              │");
  Serial.println("│ channel          - Show WiFi channel                 │");
  Serial.println("│ power            - Show WiFi power settings          │");
  Serial.println("└──────────────────────────────────────────────────────┘");
  Serial.println();
  Serial.println("┌─ NETWORK TESTING ────────────────────────────────────┐");
  Serial.println("│ ping             - Test gateway connectivity         │");
  Serial.println("│ speed            - Test connection speed             │");
  Serial.println("└──────────────────────────────────────────────────────┘");
  Serial.println();
  Serial.println("┌─ SYSTEM CONTROL ─────────────────────────────────────┐");
  Serial.println("│ clear (cls)      - Clear screen                      │");
  Serial.println("│ restart (reboot) - Restart ESP32                     │");
  Serial.println("└──────────────────────────────────────────────────────┘");
  Serial.println();
  Serial.println("QUICK START: scan → connect YourWiFi password → status");
  Serial.println();
}

// ═══════════════════════════════════════════════════════════════
// NETWORK SCANNING
// ═══════════════════════════════════════════════════════════════

void scanNetworks() {
  Serial.println();
  Serial.println("→ Scanning WiFi networks...");
  
  WiFi.scanDelete();
  int n = WiFi.scanNetworks();
  
  if (n == 0) {
    Serial.println("  No networks found");
    Serial.println();
    return;
  }
  
  Serial.print("  Found ");
  Serial.print(n);
  Serial.println(" networks:");
  Serial.println();
  Serial.println("  #  | Signal | Enc | SSID");
  Serial.println("  ---|--------|-----|--------------------------------");
  
  for (int i = 0; i < n; i++) {
    Serial.print("  ");
    Serial.print(i + 1);
    if (i + 1 < 10) Serial.print(" ");
    Serial.print(" | ");
    
    int rssi = WiFi.RSSI(i);
    if (rssi > -100 && rssi < 0) {
      if (rssi > -10) Serial.print(" ");
      if (rssi > -100) Serial.print(" ");
    }
    Serial.print(rssi);
    
    // Signal quality indicator
    if (rssi >= -50) Serial.print("★★★");
    else if (rssi >= -60) Serial.print("★★ ");
    else if (rssi >= -70) Serial.print("★  ");
    else Serial.print("   ");
    
    Serial.print(" | ");
    Serial.print(WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "Open" : "Sec ");
    Serial.print(" | ");
    Serial.print(WiFi.SSID(i));
    
    if (WiFi.SSID(i) == savedSSID) {
      Serial.print(" ← SAVED");
    }
    if (WiFi.status() == WL_CONNECTED && WiFi.SSID(i) == WiFi.SSID()) {
      Serial.print(" ← CONNECTED");
    }
    Serial.println();
  }
  Serial.println();
}

void scanNetworksDetailed() {
  Serial.println();
  Serial.println("→ Detailed WiFi Scan...");
  
  WiFi.scanDelete();
  int n = WiFi.scanNetworks();
  
  if (n == 0) {
    Serial.println("  No networks found");
    return;
  }
  
  Serial.print("  Found ");
  Serial.print(n);
  Serial.println(" networks:");
  Serial.println();
  
  for (int i = 0; i < n; i++) {
    Serial.println("  ┌─────────────────────────────────────");
    Serial.print("  │ Network #");
    Serial.println(i + 1);
    Serial.print("  │ SSID: ");
    Serial.println(WiFi.SSID(i));
    Serial.print("  │ BSSID: ");
    Serial.println(WiFi.BSSIDstr(i));
    Serial.print("  │ Signal: ");
    Serial.print(WiFi.RSSI(i));
    Serial.print(" dBm (");
    int quality = 2 * (WiFi.RSSI(i) + 100);
    if (quality > 100) quality = 100;
    if (quality < 0) quality = 0;
    Serial.print(quality);
    Serial.println("%)");
    Serial.print("  │ Channel: ");
    Serial.println(WiFi.channel(i));
    Serial.print("  │ Security: ");
    
    switch(WiFi.encryptionType(i)) {
      case WIFI_AUTH_OPEN: Serial.println("Open"); break;
      case WIFI_AUTH_WEP: Serial.println("WEP"); break;
      case WIFI_AUTH_WPA_PSK: Serial.println("WPA-PSK"); break;
      case WIFI_AUTH_WPA2_PSK: Serial.println("WPA2-PSK"); break;
      case WIFI_AUTH_WPA_WPA2_PSK: Serial.println("WPA/WPA2-PSK"); break;
      case WIFI_AUTH_WPA2_ENTERPRISE: Serial.println("WPA2-Enterprise"); break;
      default: Serial.println("Unknown");
    }
    
    if (WiFi.SSID(i) == savedSSID) {
      Serial.println("  │ Status: ← SAVED");
    }
    if (WiFi.status() == WL_CONNECTED && WiFi.SSID(i) == WiFi.SSID()) {
      Serial.println("  │ Status: ← CONNECTED");
    }
  }
  Serial.println("  └─────────────────────────────────────");
  Serial.println();
}

// ═══════════════════════════════════════════════════════════════
// CONNECTION MANAGEMENT
// ═══════════════════════════════════════════════════════════════

void connectCommand(String params) {
  params.trim();
  
  int spaceIndex = params.indexOf(' ');
  
  if (spaceIndex == -1) {
    Serial.println();
    Serial.println("Usage: connect <ssid> <password>");
    Serial.println("Example: connect MyWiFi password123");
    Serial.println();
    return;
  }
  
  String ssid = params.substring(0, spaceIndex);
  String pass = params.substring(spaceIndex + 1);
  
  // Clean quotes if present
  ssid.replace("\"", "");
  pass.replace("\"", "");
  ssid.trim();
  pass.trim();
  
  if (ssid.length() == 0) {
    Serial.println("Error: SSID cannot be empty");
    return;
  }
  
  savedSSID = ssid;
  savedPassword = pass;
  
  Serial.println();
  Serial.println("→ Attempting connection...");
  Serial.print("  SSID: '");
  Serial.print(ssid);
  Serial.println("'");
  Serial.print("  Password length: ");
  Serial.println(pass.length());
  Serial.println();
  
  WiFi.disconnect();
  delay(100);
  
  connectionStartTime = millis();
  WiFi.begin(ssid.c_str(), pass.c_str());
  
  unsigned long startTime = millis();
  int dots = 0;
  
  Serial.print("  Status: ");
  while (WiFi.status() != WL_CONNECTED && (millis() - startTime) < MAX_CONNECT_TIME) {
    delay(500);
    
    switch(WiFi.status()) {
      case WL_IDLE_STATUS: Serial.print("I"); break;
      case WL_NO_SSID_AVAIL: Serial.print("N"); break;
      case WL_CONNECT_FAILED: Serial.print("F"); break;
      case WL_CONNECTION_LOST: Serial.print("L"); break;
      case WL_DISCONNECTED: Serial.print("."); break;
      default: Serial.print("?");
    }
    
    dots++;
    if (dots % 50 == 0) {
      Serial.println();
      Serial.print("  ");
    }
  }
  Serial.println();
  Serial.println();
  
  Serial.print("  Final Status: ");
  switch(WiFi.status()) {
    case WL_CONNECTED: Serial.println("CONNECTED"); break;
    case WL_NO_SSID_AVAIL: Serial.println("SSID NOT FOUND"); break;
    case WL_CONNECT_FAILED: Serial.println("CONNECTION FAILED (Wrong password?)"); break;
    case WL_IDLE_STATUS: Serial.println("IDLE"); break;
    case WL_DISCONNECTED: Serial.println("DISCONNECTED"); break;
    default: Serial.println("UNKNOWN");
  }
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) {
    wasConnected = true;
    unsigned long connectTime = millis() - connectionStartTime;
    
    Serial.println("╔════════════════════════════════════════════╗");
    Serial.println("║     ✓ Connected Successfully!             ║");
    Serial.println("╚════════════════════════════════════════════╝");
    Serial.print("  SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("  IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("  Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("  Signal: ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.print("  Channel: ");
    Serial.println(WiFi.channel());
    Serial.print("  Connection Time: ");
    Serial.print(connectTime);
    Serial.println(" ms");
    Serial.println();
  } else {
    Serial.println("✗ Connection failed!");
    Serial.println("  Possible reasons:");
    Serial.println("  - Wrong password");
    Serial.println("  - SSID not found (case-sensitive!)");
    Serial.println("  - Network out of range");
    Serial.println("  - Router issues");
    Serial.println();
  }
}

void reconnectWiFi() {
  if (savedSSID.length() == 0) {
    Serial.println("No saved WiFi credentials");
    return;
  }
  
  Serial.println();
  Serial.print("→ Reconnecting to: ");
  Serial.println(savedSSID);
  WiFi.begin(savedSSID.c_str(), savedPassword.c_str());
}

// ═══════════════════════════════════════════════════════════════
// STATUS DISPLAY
// ═══════════════════════════════════════════════════════════════

void showStatus() {
  Serial.println();
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║         Connection Status                 ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.println();
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("  Status: ✓ Connected");
    Serial.print("  SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("  BSSID: ");
    Serial.println(WiFi.BSSIDstr());
    Serial.print("  IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("  Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("  Subnet: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("  DNS: ");
    Serial.println(WiFi.dnsIP());
    Serial.print("  Signal: ");
    Serial.print(WiFi.RSSI());
    Serial.print(" dBm (");
    int quality = 2 * (WiFi.RSSI() + 100);
    if (quality > 100) quality = 100;
    if (quality < 0) quality = 0;
    Serial.print(quality);
    Serial.println("%)");
    Serial.print("  Channel: ");
    Serial.println(WiFi.channel());
    Serial.print("  MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("  Auto-Reconnect: ");
    Serial.println(autoReconnect ? "ON" : "OFF");
    
    if (connectionStartTime > 0) {
      unsigned long uptime = (millis() - connectionStartTime) / 1000;
      Serial.print("  Uptime: ");
      if (uptime >= 3600) {
        Serial.print(uptime / 3600);
        Serial.print("h ");
      }
      if (uptime >= 60) {
        Serial.print((uptime % 3600) / 60);
        Serial.print("m ");
      }
      Serial.print(uptime % 60);
      Serial.println("s");
    }
  } else {
    Serial.println("  Status: ✗ Disconnected");
    if (savedSSID.length() > 0) {
      Serial.print("  Last SSID: ");
      Serial.println(savedSSID);
    }
    Serial.print("  MAC: ");
    Serial.println(WiFi.macAddress());
    Serial.print("  Auto-Reconnect: ");
    Serial.println(autoReconnect ? "ON" : "OFF");
  }
  Serial.println();
}

void showIP() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("  Local IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("  Gateway: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("  Subnet: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("  DNS: ");
    Serial.println(WiFi.dnsIP());
    Serial.println();
  } else {
    Serial.println("Not connected to WiFi");
  }
}

void showSignal() {
  if (WiFi.status() == WL_CONNECTED) {
    int rssi = WiFi.RSSI();
    int quality = 2 * (rssi + 100);
    if (quality > 100) quality = 100;
    if (quality < 0) quality = 0;
    
    Serial.println();
    Serial.print("  Signal Strength: ");
    Serial.print(rssi);
    Serial.println(" dBm");
    Serial.print("  Quality: ");
    Serial.print(quality);
    Serial.println("%");
    Serial.print("  Rating: ");
    if (rssi >= -50) Serial.println("Excellent ★★★★★");
    else if (rssi >= -60) Serial.println("Good ★★★★");
    else if (rssi >= -70) Serial.println("Fair ★★★");
    else if (rssi >= -80) Serial.println("Weak ★★");
    else Serial.println("Very Weak ★");
    Serial.println();
  } else {
    Serial.println("Not connected to WiFi");
  }
}

void showChannel() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi Channel: ");
    Serial.println(WiFi.channel());
  } else {
    Serial.println("Not connected");
  }
}

void showPowerInfo() {
  Serial.println();
  Serial.println("WiFi Power Settings:");
  Serial.print("  TX Power: ");
  Serial.print(WiFi.getTxPower());
  Serial.println(" dBm");
  Serial.print("  Sleep Mode: ");
  Serial.println(WiFi.getSleep() ? "Enabled" : "Disabled");
  Serial.println();
}

// ═══════════════════════════════════════════════════════════════
// NETWORK TESTING
// ═══════════════════════════════════════════════════════════════

void pingTest() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi");
    return;
  }
  
  Serial.println();
  Serial.println("→ Pinging gateway...");
  Serial.print("  Gateway: ");
  Serial.println(WiFi.gatewayIP());
  
  bool success = WiFi.gatewayIP() != IPAddress(0, 0, 0, 0);
  
  if (success) {
    Serial.println("  ✓ Gateway reachable");
  } else {
    Serial.println("  ✗ Gateway not reachable");
  }
  Serial.println();
}

void testSpeed() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi");
    return;
  }
  
  Serial.println();
  Serial.println("→ Connection Speed Test");
  Serial.print("  Signal: ");
  Serial.print(WiFi.RSSI());
  Serial.println(" dBm");
  Serial.print("  Channel: ");
  Serial.println(WiFi.channel());
  
  int rssi = WiFi.RSSI();
  int estimatedSpeed = 0;
  
  if (rssi >= -50) estimatedSpeed = 150;
  else if (rssi >= -60) estimatedSpeed = 100;
  else if (rssi >= -70) estimatedSpeed = 50;
  else if (rssi >= -80) estimatedSpeed = 20;
  else estimatedSpeed = 10;
  
  Serial.print("  Estimated Speed: ~");
  Serial.print(estimatedSpeed);
  Serial.println(" Mbps");
  Serial.println("  (Actual speed depends on router and network load)");
  Serial.println();
}

// ═══════════════════════════════════════════════════════════════
// SYSTEM INFORMATION
// ═══════════════════════════════════════════════════════════════

void showSystemInfo() {
  Serial.println();
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║         System Information                ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.println();
  Serial.print("  Chip: ");
  Serial.println(ESP.getChipModel());
  Serial.print("  Revision: ");
  Serial.println(ESP.getChipRevision());
  Serial.print("  Cores: ");
  Serial.println(ESP.getChipCores());
  Serial.print("  CPU Freq: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");
  Serial.print("  Flash Size: ");
  Serial.print(ESP.getFlashChipSize() / 1024 / 1024);
  Serial.println(" MB");
  Serial.print("  Flash Speed: ");
  Serial.print(ESP.getFlashChipSpeed() / 1000000);
  Serial.println(" MHz");
  Serial.print("  Free Heap: ");
  Serial.print(ESP.getFreeHeap() / 1024);
  Serial.println(" KB");
  Serial.print("  MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("  Uptime: ");
  
  unsigned long uptime = millis() / 1000;
  if (uptime >= 3600) {
    Serial.print(uptime / 3600);
    Serial.print("h ");
  }
  if (uptime >= 60) {
    Serial.print((uptime % 3600) / 60);
    Serial.print("m ");
  }
  Serial.print(uptime % 60);
  Serial.println("s");
  
  Serial.println();
  Serial.println("  Developed by: Upendra237");
  Serial.println("  Version: " VERSION);
  Serial.println();
}

// ═══════════════════════════════════════════════════════════════
// UTILITY FUNCTIONS
// ═══════════════════════════════════════════════════════════════

void clearScreen() {
  for(int i = 0; i < 50; i++) {
    Serial.println();
  }
  Serial.println("╔══════════════════════════════════════════════╗");
  Serial.println("║    ESP32 Ultimate WiFi Toolkit v" VERSION "      ║");
  Serial.println("║         Developed by Upendra237              ║");
  Serial.println("╚══════════════════════════════════════════════╝");
}

void printPrompt() {
  Serial.print("\nwifi> ");
}

// ═══════════════════════════════════════════════════════════════
// END OF CODE
// ═══════════════════════════════════════════════════════════════