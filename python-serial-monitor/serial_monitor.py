"""
╔════════════════════════════════════════════════════════════════╗
║              Python Serial Monitor - CLI Version               ║
║                    Works with Arduino/ESP32                    ║
╚════════════════════════════════════════════════════════════════╝

Version: 1.0.0
Developed by: Upendra237
Code Assisted by: Claude AI Sonnet 4.5
GitHub: https://github.com/Upendra237/Arduino/tree/main/python-serial-monitor

Description:
    A lightweight command-line serial monitor for Arduino and ESP32.
    Features auto-port detection, multiple baud rates, and real-time
    data monitoring with send capabilities.
"""

import serial
import serial.tools.list_ports
import threading
import sys
import time
from datetime import datetime

# ═══════════════════════════════════════════════════════════════
# CONFIGURATION
# ═══════════════════════════════════════════════════════════════

VERSION = "1.0.0"

# Common baud rates for Arduino/ESP32
BAUD_RATES = {
    1: 9600,
    2: 19200,
    3: 57600,
    4: 115200,  # Default for ESP32
    5: 230400,
    6: 460800,
    7: 921600
}

# ═══════════════════════════════════════════════════════════════
# COLOR CODES (Optional - works in most terminals)
# ═══════════════════════════════════════════════════════════════

class Colors:
    HEADER = '\033[95m'
    BLUE = '\033[94m'
    CYAN = '\033[96m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

# ═══════════════════════════════════════════════════════════════
# HELPER FUNCTIONS
# ═══════════════════════════════════════════════════════════════

def print_banner():
    """Display welcome banner"""
    print("\n" + Colors.CYAN + "═" * 64)
    print("║" + " " * 62 + "║")
    print("║" + " " * 12 + "Python Serial Monitor - CLI v" + VERSION + " " * 16 + "║")
    print("║" + " " * 18 + "Developed by " + "Upendra237" + " " * 21 + "║")
    print("║" + " " * 62 + "║")
    print("═" * 64 + Colors.ENDC)
    print()

def list_ports():
    """List all available serial ports with details"""
    ports = serial.tools.list_ports.comports()
    
    if not ports:
        print(Colors.RED + "✗ No serial ports found!" + Colors.ENDC)
        print("\nTroubleshooting:")
        print("  1. Check if device is connected")
        print("  2. Install/update USB drivers (CP210x, CH340, FTDI)")
        print("  3. Try a different USB port or cable")
        return []
    
    print(Colors.GREEN + "=" * 64)
    print("  Available Serial Ports:")
    print("=" * 64 + Colors.ENDC)
    
    for i, port in enumerate(ports, 1):
        print(f"{Colors.BOLD}{i}.{Colors.ENDC} {Colors.CYAN}{port.device}{Colors.ENDC}")
        print(f"   Description: {port.description}")
        print(f"   Hardware ID: {port.hwid}")
        print()
    
    print(Colors.GREEN + "=" * 64 + Colors.ENDC)
    return ports

def select_port(ports):
    """Let user select a port"""
    while True:
        try:
            choice = input(f"\n{Colors.YELLOW}Select port number: {Colors.ENDC}")
            port_index = int(choice) - 1
            
            if 0 <= port_index < len(ports):
                return ports[port_index].device
            else:
                print(Colors.RED + "✗ Invalid selection! Please try again." + Colors.ENDC)
        except ValueError:
            print(Colors.RED + "✗ Please enter a valid number!" + Colors.ENDC)
        except KeyboardInterrupt:
            print("\n\n" + Colors.YELLOW + "Operation cancelled." + Colors.ENDC)
            sys.exit(0)

def select_baud_rate():
    """Let user select baud rate"""
    print(f"\n{Colors.GREEN}Common Baud Rates:{Colors.ENDC}")
    print(f"  1. 9600      (Standard)")
    print(f"  2. 19200")
    print(f"  3. 57600")
    print(f"  4. 115200    {Colors.CYAN}(ESP32 Default) ⭐{Colors.ENDC}")
    print(f"  5. 230400")
    print(f"  6. 460800")
    print(f"  7. 921600")
    print(f"\n  Or enter custom baud rate")
    
    while True:
        try:
            choice = input(f"\n{Colors.YELLOW}Select baud rate: {Colors.ENDC}")
            
            # Check if it's a predefined option
            if choice.isdigit() and len(choice) <= 2:
                choice_num = int(choice)
                if choice_num in BAUD_RATES:
                    return BAUD_RATES[choice_num]
            
            # Custom baud rate
            baud = int(choice)
            if 300 <= baud <= 2000000:  # Valid range
                confirm = input(f"Use custom baud rate {baud}? (y/n): ").lower()
                if confirm == 'y':
                    return baud
            else:
                print(Colors.RED + "✗ Baud rate out of valid range (300-2000000)" + Colors.ENDC)
                
        except ValueError:
            print(Colors.RED + "✗ Please enter a valid number!" + Colors.ENDC)
        except KeyboardInterrupt:
            print("\n\n" + Colors.YELLOW + "Operation cancelled." + Colors.ENDC)
            sys.exit(0)

