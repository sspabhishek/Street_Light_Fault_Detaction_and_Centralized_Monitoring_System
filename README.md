# Street_Light_Fault_Detection_and_Centralized_Monitoring_System

## Overview

The **Street_Light_Fault_Detection_and_Centralized_Monitoring_System** is a comprehensive solution designed to monitor and manage street lights in an urban environment. This project includes both the hardware components and the software dashboard required for centralized monitoring and fault detection.

## Features

- **Fault Detection**: Monitors street light systems for faults and malfunctions.
- **Centralized Dashboard**: Provides a user-friendly interface for real-time monitoring and data visualization.
- **Mesh Networking**: Allows multiple nodes to communicate and relay data efficiently, ensuring robust communication even in case of partial network failures.
- **Data Reporting**: Sends sensor data (current, voltage) to a central server for further analysis and reporting.

## Hardware

- **ESP8266 Modules**: Used for mesh networking and data transmission.
- **Current Sensors**: Measures the electrical current consumed by the street lights.
- **Voltage Sensors**: Measures the voltage levels to ensure proper operation.

## Software

- **Firmware**: Developed for ESP8266 to handle sensor data collection, fault detection, and communication via mesh network.
- **Centralized Dashboard**: A web-based interface to visualize data, manage faults, and monitor the health of the street lighting system.

## Getting Started

### Hardware Setup

1. **Connect Sensors**: Attach current and voltage sensors to the ESP8266 as per the pin configuration provided in the code.
2. **Power Supply**: Ensure all components are properly powered and connected.

### Software Setup

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/sspabhishek/Street_Light_Fault_Detaction_and_Centralized_Monitoring_System
   ```

2. **Install Dependencies**:
   - Ensure you have the necessary libraries installed for the ESP8266:
     - `painlessMesh`
     - `ESP8266HTTPClient`
     - `ESP8266WiFi`
     - `ArduinoJson`

3. **Upload Firmware**:
   - Open the firmware code in the Arduino IDE.
   - Select the appropriate board and port.
   - Upload the code to the ESP8266 modules.

4. **Configure Dashboard**:
   - Set up the server and dashboard as described in the project documentation.
   - Link the dashboard to your server URL to receive and display data from the ESP8266 modules.

## Code Structure

- **`firmware/`**: Contains the ESP8266 firmware code for fault detection and data transmission.
- **`dashboard/`**: Contains the code and assets for the centralized monitoring dashboard.
- **`docs/`**: Includes project documentation and setup guides.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request if you have improvements or bug fixes. Make sure to follow the coding standards and provide a clear description of your changes.


## Contact

For questions or feedback, please contact [abhishekprajapati243@gmail.com](mailto:your-email@example.com).
