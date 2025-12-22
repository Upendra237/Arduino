/*
 * ═══════════════════════════════════════════════════════════════
 *  ESP32 Robust WiFi Connection
 * ═══════════════════════════════════════════════════════════════
 *  Version: 1.0.0
 *  Developed by: Upendra237
 *  Code Assisted by: Claude AI Sonnet 4.5
 *  GitHub: https://github.com/Upendra237/Arduino/tree/main/esp32-robust-wifi-connection
 * 
 *  Description:
 *  Ultra-reliable WiFi connection manager for ESP32 that never gives up.
 *  Features automatic reconnection, detailed status monitoring, LED indicators,
 *  and comprehensive error handling. Perfect for IoT projects requiring
 *  persistent internet connectivity.
 * 
 *  Features:
 *  ✓ Automatic WiFi connection on startup
 *  ✓ Continuous connection monitoring
 *  ✓ Automatic reconnection on disconnect
 *  ✓ LED status indicator (solid=connected, blink=disconnected)
 *  ✓ Detailed serial debugging output
 *  ✓ Signal strength monitoring
 *  ✓ Connection time tracking
 *  ✓ Never gives up trying to connect
 * 
 *  Hardware Required:
 *  - ESP32 Development Board (any variant)
 *  - USB Cable
 *  - WiFi Network
 * 
 *  Serial Monitor Settings:
 *  - Baud Rate: 115200
 * ═══════════════════════════════════════════════════════════════
 */

#include <WiFi.h>

// ═══════════════════════════════════════════════════════════════
// ⚙️ WiFi CREDENTIALS - CHANGE THESE!
// ═══════════════════════════════════════════════════════════════

const char* WIFI_SSID = "YOUR_WIFI_SSID";        // Your WiFi network name
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD"; // Your WiFi password

// ═══════════════════════════════════════════════════════════════
// ⚙️ CONFIGURATION
// ═══════════════════════════════════════════════════════════════

#define VERSION "1.0.0"
#define SERIAL_BAUD 115200

// Pin Configuration
#define LED_BUILTIN 2                     // Built-in LED pin (GPIO 2)

// Timing Configuration (milliseconds)
#define CONNECTION_TIMEOUT 20000          // Max wait time per attempt (20s)
#define CHECK_INTERVAL 5000               // Check connection status every 5s
#define RETRY_DELAY 3000                  // Wait before retry (3s)

// ═══════════════════════════════════════════════════════════════
// 🌐 GLOBAL VARIABLES
// ═══════════════════════════════════════════════════════════════

unsigned long lastConnectionCheck = 0;
unsigned long connectionStartTime = 0;
unsigned long totalUptime = 0;
int connectionAttempts = 0;
bool wasConnected = false;

// ═══════════════════════════════════════════════════════════════
// 🚀 SETUP - RUNS ONCE ON STARTUP
// ═══════════════════════════════════════════════════════════════

void setup() {
  // Initialize Serial Monitor
  Serial.begin(SERIAL_BAUD);
  delay(1000);
  
  // Initialize LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // Display startup information
  printBanner();
  printSystemInfo();
  printWiFiConfig();
  
  // Configure WiFi for maximum reliability
  WiFi.mode(WIFI_STA);                    // Station mode only
  WiFi.setAutoReconnect(true);            // Enable auto-reconnect
  WiFi.persistent(true);                  // Save credentials to flash
  WiFi.setSleep(false);                   // Disable sleep for stability
  
  Serial.println("→ Initializing WiFi connection...\n");
  delay(1000);
  
  // Initial connection attempt
  connectToWiFi();
}

// ═══════════════════════════════════════════════════════════════
// 🔄 MAIN LOOP - RUNS CONTINUOUSLY
// ═══════════════════════════════════════════════════════════════

void loop() {
  // Periodic connection monitoring
  if (millis() - lastConnectionCheck >= CHECK_INTERVAL) {
    lastConnectionCheck = millis();
    checkAndMaintainConnection();
  }
  
  // Update LED status indicator
  updateLED();
  
  delay(100);
}

// ═══════════════════════════════════════════════════════════════
// 📡 WiFi CONNECTION FUNCTIONS
// ═══════════════════════════════════════════════════════════════

