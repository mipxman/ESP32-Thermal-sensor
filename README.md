# ESP32-Thermal-sensor

This project was developed for the **"Electronics for Applied Physics"** course at the **University of Bologna**.  

You are free to use, modify, and distribute this code for academic and educational purposes.



This project establishes a wireless temperature and humidity monitoring system using an Arduino Mega 2560 R3 with a DHT11 sensor and an RF 433MHz transmitter to send data. On the receiving side, an ESP32-S3 with an RF 433MHz receiver collects the data, displays it on an LCD screen (LM016L), and hosts a web server to show real-time temperature and humidity readings over WiFi.

🔹 Features:
✔ Wireless Data Transmission (RF 433MHz)
✔ Real-Time Monitoring on LCD & Web Interface
✔ ESP32-S3 as a Web Server with WiFi Connectivity
✔ Low-Power, Cost-Effective Solution



## 📋 Requirements

| **Component**         | **Quantity** | **Description**                                   | **Buy Link** |
|----------------------|------------|---------------------------------------------------|-------------|
| **[ESP32-S3](https://www.amazon.com/s?k=esp32-s3)** | 1 | Microcontroller (Receiver) | [🔗 Amazon](https://www.amazon.com/s?k=esp32-s3) |
| **[Arduino Mega 2560 R3](https://www.amazon.com/s?k=arduino+mega+2560)** | 1 | Microcontroller (Transmitter) | [🔗 Amazon](https://www.amazon.com/s?k=arduino+mega+2560) |
| **[DHT11 Sensor](https://www.amazon.com/s?k=dht11+sensor)** | 1 | Temperature and humidity sensor | [🔗 Amazon](https://www.amazon.com/s?k=dht11+sensor) |
| **[RF 433MHz TX Module](https://www.amazon.com/s?k=rf+433mhz+transmitter)** | 1 | Wireless transmitter module | [🔗 Amazon](https://www.amazon.com/s?k=rf+433mhz+transmitter) |
| **[RF 433MHz RX Module](https://www.amazon.com/s?k=rf+433mhz+receiver)** | 1 | Wireless receiver module | [🔗 Amazon](https://www.amazon.com/s?k=rf+433mhz+receiver) |
| **[I2C LCD Display (LM016L)](https://www.amazon.com/s?k=i2c+lcd+display)** | 1 | LCD module to display data | [🔗 Amazon](https://www.amazon.com/s?k=i2c+lcd+display) |
| **[Jumper Wires](https://www.amazon.com/s?k=jumper+wires)** | Various | For connecting components | [🔗 Amazon](https://www.amazon.com/s?k=jumper+wires) |
| **[Power Supply](https://www.amazon.com/s?k=5v+power+supply)** | 1 | 5V power supply for microcontrollers | [🔗 Amazon](https://www.amazon.com/s?k=5v+power+supply) |


I use the Arduino Mega and ESP32-S3 with a RF modules to send a temperature data and humadity in the web-server and archive that.   

This document is completing soon. 
## 🛠 Wiring Configuration
### 📡 Wiring for Arduino Mega 2560 R3 (Transmitter)

| **Component**  | **Arduino Mega Pin** |
|---------------|----------------------|
| **DHT11 Data** | **Pin 2**           |
| **RF TX DATA** | **Pin 7**           |
| **RF TX VCC**  | **5V**              |
| **RF TX GND**  | **GND**             |

### 📡 Wiring for ESP32-S3 (Receiver)

| **Component**  | **ESP32-S3 Pin** |
|---------------|-----------------|
| **RF RX DATA** | **Pin 13**      |
| **RF RX VCC**  | **5V**          |
| **RF RX GND**  | **GND**         |
| **LCD SDA**    | **GPIO 8**      |
| **LCD SCL**    | **GPIO 9**      |

© 2025 MO (mipxman)
