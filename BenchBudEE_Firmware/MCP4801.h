//
// File			MCP4801.h
// Class library header
//
// Details		<#details#>
//
// Project	 	BenchBudEE_MenuSystem
//
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			20/06/2014 9:02 pm
//
// Copyright	© Phillip Hall, 2014


// Core library
#include "Arduino.h"
#include "Constants.h"

#ifndef MCP4801__h
#define MCP4801__h

#define VREF 2.048
#define RES8BIT 256
#define WR_ENABLE 0
#define GAIN 1

class MCP4801 {
  
public:
    MCP4801(int slaveSelectLowPin, int shutdownLowPin);

    //Configuration methods
    void begin(); // Default
    
    //Functionality methods
    int setValue(int value);
    int setVoltageOutput(float voltage);
    
private:
    int _shutdownLowPin;
    int _slaveSelectLowPin;
};

#endif
