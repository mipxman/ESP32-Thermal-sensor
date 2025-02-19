#include <RH_ASK.h>
#include <SPI.h>
#include <DHT.h>

#define DHTPIN 2       // DHT11 sensor connected to pin D2
#define DHTTYPE DHT11  // Sensor type

DHT dht(DHTPIN, DHTTYPE);
RH_ASK rf_driver;  

void setup() {
    Serial.begin(9600);
    rf_driver.init();
    dht.begin();
}

void loop() {
    // Read temperature and humidity from the sensor
    float temperature = dht.readTemperature(); // Celsius
    float humidity = dht.readHumidity(); // Humidity

    // Check if the sensor reading is valid
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Convert float values to integer (for easier transmission)
    int temp_int = (int)(temperature * 10);  // Multiply by 10 to keep one decimal place
    int hum_int = (int)(humidity * 10);     // Multiply by 10 to keep one decimal place

    // Format the message as integer values (e.g., "T:253 H:605")
    char message[32];
    snprintf(message, sizeof(message), "T:%d H:%d", temp_int, hum_int);

    // Send data
    Serial.print("Sending: ");
    Serial.println(message);
    rf_driver.send((uint8_t *)message, strlen(message));
    rf_driver.waitPacketSent();

    delay(2000); // Wait before sending again
}
