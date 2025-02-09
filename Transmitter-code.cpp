#include <RH_ASK.h>
#include <SPI.h>
#include <DHT.h>

#define DHTPIN 2      // DHT11 sensor data pin
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

RH_ASK driver(2000, 4, 7, 0); // (Speed, RX, TX, PTT) TX on pin 7

void setup() {
    Serial.begin(115200);
    dht.begin();
    if (!driver.init()) {
        Serial.println("❌ RF Transmitter init failed!");
        while (1);
    }
    Serial.println("✅ RF Transmitter Ready");
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // Check if reading failed
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("⚠️ ERROR: Failed to read from DHT sensor!");
        delay(2000);
        return;
    }

    // Convert float to string properly
    char tempStr[6];
    char humStr[6];
    dtostrf(temperature, 4, 1, tempStr);
    dtostrf(humidity, 4, 1, humStr);

    // Format message
    char message[32];
    snprintf(message, sizeof(message), "T:%sC H:%s%%", tempStr, humStr);

    // Send data via RF
    driver.send((uint8_t *)message, strlen(message));
    driver.waitPacketSent();

    Serial.print("✅ Sent: ");
    Serial.println(message);
    delay(5000); // Send data every 5 seconds
}
