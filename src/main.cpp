#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
//parametri WiFi
#define WLAN_SSID "TM Family"
#define WLAN_PASS "MeddaFamily2?"


//n.b 13 e 14 invertiti
#define GREEN   13
#define RED    12
#define BLUE  14

// PROTOTIPI FUNZIONI
void runServer();
void wiFiStart();

WiFiClient client;
AsyncWebServer server(80);
String command= "";

void select_light(String c){
  //int res;
  if(c=="OFF"){
    //res=0;
      ledcWrite(1, 0);
      ledcWrite(2, 0);
      ledcWrite(3, 0);
  }

  if(c=="ON"){
    //res=1;
      ledcWrite(1, 255);
      ledcWrite(2, 255);
      ledcWrite(3, 255);
  }

  if(c=="GREEN"){
    //res=2;
    ledcWrite(1, 255);
    ledcWrite(2, 0);
    ledcWrite(3, 0);
  }

  if(c=="RED"){
    //res=3;
    ledcWrite(1, 0);
    ledcWrite(2, 255);
    ledcWrite(3, 0);
  }

  if(c=="BLUE"){
    //res=4;
    ledcWrite(1, 0);
    ledcWrite(2, 0);
    ledcWrite(3, 255);
  }
  //return res;
}


void runServer(){

  server.on("/Control", HTTP_GET, [] (AsyncWebServerRequest *request) {
    command=request->getParam("command")->value();
    select_light(command);
    request->send(204); //rsp
  });
}

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
  Serial.begin(9600);
  ledcAttachPin(GREEN,1);
  ledcAttachPin(RED,2);
  ledcAttachPin(BLUE,3);

  //inizializzo i canali con ledcSetup(channel, frequency, resolution)
  ledcSetup(1,12000 ,8);
  ledcSetup(2,12000 ,8);
  ledcSetup(3,12000 ,8);

  /*azzero tutti i canali
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);*/
  wiFiStart();
  runServer();
}

void loop() {
  delay(100);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
