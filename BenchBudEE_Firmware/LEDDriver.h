//
// File			LEDDriver.h
// Class library header
//
// Details		<#details#>
//
// Project	 	BenchBudEE_MenuSystem
//
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			22/06/2014 2:19 pm
// Version		<#version#>
//
// Copyright	© Phillip Hall, 2014


// Core library
#include "Arduino.h"

#ifndef LEDDriver__h
#define LEDDriver__h


class LEDDriver {
  
public:
    LEDDriver(int pin);
    void begin();
    
    void on();
    void off();
    
    void setBrightness(int brightness);
    int getBrightness() ;
    
    int printData();
  
private:
    bool    _on;
    int     _pin;
    int     _brightness;
};

#endif
