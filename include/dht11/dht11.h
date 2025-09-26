#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>

class dht11
{
public:
    dht11(uint8_t DHT_PIN, int type = DHT11);
    void init();
    void loop();
    void datosTemperatura();
    float getTemperatura();
    float getHumedad();
    float getPuntoRocio();
    float getSensacionTermica();


private:
    DHT_Unified dht;  // Objeto del sensor
    uint32_t delayMS; // Tiempo mínimo entre lecturas
    float T;          // Última lectura de temperatura
    float Rh;         // Última lectura de humedad

    void iniciarDHT();
};

#endif