void connectToWiFi() {
  connectionAttempts++;
  
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║          WiFi Connection Attempt           ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.print("  Attempt #: ");
  Serial.println(connectionAttempts);
  Serial.print("  SSID: ");
  Serial.println(WIFI_SSID);
  Serial.print("  Status: ");
  
  // Clean disconnect before reconnecting
  WiFi.disconnect();
  delay(100);
  
  // Start connection
  connectionStartTime = millis();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  // Wait for connection with visual feedback
  int dots = 0;
  while (WiFi.status() != WL_CONNECTED && 
         (millis() - connectionStartTime) < CONNECTION_TIMEOUT) {
    delay(500);
    Serial.print(".");
    dots++;
    
    // Blink LED during connection attempt
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    
    // New line every 50 dots for readability
    if (dots % 50 == 0) {
      Serial.println();
      Serial.print("          ");
    }
  }
  
  Serial.println();
  Serial.println();
  
  // Check connection result
  if (WiFi.status() == WL_CONNECTED) {
    onWiFiConnected();
  } else {
    onWiFiConnectionFailed();
  }
}

void onWiFiConnected() {
  unsigned long connectTime = millis() - connectionStartTime;
  
  // Success banner
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║     ✓✓✓ CONNECTED SUCCESSFULLY! ✓✓✓      ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.println();
  
  // Network information
  Serial.println("📡 Network Information:");
  Serial.print("   SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("   IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("   Gateway: ");
  Serial.println(WiFi.gatewayIP());
  Serial.print("   Subnet Mask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("   DNS Server: ");
  Serial.println(WiFi.dnsIP());
  Serial.println();
  
  // Device information
  Serial.println("📶 Connection Details:");
  Serial.print("   MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.print("   BSSID: ");
  Serial.println(WiFi.BSSIDstr());
  Serial.print("   Channel: ");
  Serial.println(WiFi.channel());
  Serial.print("   Signal Strength: ");
  Serial.print(WiFi.RSSI());
  Serial.print(" dBm (");
  Serial.print(getSignalQuality());
  Serial.println(")");
  Serial.println();
  
  // Connection statistics
  Serial.println("📊 Statistics:");
  Serial.print("   Connection Time: ");
  Serial.print(connectTime);
  Serial.println(" ms");
  Serial.print("   Total Attempts: ");
  Serial.println(connectionAttempts);
  Serial.println();
  
  Serial.println("════════════════════════════════════════════");
  Serial.println("  🌐 WiFi is ONLINE and READY!");
  Serial.println("════════════════════════════════════════════");
  Serial.println();
  
  // Solid LED when connected
  digitalWrite(LED_BUILTIN, HIGH);
  wasConnected = true;
}

void onWiFiConnectionFailed() {
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║         ✗ CONNECTION FAILED ✗             ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.println();
  
  // Diagnose failure reason
  Serial.println("🔍 Diagnosis:");
  switch(WiFi.status()) {
    case WL_NO_SSID_AVAIL:
      Serial.println("   ✗ Network not found");
      Serial.println("   → Check: SSID spelling (case-sensitive)");
      Serial.println("   → Check: Router is powered on");
      Serial.println("   → Check: ESP32 is within range");
      break;
      
    case WL_CONNECT_FAILED:
      Serial.println("   ✗ Connection failed");
      Serial.println("   → Check: Password is correct");
      Serial.println("   → Check: Security type matches (WPA2/WPA3)");
      Serial.println("   → Try: Restart router");
      break;
      
    case WL_IDLE_STATUS:
      Serial.println("   ✗ Connection timeout");
      Serial.println("   → Check: Router is responding");
      Serial.println("   → Check: No MAC filtering enabled");
      break;
      
    default:
      Serial.print("   ✗ Unknown error (Status code: ");
      Serial.print(WiFi.status());
      Serial.println(")");
      Serial.println("   → Try: Power cycle ESP32");
  }
  
  Serial.println();
  Serial.print("⏳ Retrying in ");
  Serial.print(RETRY_DELAY / 1000);
  Serial.println(" seconds...");
  Serial.println();
  
  // Fast LED blink to indicate failure
  blinkLED(6, 100);
  
  // Wait before retry (minus blink time)
  delay(RETRY_DELAY - 1200);
  
  // Retry connection
  connectToWiFi();
}

void checkAndMaintainConnection() {
  if (WiFi.status() == WL_CONNECTED) {
    // Update uptime
    if (connectionStartTime > 0) {
      totalUptime = (millis() - connectionStartTime) / 1000;
    }
    
    // Periodic status update
    Serial.println("═════════════════════════════════════════════════════════════════════════════════");
    Serial.print("  ✓ WiFi Status: CONNECTED");
    Serial.print(" | IP: ");
    Serial.print(WiFi.localIP());
    Serial.print(" | Signal: ");
    Serial.print(WiFi.RSSI());
    Serial.print(" dBm | Uptime: ");
    printUptime(totalUptime);
    Serial.println("\n═════════════════════════════════════════════════════════════════════════════════");
  } else {
    // Connection lost - trigger reconnection
    if (wasConnected) {
      Serial.println();
      Serial.println("════════════════════════════════════════════");
      Serial.println("  ⚠️  WiFi DISCONNECTED!");
      Serial.println("════════════════════════════════════════════");
      Serial.println("  → Auto-reconnecting now...");
      Serial.println();
      
      wasConnected = false;
      digitalWrite(LED_BUILTIN, LOW);
      connectionStartTime = 0;
      
      connectToWiFi();
    }
  }
}

// ═══════════════════════════════════════════════════════════════
// 💡 LED CONTROL FUNCTIONS
// ═══════════════════════════════════════════════════════════════

void updateLED() {
  if (WiFi.status() == WL_CONNECTED) {
    // Solid ON when connected
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // Slow blink when disconnected (1 Hz)
    digitalWrite(LED_BUILTIN, (millis() / 500) % 2);
  }
}

void blinkLED(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delayMs);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayMs);
  }
}

