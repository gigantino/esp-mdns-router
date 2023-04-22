#include "secrets.h"
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESPmDNS.h>

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

    // initialize the mDNS
    if (!MDNS.begin(SLAVE_HOST_NAME)) {
        Serial.println("[!] Error setting up mDNS.");
        while (1) {
            delay(1000);
        }
    }
    Serial.println("[+] mDNS set-up as: " + String(SLAVE_HOST_NAME) + ".local");
}

void loop()
{
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        // e.g. http://master.local/?value=1024
        String requestPath = "http://" + String(MASTER_HOST_NAME) + ".local/?value=" + String(analogRead(0));
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