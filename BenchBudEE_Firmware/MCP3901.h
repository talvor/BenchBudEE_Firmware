//
// File			MCP3901.h
// Class library header
//
// Details		<#details#>
//
// Project	 	BenchBudEE_MenuSystem
//
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			20/06/2014 9:07 pm
//
// Copyright	© Phillip Hall, 2014
//


// Core library
#include "Arduino.h"
#include "Constants.h"

#ifndef MCP3901__h
#define MCP3901__h


class MCP3901 {
  
public:
    MCP3901(int slaveSelectLowPin, int resetLowPin, int dataReadyLowPin);
    
    //Configuration methods
    void begin(); // Default
    
    //Functionality methods
    float getValue(int channel);
    float getVolts(int channel);

    void readChannels ();
    
    int printData();
    
private:
    int _slaveSelectLowPin;
    int _resetLowPin;
    int _dataReadyLowPin;
    
    float _ch0Value;
    float _ch0Volts;
    float _ch1Value;
    float _ch1Volts;
};

#endif
