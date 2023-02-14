# Arduino-AirDensity
Library to calculate air density and others from BME280/DHT/Other Sensors.

This library uses the given Temperature,Humidity and Pressure in air and calculates the approximate Air Density.The accuracy of this prediction is based on the accuracy of the used sensors and the constants in the code, feel free to change the constants.


# Compatibility 
This library should work with any sensors, The library calculates the Air Density based on the Temperature,Humidity and Preassure of the air.

There seems to be an issue running the library on an ESP8266, The example library uses 93% of memory and sometimes had caused the ESP to crash with OOM(Out Of Memory ) Error


| IC | Compatibility |
|----|---------------|
|ESP-8266| Possible OOM error|
|ESP-32 | Not Tested | 
|Arduino Uno |OK|
|Arduino Pro Mini | OK|
|Arduino Nano | OK|
|Arduino Mega | Not Tested,But OK?|

# Uses

```cpp
  CalcMAD(float Pressure,float Temperature,float Humidity);  //---------- Calculate Moist Air Density ----------//
  CalcPPDA(float Pressure,float Temperature,float Humidity); //---------- Calculate partial pressure of dry air ----------//
  CalcPVP(float Humidity,float Temperature);                 //---------- Calculating water vapor partial pressure ----------//
  CalcDryDensity(float Pressure,float Temp);                 //---------- Calculate Dry Air Density ----------//
  CalcDewPoint(float Humidity,float Temperature);            //---------- Calculate Dew Point ----------//
```
- Pressure : hPa
- Temperature : °C
- Humidity : %
  

# Examples
This Examples uses BME280 to read temperature,humidity and pressure.

```cpp
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
```

# Refrences

This Library is based on research at : https://www.emd-international.com/files/windpro/WindPRO_AirDensity.pdf
