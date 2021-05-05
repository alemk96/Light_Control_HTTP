#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//Wifi parameters
#define WLAN_SSID "your_ssid"
#define WLAN_PASS "Your_password"



#define GREEN //your green pin
#define RED   //your red pin
#define BLUE  //your blue pin




WiFiClient client;
AsyncWebServer server(80);
String command= "";
String value_temp;
String value_hum;

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

  server.on("/control", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if(request->hasParam("command")){
      command=request->getParam("command")->value();
      Serial.println(command);
      select_light(command);
      request->send(200, "text/plain",command);
    }
  });
  server.on("/temperature", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if(request->hasParam("value")){
      value_temp=request->getParam("value")->value();
      request->send(204);
    }
  });

  server.on("/humidity", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if(request->hasParam("value")){
      value_hum=request->getParam("value")->value();
      request->send(204);
    }
  });


  server.on("/status", HTTP_GET, [] (AsyncWebServerRequest *request) {
      request->send(200, "text/plain", "Temperature: "+value_temp+"°C"+"\nHumidity: "+value_hum+"%");

  });

  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404);
  });


  // start server

  server.begin();
}

void OTAStart(){
  // Port defaults to 3232
// ArduinoOTA.setPort(3232);

// Hostname defaults to esp3232-[MAC]
 ArduinoOTA.setHostname("SET_HOSTNAME");

// No authentication by default
 ArduinoOTA.setPassword("SET_PASSOWORD");

// Password can be set with it's md5 value as well
// MD5(earthshield) 
//ArduinoOTA.setPasswordHash("a5214546592fc28db1dd03d694368cff");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
}
//WIFI 
void wiFiStart(){
  
    WiFi.mode(WIFI_STA);
    WiFi.begin(WLAN_SSID,WLAN_PASS);
    Serial.println();
    Serial.print("Waiting for WiFi...");

    
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

  
  ledcSetup(1,12000 ,8);
  ledcSetup(2,12000 ,8);
  ledcSetup(3,12000 ,8);

  
  wiFiStart();
  OTAStart();
  runServer();
}

void loop(){
  ArduinoOTA.handle();
  delay(100);
}