def read_serial(ser, show_timestamp=False):
    """Read data from serial port continuously"""
    print(Colors.CYAN + "\n" + "=" * 64)
    print("  Live Data Stream (Press Ctrl+C to exit)")
    print("=" * 64 + Colors.ENDC)
    print()
    
    while True:
        try:
            if ser.in_waiting:
                data = ser.readline().decode('utf-8', errors='ignore').strip()
                if data:
                    if show_timestamp:
                        timestamp = datetime.now().strftime("%H:%M:%S.%f")[:-3]
                        print(f"{Colors.BLUE}[{timestamp}]{Colors.ENDC} {data}")
                    else:
                        print(data)
        except serial.SerialException as e:
            print(f"\n{Colors.RED}✗ Serial connection lost: {e}{Colors.ENDC}")
            break
        except Exception as e:
            print(f"\n{Colors.RED}✗ Error reading: {e}{Colors.ENDC}")
            break

def send_data(ser):
    """Handle sending data to serial port"""
    print(f"\n{Colors.YELLOW}Commands:{Colors.ENDC}")
    print(f"  - Type message and press Enter to send")
    print(f"  - Press Ctrl+C to disconnect and exit")
    print()
    
    while True:
        try:
            user_input = input()
            if user_input.strip():
                ser.write((user_input + '\n').encode('utf-8'))
                print(f"{Colors.GREEN}→ Sent: {user_input}{Colors.ENDC}")
        except KeyboardInterrupt:
            print(f"\n\n{Colors.YELLOW}Disconnecting...{Colors.ENDC}")
            return
        except Exception as e:
            print(f"\n{Colors.RED}✗ Error sending: {e}{Colors.ENDC}")
            return

# ═══════════════════════════════════════════════════════════════
# MAIN FUNCTION
# ═══════════════════════════════════════════════════════════════

def main():
    """Main program flow"""
    try:
        # Display banner
        print_banner()
        
        # List and select port
        ports = list_ports()
        if not ports:
            sys.exit(1)
        
        selected_port = select_port(ports)
        
        # Select baud rate
        baud_rate = select_baud_rate()
        
        # Ask for timestamp option
        timestamp_choice = input(f"\n{Colors.YELLOW}Show timestamps? (y/n): {Colors.ENDC}").lower()
        show_timestamp = timestamp_choice == 'y'
        
        # Connect to serial port
        print(f"\n{Colors.CYAN}Connecting to {selected_port} at {baud_rate} baud...{Colors.ENDC}")
        
        try:
            ser = serial.Serial(selected_port, baud_rate, timeout=1)
            time.sleep(2)  # Wait for connection to stabilize
            
            print(f"{Colors.GREEN}✓ Connected successfully!{Colors.ENDC}")
            print(f"{Colors.GREEN}✓ Port: {selected_port}{Colors.ENDC}")
            print(f"{Colors.GREEN}✓ Baud Rate: {baud_rate}{Colors.ENDC}")
            
            # Start reading thread
            read_thread = threading.Thread(
                target=read_serial, 
                args=(ser, show_timestamp), 
                daemon=True
            )
            read_thread.start()
            
            # Handle sending data in main thread
            send_data(ser)
            
            # Cleanup
            ser.close()
            print(f"\n{Colors.GREEN}✓ Disconnected successfully{Colors.ENDC}")
            print(f"{Colors.CYAN}Thank you for using Python Serial Monitor!{Colors.ENDC}\n")
            
        except serial.SerialException as e:
            print(f"\n{Colors.RED}✗ Connection failed: {e}{Colors.ENDC}")
            print(f"\n{Colors.YELLOW}Troubleshooting:{Colors.ENDC}")
            print(f"  1. Check if port is already in use")
            print(f"  2. Verify device is properly connected")
            print(f"  3. Try a different port or baud rate")
            sys.exit(1)
            
    except KeyboardInterrupt:
        print(f"\n\n{Colors.YELLOW}Program terminated by user.{Colors.ENDC}")
        sys.exit(0)
    except Exception as e:
        print(f"\n{Colors.RED}✗ Unexpected error: {e}{Colors.ENDC}")
        sys.exit(1)

# ═══════════════════════════════════════════════════════════════
# ENTRY POINT
# ═══════════════════════════════════════════════════════════════

if __name__ == "__main__":
    main()