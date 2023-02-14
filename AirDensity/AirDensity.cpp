#include "AirDensity.h"
#include <math.h>
//---------- Calculate Moist Air Density ----------//
float CalcMAD(float Pressure,float Temperature,float Humidity){
  float Pd;
  float Pv;
  float Rd = 287.05;
  float Rv = 461.495;
  Pd = CalcPPDA(Pressure,Temperature,Humidity);
  Pv = CalcPVP(Humidity,Temperature);
  return (Pd/(Rd*(Temperature + 273.15)))+(Pv/(Rv*(Temperature + 273.15)))*100;
}


//---------- Calculate partial pressure of dry air ----------//
float CalcPPDA(float Pressure,float Temperature,float Humidity){
  return Pressure - CalcPVP(Humidity,Temperature);
}


//---------- Calculating water vapor partial pressure ----------//
float CalcPVP(float Humidity,float Temperature){
  float pT;   //
  float Es;
  pT = 0.99999683 + Temperature*(-0.90826951E-2 + Temperature*(0.78736169E-4 + Temperature*(-0.61117958E-6 + Temperature*(0.43884187E-8 + Temperature*(-0.29883885E-10 + Temperature*(0.21874425E-12 + Temperature*(-0.17892321E-14+ Temperature*(0.11112018E-16 + (Temperature*-0.30994571E-19)))))))));
  Es = 6.1078/pow(pT,8);
  return Es*Humidity;
}


//---------- Calculate Dry Air Density ----------//
float CalcDryDensity(float Pressure,float Temp){ //Dry Air Density Calculate function. Preassure(hPa),Temperature(C/K),Rair(Gas Constant)
  float Rair = 287.05 ;//Spesific gas constant of dry air
  return ((Pressure*100)/((Temp + 273.15)*Rair));
}


//---------- Calculate Dew Point ----------//
float CalcDewPoint(float Humidity,float Temperature){
  float Acoeff;
  Acoeff = log(Humidity)+((17.62*Temperature)/(243.12+Temperature)); // Calculate Alpha Magnus coefficient
  return (243.12*Acoeff)/(17.62-Acoeff);
}