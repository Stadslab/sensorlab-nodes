#include "DHT.h"
#include "config.h"
#include <Adafruit_NeoPixel.h>

#define DHTPIN D5
#define DHTTYPE DHT11

AdafruitIO_Feed *TempN1 = io.feed("TempN1");
AdafruitIO_Feed *HumN1 = io.feed("HumN1");
AdafruitIO_Feed *LuxN1 = io.feed("LuxN1");

DHT dht(DHTPIN, DHTTYPE);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, D4, NEO_GRB + NEO_KHZ800);

void setup() {
   pixels.begin();
  // setup serial.
  Serial.begin(115200);
  pixels.setPixelColor(0, pixels.Color(25,25,0));
  pixels.show();
  while(! Serial);
  Serial.println(F("Sensorlab Node 1"));
  
  //wifi connection.
  Serial.print("Verbinden met Adafruit.io");
  io.connect();
  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
    pixels.setPixelColor(0, pixels.Color(0,0,50));
    pixels.show();
  Serial.println();
  Serial.println(io.statusText());
  
  dht.begin();
  
  Serial.println(F("Klaar!"));
  pixels.setPixelColor(0, pixels.Color(0,50,0));
  pixels.show();
}

void loop() {
io.run();
pixels.setPixelColor(0, pixels.Color(0,0,50));
pixels.show();
TempN1->save(dht.readTemperature());
HumN1->save(dht.readHumidity());
LuxN1->save(1023-analogRead(A0));

pixels.setPixelColor(0, pixels.Color(0,50,0));
pixels.show();

delay(5000);
}


