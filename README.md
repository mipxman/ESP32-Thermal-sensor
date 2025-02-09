# ESP32-Thermal-sensor
This is a project for Applied Electronic course university di Bologna , 2025 

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

