//
// File			Relay.h
// Class library header
//
// Details		<#details#>
//
// Project	 	BenchBudEE_MenuSystem
//
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			20/06/2014 7:22 am
// Version		<#version#>
//
// Copyright	© Phillip Hall, 2014


// Core library -
#include "Arduino.h"
#include "Constants.h"
#include "Timer.h"

#ifndef Relay__h
#define Relay__h

class Relay {
    
public:
	Relay(int pin);
	~Relay();
    
    void begin(); // Default

    bool isOff(void)  const;
    bool isOn(void)   const;
    void off(void);
    void on(void);
    void toggle(void);

    int printData();
    
    void startOscillate(unsigned long freq);
    void stopOscillate();
    
private:
    bool    _state;
    int     _pin;
    int     _timer;
    unsigned long     _freq;
};

void doOscillate();
#endif
