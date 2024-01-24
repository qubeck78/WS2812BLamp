
#include <WiFi.h>

#include <ArduinoOTA.h>

#include "lamp.h"
#include "web.h"

//https://deepbluembedded.com/esp32-timers-timer-interrupt-tutorial-arduino-ide/


void setup() 
{
  lampInit();

  WiFi.config( INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE );
  WiFi.setHostname( "LazienkaLampa" );  
  WiFi.begin( "ssid" , "password" );

  ArduinoOTA
    .onStart([]() 
    {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      //Serial.println("Start updating " + type);
    })
    .onEnd([]() 
    {
      //Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) 
    {
      //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) 
    {
      /*
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
      */
    });

  lampSetScene( 1 );

  ArduinoOTA.setHostname( "LazienkaLampa" );
  ArduinoOTA.begin();

  webInit();
  
   
}


void loop() 
{
  
  ArduinoOTA.handle();

  lampMain();
  webMain();
  
}
