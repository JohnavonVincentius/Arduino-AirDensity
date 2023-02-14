#include <math.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C

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

//---------- Calculate Moist Air Density ----------//
float CalcMAD(float Pressure,float Temperature,float Humidity){
  float Pd;
  float Pv;
  float TempK;
  
  float Pair;

  float Rd = 287.05;
  float Rv = 461.495;

  Pd = CalcPPDA(Pressure,Temperature,Humidity);
  Pv = CalcPVP(Humidity,Temperature);
  TempK = Temperature + 273.15;

  Pair = (Pd/(Rd*TempK))+(Pv/(Rv*TempK));
  return Pair*100;
}

//---------- Calculate partial pressure of dry air ----------//
float CalcPPDA(float Pressure,float Temperature,float Humidity){
  float Pd;
  float Pv = CalcPVP(Humidity,Temperature);
  Pd = Pressure-Pv;
  return Pd;
}

//---------- Calculating water vapor partial pressure ----------//
float CalcPVP(float Humidity,float Temperature){
  float pT;   //
  float Es;
  float Pv;

  float c0 = 0.99999683;
  float c1 = -0.90826951E-2;
  float c2 = 0.78736169E-4;
  float c3 = -0.61117958E-6;
  float c4 = 0.43884187E-8;
  float c5 = -0.29883885E-10;
  float c6 = 0.21874425E-12;
  float c7 = -0.17892321E-14;
  float c8 = 0.11112018E-16;
  float c9 = -0.30994571E-19;

  pT = c0 + Temperature*(c1 + Temperature*(c2 + Temperature*(c3 + Temperature*(c4 + Temperature*(c5 + Temperature*(c6 + Temperature*(c7+ Temperature*(c8 + (Temperature*c9)))))))));
  Es = 6.1078/pow(pT,8);

  Pv = Es*Humidity;
  return Pv;
}

//---------- Calculate Dry Air Density ----------//
float CalcDryDensity(float Pressure,float Temp){ //Dry Air Density Calculate function. Preassure(hPa),Temperature(C/K),Rair(Gas Constant)
  float Rair = 287.05 ;//Spesific gas constant of dry air
  float TempK;
  float Pa;
  Pa = Pressure*100; //Convert hPa to Pa
  TempK = Temp + 273.15;
  float DryAirDensity = (Pa/(TempK*Rair));   // Calculates Air Density by Ideal Gas Law
  return DryAirDensity;
}

//---------- Calculate Dew Point ----------//
float CalcDewPoint(float Humidity,float Temperature){
  float Acoeff;
  float DewPoint;

  Acoeff = log(Humidity)+((17.62*Temperature)/(243.12+Temperature)); // Calculate Alpha Magnus coefficient
  DewPoint = (243.12*Acoeff)/(17.62-Acoeff); // Calculate Dew Point
  return DewPoint;
}