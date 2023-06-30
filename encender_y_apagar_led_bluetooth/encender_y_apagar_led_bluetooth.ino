#include <SoftwareSerial.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>


OneWire ourWire(5);
DallasTemperature sensors(&ourWire);

#define LEDRED 2

char RECEPCIONLED;

SoftwareSerial BLUEANG(10, 11); // RX,TX
void setup() {
  pinMode(LEDRED, OUTPUT);
  Serial.begin(9600);
  BLUEANG.begin(38400);
  sensors.begin();
  
}

void loop() {
  LEDPRENDER();
  TEMPERATURE();






  
}

void TEMPERATURE (void)
{
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  BLUEANG.print(tempC);
  BLUEANG.println(" ºC");
  delay(1000);
}

void LEDPRENDER (void)
{
  if(BLUEANG.available() ) {
    RECEPCIONLED=BLUEANG.read();
    Serial.print(RECEPCIONLED);
    if(RECEPCIONLED=='1')
    {
      Serial.print("ENCENDIDO");
      digitalWrite(LEDRED,HIGH);
    }
    if(RECEPCIONLED=='2')
    {
      Serial.print("APAGADO");
      digitalWrite(LEDRED,LOW);
    }

  }
  
}
