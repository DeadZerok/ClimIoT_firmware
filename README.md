# 🌦️ ClimIoT_firmware: Estación Meteorológica con ESP 32 wroom 32U y DHT11
---

Un proyecto para monitorear las condiciones climáticas en tiempo real utilizando hardware de bajo costo y la potencia del Internet de las Cosas (IoT)! Esta estación meteorológica personal mide la **temperatura**, la **humedad** y la **punto de rosio** y **Sencsacion termica** envía los datos a la nube para su visualización y análisis.

## 📝 Descripción General

**ClimIoT**  En este apartado nos encontraremos con la configuracion del hardware, tanto la configuracion del DHT11 como el envio de datos a la base . Es una solución ideal para entusiastas de la electrónica, estudiantes y cualquiera interesado en recolectar datos meteorológicos locales.

El objetivo principal es **conexion de componentes**,en una **guardado de datos** y **conectividad con la base de tiempo real**  permitiento tener los datos del entorno en firabase.

***

## 🧠 ¿Cómo Funciona?
El sistema es elavorado con la plataforma De **PlatformIO**  y   firebase  personalizada que gestiona los datos enviados por el ESP32 a la base y los guarda en tiempo real.
---

## ⚙️ Tecnologías y Herramientas

* **PlatformIO:** Un framework de React para construir aplicaciones web rápidas y modernas.
* **Firebase:** Una plataforma de Google usada como backend que provee servicios como base de datos en tiempo real.
* **Lenguaje (Firmware)**: **C++** sobre el framework de PlatformIO.
---
## 🚀 Instalación y configuracion

### 1. Conexión del Hardware

Conecta el sensor DHT11 al MIcrocontrolador ESP8266 siguiendo el protocolo I2C:

|  ESP32 wroom32U   | Sensor DHT11  |
| :-------------:   | :-----------: |
|     `VIN o 5V`    |     `VIN`     |
|       `GND`       |     `GND`     |
|      `Pin 16`     |      `S`      |


### 2. Configuración del Software
1.  **Clona este repositorio**:
    ```bash
    git clone [https://github.com/DeadZerok/ClimIoT_firmware](https://github.com/DeadZerok/ClimIoT_firmware)
    ```
2.  **Abre el código** en PlatformIO.
3.  **Instala las librerías necesarias**:
    * `DHT sensor library by Adafruit`
    * `Adafruit Unified Sensor`
    * `FirebaseClient by Mobizt`
4.  **Configura tus credenciales**:
    Modifica el archivo en **[ClimIoT_firmware/include/config
/conexiones.h](https://github.com/DeadZerok/ClimIoT_firmware/blob/master/include/config/conexiones.h)** con el nombre de tu red Wi-Fi, tu contraseña y tu configuracion de  Firebase.
    ```cpp
    const char* ssid = "TU_WIFI";
    const char* password = "TU_PASSWORD";
    const long channelID = TU_CHANNEL_ID;
    const char* writeAPIKey = "TU_WRITE_API_KEY";
    ```
5.  **Sube el código** compila y sube a tu placa ESP 32.

***



## 📊 Visualización de Datos

Puedes visualizarlo en: [ClimIoT](https://climiot.netlify.app/)
---
# Importante !!
Para que funcione correctamente tienes que seguir tambien:  [ClimIoT_Firmware](https://github.com/DeadZerok/ClimIoT)
