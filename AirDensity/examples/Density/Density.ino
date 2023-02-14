#include <AirDensity.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  if (!bme.begin(0x76)) {
    Serial.println("BME280 INIT FALIURE");
    while (1);
  }
}

void loop() {
  float T = bme.readTemperature();
  float H = bme.readHumidity()/100;
  float P = bme.readPressure() / 100.0F;

  Serial.print("Temperature:");
  Serial.println(T);

  Serial.print("Humidity:");
  Serial.println(H);

  Serial.print("Pressure:");
  Serial.println(P);


  Serial.print("Dew Point:");
  Serial.println(CalcDewPoint(H,T));

  Serial.print("Dry Air Preassure:");
  Serial.println(CalcPPDA(P,T,H));

  Serial.print("Water Vapor Preassure:");
  Serial.println(CalcPVP(H,T));

  Serial.print("Air Density:");
  Serial.println(CalcMAD(P,T,H),4);
  delay (1000);
}
