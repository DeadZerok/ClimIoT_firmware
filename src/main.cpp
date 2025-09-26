#include <Arduino.h>
#include "dataBase/dataBaseFire.h"
#include "Wifi/ConexionWifi.h"
#include "dht11/dht11.h"
#include "config/pines.h"

FirebaseManager firebaseManager; 
ConexionWifi conexionWifi;

void setup()
{
  Serial.begin(115200);
  conexionWifi.init();
  firebaseManager.iniciarFireBase();
}

void loop()
{
  conexionWifi.loop();
  firebaseManager.loop();
}
