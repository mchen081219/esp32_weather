#include <Arduino.h>
#include <WiFi.h>
#include <stdio.h>
#include <FastLED.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h> 

const char * ssid = "15-105-02";
const char * pass = "mc18059681219";
#define Num_led 1
#define Output_gpio 48
#define Color_typ GRB
#define Led_typ WS2812B
CRGB leds[Num_led];
uint8_t max_light = 64;

void setup() {
  LEDS.addLeds<Led_typ,Output_gpio,Color_typ>(leds,Num_led);
  FastLED.setBrightness(max_light);
  WiFi.begin(ssid,pass);
  delay(50);
  while (WiFi.status() != WL_CONNECTED)
  {
     leds[0] = CRGB::White;
     FastLED.show();
     delay(150);
     leds[0] =CRGB::Black;
     FastLED.show();
     delay(100);
  }
  HTTPClient http;
  http.begin("https://devapi.qweather.com/v7/weather/now?location=117.66,24.54&key=6a62c0782b734578a930a8704f67a041");
  delay(50);
  int http_code = http.GET();
  if (http_code != 200)
  {
    for (int i = 0; i < 10; i++)
    {
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(100);
    leds[0] =CRGB::Black;
    FastLED.show();
    delay(50);
    }
  } else {
      for (int i = 0; i < 2; i++)
    {
    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(100);
    leds[0] =CRGB::Black;
    FastLED.show();
    delay(50);
    }
  }  
  delay(500);
  String res = http.getString();
  JsonDocument doc;
  deserializeJson(doc,res);
  String wea = doc["now"]["text"].as<String>();
  int ico = doc["now"]["icon"].as<int>();
  http.end();
  if (ico < 299)
  {
    for (int i = 0; i < 5; i++)
    {
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(100);
    leds[0] =CRGB::Black;
    FastLED.show();
    delay(50);
    }
  } else {
    if (ico == 300 || ico == 306 || ico == 305 || ico == 309 || ico == 314 || ico == 350 || ico ==399)
    {
      for (int i = 0; i < 5; i++) {
      leds[0] = CRGB::Red;
      FastLED.show();
      delay(100);
      leds[0] =CRGB::Black;
      FastLED.show();
      delay(50);
      }
    } else {
      for (int i = 0; i < 5; i++)
      {
      leds[0] = CRGB::Red;
      FastLED.show();
      delay(200);
      leds[0] =CRGB::Black;
      FastLED.show();
      delay(50);
      }
    }
    
  }
  
}

void loop() {

}
