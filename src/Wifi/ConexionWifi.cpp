#include "config/conexiones.h"
#include "Wifi/ConexionWifi.h"
#include <Arduino.h>

void ConexionWifi::init()
{
    connectWiFi();
};

void ConexionWifi::loop() {
    checkWiFi();
};

void ConexionWifi::connectWiFi()
{
    Serial.printf("Conectando a WiFi %s", WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.printf("\nWiFi conectado. IP: %s\n");
};

void ConexionWifi::checkWiFi()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("WiFi perdido, intentando reconectar...");
        WiFi.disconnect();
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
        unsigned long startAttemptTime = millis();

        // Esperar hasta reconexión o timeout (10 segundos)
        while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000)
        {
            delay(500);
            Serial.print(".");
        }

        if (WiFi.status() == WL_CONNECTED)
            Serial.printf("\nWiFi reconectado. IP: %s\n", WiFi.localIP().toString().c_str());
        else
            Serial.println("\nNo se pudo reconectar al WiFi.");
    }
};