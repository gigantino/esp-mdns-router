#include "secrets.h"
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char* ssid = MASTER_SSID;
const char* password = MASTER_PASSWORD;

void setup()
{
    Serial.begin(115200);

    // connect to the master
    WiFi.begin(ssid, password);
    Serial.println("[~] Connecting to " + String(MASTER_SSID));

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print('.');
    }

    // log the IP address once the connection is successful
    Serial.println("\n[*] Connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        // e.g. http://master.local/?value=1024
        String serverPath = "http://" + String(MASTER_HOST_NAME) + ".local/?value=" + String(analogRead(0));
        Serial.println(serverPath);

        http.begin(client, serverPath.c_str());

        int httpResponseCode = http.GET();

        if (httpResponseCode > 0) {
            Serial.print("HTTP response code: ");
            Serial.println(httpResponseCode);
            String payload = http.getString();
            Serial.println(payload);
        } else {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("Disconnected!");
    }
}