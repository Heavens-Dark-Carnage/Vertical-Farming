This project is an automated vertical farming system built with an ESP32 microcontroller and various sensors to monitor and manage environmental conditions. It integrates with the Blynk platform for remote monitoring and control, allowing users to track real-time data and automate functions like irrigation based on set thresholds.

# **Features**
 - **Environmental Monitoring:** Tracks temperature, humidity, light levels, soil moisture, and water level using sensors.
 - **OLED Display:** Displays sensor data on an OLED screen in real-time.
 - **Automated Irrigation:** Controls a water pump based on soil moisture and water level.
 - **Blynk Integration:** Sends data to the Blynk app for remote monitoring.

# **Components**
 - ESP32 Microcontroller
 - DHT11 Temperature and Humidity Sensor
 - LDR for light intensity
 - Soil Moisture Sensor
 - Water Level Sensor
 - Water Pump
 - OLED Display (SSD1306)

# **Setup Instructions**
 1. Update the `ssid` and `pass` variables in the code with your WiFi credentials.
 2. Install the required libraries:
       - `BlynkSimpleEsp32.h` for Blynk integration
       - `Adafruit_GFX.h` and `Adafruit_SSD1306.h` for OLED display
       - `DHT.h` for temperature and humidity sensor support

 3. Adjust the thresholds in the code based on your environment.
 4. Upload the code to your ESP32 and monitor via the Serial Monitor or the Blynk app.

> [!NOTE]
> This system is intended for small-scale indoor farming or educational projects, offering a real-time solution for environmental monitoring and irrigation control.
