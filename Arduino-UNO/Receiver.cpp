#include <RH_ASK.h>
#include <SPI.h>
#include <LiquidCrystal.h>

RH_ASK rf_driver;
LiquidCrystal lcd(7, 8, 9, 10, 3, 4);  // LCD pin configuration

void setup() {
    Serial.begin(9600);
    rf_driver.init();
    lcd.begin(16, 2);
    lcd.print("Waiting...");
}

void loop() {
    uint8_t buf[20];
    uint8_t buflen = sizeof(buf);

    if (rf_driver.recv(buf, &buflen)) {
        buf[buflen] = '\0';  // Null-terminate received data
        Serial.print("Received: ");
        Serial.println((char *)buf);

        // Parse the received message
        int temp_int, hum_int;
        if (sscanf((char *)buf, "T:%d H:%d", &temp_int, &hum_int) == 2) {
            // Convert back to float values
            float temperature = temp_int / 10.0;  // Divide by 10 to get the correct value
            float humidity = hum_int / 10.0;      // Divide by 10 to get the correct value

            // Display the results on LCD
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("T:");
            lcd.print(temperature, 1); // Display with one decimal
            lcd.setCursor(0, 1);
            lcd.print("H:");
            lcd.print(humidity, 1); // Display with one decimal
        }
    } else {
        Serial.println("No data received...");
    }

    delay(500);
}
