#include "config/conexiones.h"
#include "dataBase/dataBaseFire.h"
#include "dht11/dht11.h"
#include "config/pines.h"

// --- Cliente SSL + AsyncClient ---
WiFiClientSecure ssl_client;
using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);

// --- Firebase ---
UserAuth user_auth(API_KEY, USER_EMAIL, USER_PASSWORD, 3000);
FirebaseApp app;
RealtimeDatabase Database;

dht11 sensor(DHT_PIN); // ó dht11 sensor(DHT_PIN, DHT11);



void FirebaseManager::iniciarFireBase()
{
    sensor.init(); 
    Firebase.printf("Firebase Client v%s\n", FIREBASE_CLIENT_VERSION);

    ssl_client.setInsecure();

    Serial.println("Inicializando Firebase...");
    initializeApp(aClient, app, getAuth(user_auth));

    Serial.print("Esperando autenticación");
    while (!app.ready())
    {
        Serial.print(".");
        app.loop();
        delay(200);
    }
    Serial.println("\nFirebase autenticado ");
    app.getApp<RealtimeDatabase>(Database);
    Database.url(DATABASE_URL);
}


void FirebaseManager::loop(){
    objetoDB(DBhis);
};

void FirebaseManager::printLastError()
{
    Serial.print("LastError msg: ");
    Serial.println(aClient.lastError().message().c_str());
    Serial.print("LastError code: ");
    Serial.println(aClient.lastError().code());
}



void FirebaseManager::EscribirEstadoInicial()
{
    String statusPath = "/UsersData/" + String(app.getUid()) + "/status";
    if (Database.set<String>(aClient, statusPath, "online"))
        Serial.println(" Estado inicial escrito: online");
    else
    {
        Serial.println(" Error al escribir estado inicial");
        printLastError();
    }
}

void FirebaseManager::objetoDB(uint32_t delayHis){
    static unsigned long lastMillis = 0;

    app.loop();

    if (millis() - lastMillis > delayHis)
    {
        lastMillis = millis();
        float temp = sensor.getTemperatura();
        float hume = sensor.getHumedad();
        float punrocio = sensor.getPuntoRocio();
        float sentermica = sensor.getSensacionTermica();

        // Crear objeto JSON usando JsonWriter (como en el ejemplo oficial)
        object_t jsonData;
        JsonWriter writer;

        object_t obj1, obj2, obj3, obj4;
        writer.create(obj1, "Temperatura", temp);
        writer.create(obj2, "humedad", hume);
        writer.create(obj3, "punto_rocio", punrocio);
        writer.create(obj4, "Sensacion_Termica", sentermica);

        // Unir los tres objetos en uno solo
        object_t combined;
        writer.join(combined, 4, obj1, obj2, obj3, obj4);

        // Asignar el objeto combinado a jsonData
        jsonData = combined;

        // Ruta para historial de lecturas

        // String path = "/DatosTemperatura";

        // if (Database.push<object_t>(aClient, path, jsonData))
        // {
        //     Serial.printf("Objeto enviado: Temperatura=%.2f, humedad=%.2f, punto de rocio=%.2f, , Sensacion Termica=%.2f\n", temp, hume, punrocio, sentermica);
        // }
        // else
        // {
        //     Serial.println(" Error enviando objeto");
        //     printLastError();
        // }

        // Opcional: Guardar también el último valor en una ruta separada
        String lastReadingPath = "/ActualDatos";
        if (Database.set<object_t>(aClient, lastReadingPath, jsonData))
        {
            Serial.printf("Última lectura actualizada: Temperatura=%.2f, humedad=%.2f, punto de rocio=%.2f, , Sensacion Termica=%.2f\n", temp, hume, punrocio, sentermica);
        }
        else
        {
            Serial.println(" Error actualizando última lectura");
            printLastError();
        }
    }

    app.loop();
};