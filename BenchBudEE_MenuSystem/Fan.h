//
// File			Fan.h
// Class library header
//
// Details		<#details#>
//
// Project	 	BenchBudEE_MenuSystem
//
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			21/06/2014 9:20 pm
// Version		<#version#>
//
// Copyright	© Phillip Hall, 2014



// Core library
#include "Arduino.h"


#ifndef Fan__h
#define Fan__h


class Fan {
public:
    Fan(int enablePin, int pwmPin);
    
    void begin();
    
    void on();
    void off();
    
    void setSpeed(int speed);
    int getSpeed() ;
    
    int printData();
    
private:
    bool    _on;
    int     _enablePin;
    int     _pwmPin;
    int     _speed;
    
};

#endif
