#include "ESPAsyncWebServer.h"
#include "secrets.h"
#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFi.h>

const char* ssid = MASTER_SSID;
const char* password = MASTER_PASSWORD;

AsyncWebServer server(80);

void setup()
{
    Serial.begin(115200);
    // initialize the access point
    Serial.println("[~] Creating AP...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Serial.print("[+] AP created successfully.");

    // initialize the mDNS
    if (!MDNS.begin(MASTER_HOST_NAME)) {
        Serial.println("[!] Error setting up mDNS.");
        while (1) {
            delay(1000);
        }
    }
    String hostName = MASTER_HOST_NAME;
    Serial.println("[+] mDNS set-up as: " + hostName + ".local");

    // log the parameters and values sent to the main route using a get request
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        int paramsLength = request->params();
        for (int i = 0; i < paramsLength; i++) {
            AsyncWebParameter* parameter = request->getParam(i);
            Serial.print(parameter->name() + ": ");
            Serial.println(parameter->value());
        }
    });
    server.begin();
}

void loop()
{
    // put your main code here, to run repeatedly
}