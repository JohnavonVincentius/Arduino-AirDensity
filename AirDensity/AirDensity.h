#ifndef AirDensity_h
    #define AirDensity_h
    #include <Arduino.h>
    #include <math.h>

    float CalcMAD(float Pressure,float Temperature,float Humidity); //---------- Calculate Moist Air Density ----------//
    float CalcPPDA(float Pressure,float Temperature,float Humidity);
    float CalcPVP(float Humidity,float Temperature);
    float CalcDryDensity(float Pressure,float Temp);
    float CalcDewPoint(float Humidity,float Temperature);
    
#endif