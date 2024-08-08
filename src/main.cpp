#include <Arduino.h>
#include <string.h>
#include <Adafruit_NeoPixel.h>
#define LED_COUNT 5
#define LED_PIN 3

Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);

void setup(){
  pixels.begin();
  pixels.clear();
  pixels.show();
  Serial.begin(9600);
}
int lastSerialTime_ms = 0;
const int luminus = 20;
auto correctColor = pixels.Color(0, luminus, 0);
auto incorrectColor = pixels.Color(luminus, 0, 0);

void loop(){
  if (Serial.available() > 0){
    String receive = Serial.readStringUntil('\n');
    for(u_int i = 0; i < LED_COUNT; i++){
      if (i >= receive.length()){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        continue;
      }
      if (receive[i] == '1'){
        pixels.setPixelColor(i, correctColor);
      }else{
        pixels.setPixelColor(i, incorrectColor);
      }
    }
    lastSerialTime_ms = millis();
  }else{
    int currentTime_ms = millis();
    if(currentTime_ms - lastSerialTime_ms > 1500){
      for(int i = 0; i < LED_COUNT; i++){
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      }
    }
  }
  pixels.show();
  delay(500);
  // pixels.clear();
}
