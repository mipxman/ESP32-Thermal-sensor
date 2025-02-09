#include <WiFi.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <time.h> // Include the time library

RH_ASK driver(2000, 13, 22, 0); // RF RX on Pin 13
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C Address: 0x27

// WiFi Configuration
const char *ssid = "Xiaomi-12";
const char *password = "123456Aa";
WiFiServer server(80);

String receivedData = "Waiting...";

// Struct to hold history data
struct HistoryEntry {
    String timestamp;
    String data;
};

// Vector to store history entries
std::vector<HistoryEntry> history;

// Convert Time to String
String getTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) return "Unknown Time";
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(buffer);
}

// Function to sort history by timestamp
bool sortByTimestamp(const HistoryEntry &a, const HistoryEntry &b) {
    return a.timestamp > b.timestamp;
}

void setup() {
    Serial.begin(115200);
    
    // LCD Initialization
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Connecting WiFi");

    // Connect WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    // Show IP Address on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Web IP:");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());

    Serial.println("\nConnected to WiFi");
    Serial.print("ESP32 Web Server IP: ");
    Serial.println(WiFi.localIP());

    // Configure NTP
    configTime(0, 0, "pool.ntp.org", "time.nist.gov"); // Configure NTP servers
    Serial.println("Waiting for NTP time sync...");
    delay(2000); // Wait for time synchronization

    server.begin();

    // RF Receiver Initialization
    if (!driver.init()) {
        Serial.println("RF Receiver init failed!");
        while (1);
    }
    Serial.println("RF Receiver Ready");
}

void loop() {
    uint8_t buf[32];
    uint8_t buflen = sizeof(buf);

    // Receive RF Data
    if (driver.recv(buf, &buflen)) {
        buf[buflen] = '\0';
        receivedData = (char *)buf;

        // Store in history
        HistoryEntry entry;
        entry.timestamp = getTime();
        entry.data = receivedData;
        history.push_back(entry);

        // Sort history by timestamp
        std::sort(history.begin(), history.end(), sortByTimestamp);

        Serial.print("Received: ");
        Serial.println(receivedData);
    }

    // Handle Web Clients
    WiFiClient client = server.available();
    if (client) {
        Serial.println("New Client Connected");
        String request = "";

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                request += c;
                if (c == '\n' && request.indexOf("\r\n\r\n") != -1) break;
            }
        }

        // Send Web Page
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println("<html><head><meta http-equiv='refresh' content='5'/></head><body>");
        client.println("<h2>ESP32-S3 Weather Station</h2>");
        client.println("<p>Last Data: " + receivedData + "</p>");
        client.println("<h3>History</h3>");

        // Display sorted history
        for (const auto &entry : history) {
            client.println("<p>[" + entry.timestamp + "] " + entry.data + "</p>");
        }

        client.println("</body></html>");
        
        client.stop();
    }
}