#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
//parametri WiFi
#define WLAN_SSID "TM Family"
#define WLAN_PASS "MeddaFamily2?"


// PROTOTIPI FUNZIONI
void runServer();
void wiFiStart();

WiFiClient client;
AsyncWebServer server(80);

//WIFI
void wiFiStart(){
  //inizializza la connessione
    WiFi.begin(WLAN_SSID,WLAN_PASS);
    Serial.println();
    Serial.print("Waiting for WiFi...");

    //Verifica della connessione
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("WiFi connected on:");
    Serial.println(WiFi.localIP());

}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}
