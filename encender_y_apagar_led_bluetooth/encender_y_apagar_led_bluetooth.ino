#include <SoftwareSerial.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ticker.h>


OneWire ourWire(5);
DallasTemperature sensors(&ourWire);

#define LEDRED 2

char RECEPCIONLED;

SoftwareSerial BLUEANG(10, 11); // RX,TX
void TEMPERATURE (void);
Ticker isr_accion_TEMP(TEMPERATURE,10000);
void setup() {
  pinMode(LEDRED, OUTPUT);
  Serial.begin(9600);
  BLUEANG.begin(9600);
  sensors.begin();
  isr_accion_TEMP.start();
}

void loop() {
  LEDPRENDER();
 isr_accion_TEMP.update();






  
}

void TEMPERATURE (void)
{
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  BLUEANG.print(tempC);
  BLUEANG.println(" ºC");

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
