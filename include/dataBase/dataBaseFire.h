#ifndef DATABASEFIRE_H
#define DATABASEFIRE_H
#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <FirebaseClient.h>

// --- Cliente SSL + AsyncClient ---
extern WiFiClientSecure ssl_client;
using AsyncClient = AsyncClientClass;
extern AsyncClient aClient;

// --- Firebase ---
extern UserAuth user_auth;
extern FirebaseApp app;
extern RealtimeDatabase Database;
extern AsyncResult databaseResult;

class FirebaseManager
{

public:
    static void printLastError();
    static void iniciarFireBase();
    static void EscribirEstadoInicial();

    void loop();

private:
    void objetoDB(uint32_t delayHis);
};

#endif
