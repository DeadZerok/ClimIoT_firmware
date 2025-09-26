#ifndef CONEXIONWIFI_H
#define CONEXIONWIFI_H

#include <WiFi.h>
#include <WiFiClientSecure.h>

class ConexionWifi
{
public:
    static void init();
    static void loop();

private:
    static void connectWiFi();
    static void checkWiFi();
};

#endif