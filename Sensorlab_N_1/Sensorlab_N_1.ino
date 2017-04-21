#include "DHT.h"
#include "config.h"

#define DHTPIN D5
#define DHTTYPE DHT11

AdafruitIO_Feed *TempN1 = io.feed("TempN1");
AdafruitIO_Feed *HumN1 = io.feed("HumN1");
AdafruitIO_Feed *LuxN1 = io.feed("LuxN1");

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // setup serial.
  Serial.begin(115200);
  while(! Serial);
  Serial.println(F("Sensorlab Node 1"));

  //wifi connection.
  Serial.print("Verbinden met Adafruit.io");
  io.connect();
  
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  
  dht.begin();
  
  Serial.println(F("Klaar!"));
}

void loop() {
io.run();
//TemperN1 = dht.readTemperature();
//HumN1 = int(dht.readHumidity());
//LuxN1 = int(analogRead(A0));

//Serial.println(LuxN1, DEC);
//Serial.println(HumN1, DEC);
//Serial.println(TempN1, DEC);

TempN1->save(dht.readTemperature());
HumN1->save(dht.readHumidity());
LuxN1->save(analogRead(A0));
delay(2000);
}