// ═══════════════════════════════════════════════════════════════
// 📊 INFORMATION DISPLAY FUNCTIONS
// ═══════════════════════════════════════════════════════════════

void printBanner() {
  Serial.println("\n\n");
  Serial.println("╔════════════════════════════════════════════╗");
  Serial.println("║   ESP32 Robust WiFi Connection v" VERSION "     ║");
  Serial.println("║          Developed by Upendra237           ║");
  Serial.println("║   Code Assisted by Claude AI Sonnet 4.5    ║");
  Serial.println("╚════════════════════════════════════════════╝");
  Serial.println();
}

void printSystemInfo() {
  Serial.println("════════════════════════════════════════════");
  Serial.println("  SYSTEM INFORMATION");
  Serial.println("════════════════════════════════════════════");
  Serial.print("  Chip Model: ");
  Serial.println(ESP.getChipModel());
  Serial.print("  Chip Revision: ");
  Serial.println(ESP.getChipRevision());
  Serial.print("  CPU Cores: ");
  Serial.println(ESP.getChipCores());
  Serial.print("  CPU Frequency: ");
  Serial.print(ESP.getCpuFreqMHz());
  Serial.println(" MHz");
  Serial.print("  Flash Size: ");
  Serial.print(ESP.getFlashChipSize() / (1024 * 1024));
  Serial.println(" MB");
  Serial.print("  Free Heap: ");
  Serial.print(ESP.getFreeHeap() / 1024);
  Serial.println(" KB");
  Serial.print("  MAC Address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("════════════════════════════════════════════");
  Serial.println();
}

void printWiFiConfig() {
  Serial.println("════════════════════════════════════════════");
  Serial.println("  WiFi CONFIGURATION");
  Serial.println("════════════════════════════════════════════");
  Serial.print("  Target SSID: ");
  Serial.println(WIFI_SSID);
  Serial.print("  Password Length: ");
  Serial.println(strlen(WIFI_PASSWORD));
  Serial.print("  Auto-Reconnect: ");
  Serial.println("ENABLED ✓");
  Serial.print("  Persistent Mode: ");
  Serial.println("ENABLED ✓");
  Serial.print("  WiFi Sleep: ");
  Serial.println("DISABLED ✓");
  Serial.print("  Connection Timeout: ");
  Serial.print(CONNECTION_TIMEOUT / 1000);
  Serial.println(" seconds");
  Serial.println("════════════════════════════════════════════");
  Serial.println();
}

void printUptime(unsigned long seconds) {
  if (seconds >= 3600) {
    Serial.print(seconds / 3600);
    Serial.print("h ");
    seconds %= 3600;
  }
  if (seconds >= 60) {
    Serial.print(seconds / 60);
    Serial.print("m ");
    seconds %= 60;
  }
  Serial.print(seconds);
  Serial.print("s");
}

// ═══════════════════════════════════════════════════════════════
// 🛠️ UTILITY FUNCTIONS
// ═══════════════════════════════════════════════════════════════

String getSignalQuality() {
  int rssi = WiFi.RSSI();
  int quality = 2 * (rssi + 100);
  if (quality > 100) quality = 100;
  if (quality < 0) quality = 0;
  
  String result = String(quality) + "%";
  
  if (rssi >= -50) result += " Excellent ★★★★★";
  else if (rssi >= -60) result += " Good ★★★★";
  else if (rssi >= -70) result += " Fair ★★★";
  else if (rssi >= -80) result += " Weak ★★";
  else result += " Very Weak ★";
  
  return result;
}

// ═══════════════════════════════════════════════════════════════
// 📝 END OF CODE
// ═══════════════════════════════════════════════════════════════