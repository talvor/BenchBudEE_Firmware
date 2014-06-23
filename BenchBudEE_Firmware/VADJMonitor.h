//
// File			VADJMonitor.h
// Class library header
//
// Details		<#details#>
//
// Project	 	BenchBudEE_MenuSystem
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			21/06/2014 3:31 pm
// Version		<#version#>
//
// Copyright	© Phillip Hall, 2014

// Core library
#include "Arduino.h"

#ifndef VADJMonitor__h
#define VADJMonitor__h

#define REFVOLTS 5.0
#define R1 3000
#define R2 1000

class VADJMonitor {
  
public:
    VADJMonitor(int vadjMonitorPin);
	~VADJMonitor();
    
    //Configuration methods
    void begin(); // Default
    void end();
    void read();
    
    int printData();
    
    float value;
    float voltage;
    
private:
    int _vadjMonitorPin;
    int _vadjMonitorTimer;
    float _denominator;
};

void vadjMonitorRead();

#endif
