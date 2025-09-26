#include "dht11/dht11.h"
#include "config/pines.h"

// Definiciones de variables

dht11::dht11(uint8_t pin, int type) : dht(pin, type)
{
    delayMS = 2000;
    T = NAN;
    Rh = NAN;
}

void dht11::init()
{
    iniciarDHT();
};

void dht11::loop() {

};

void dht11::iniciarDHT()
{
    dht.begin();
    Serial.println(F("DHTxx Sensor iniciado"));

    // Mostrar info del sensor
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("°C"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("°C"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("°C"));

    dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print(F("Sensor Type: "));
    Serial.println(sensor.name);
    Serial.print(F("Max Value:   "));
    Serial.print(sensor.max_value);
    Serial.println(F("%"));
    Serial.print(F("Min Value:   "));
    Serial.print(sensor.min_value);
    Serial.println(F("%"));
    Serial.print(F("Resolution:  "));
    Serial.print(sensor.resolution);
    Serial.println(F("%"));

    // Ajustar delay mínimo
    delayMS = sensor.min_delay / 1000;
};

float dht11::getTemperatura()
{
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature))
    {
        Serial.println(F("Error leyendo temperatura!"));
        return NAN;
    }
    return event.temperature;
};
float dht11::getHumedad()
{
    sensors_event_t event;
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity))
    {
        Serial.println(F("Error leyendo humedad!"));
        return NAN;
    }
    return event.relative_humidity;
};

float dht11::getPuntoRocio()
{
    T = getTemperatura();
    Rh = getHumedad();
    const float a = 17.27, b = 237.7;
    float gamma = (a * T) / (b + T) + log(Rh / 100.0);

    if (Rh <= 0 || Rh > 100)
    {
        return NAN;
    }
    return (b * gamma) / (a - gamma);
};
float dht11::getSensacionTermica()
{
    T = getTemperatura();
    Rh = getHumedad();
    float ST = -8.784695 + 1.61139411 * T + 2.338549 * Rh - 0.14611605 * T * Rh - 0.012308094 * T * T - 0.016424828 * Rh * Rh + 0.002211732 * T * T * Rh + 0.00072546 * T * Rh * Rh - 0.000003582 * T * T * Rh * Rh;

    return ST;
};

//--- Función para llamar desde loop ---

void dht11::datosTemperatura()
{
    delay(delayMS);

    float temp = getTemperatura();
    float hum = getHumedad();
    float puntoRosio = getPuntoRocio();
    float senTermica = getSensacionTermica();

    Serial.printf("------------INFORMACION DE TEMPERATURA-----\n\n");

    if (!isnan(temp) && !isnan(hum))
    {
        Serial.printf("Temperatura: %.2f °C\n", temp);
        Serial.printf("Humedad: %.2f %\n", hum);
        Serial.printf("Punto de rosio: %.2f °C\n", puntoRosio);
        Serial.printf("Sensacion termica: %.2f °C\n", senTermica);
    }
}

