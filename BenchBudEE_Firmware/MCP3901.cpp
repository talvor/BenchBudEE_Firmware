//
// MCP3901.cpp
// Class library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 20/06/2014 9:07 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014
//

// Library header
#include "SPI.h"
#include "math.h"
#include "MCP3901.h"
#include "Timer.h"

#define  CHAR_BIT	8

extern Timer hardwareTimer;
extern MCP3901 mcp3901;

void do_readChannels ();
float convertCountToVolts(int counts);

// Code
MCP3901::MCP3901(int slaveSelectLowPin, int resetLowPin, int dataReadyLowPin) {
    _slaveSelectLowPin = slaveSelectLowPin;
    _resetLowPin = resetLowPin;
    _dataReadyLowPin = dataReadyLowPin;
    
}

void MCP3901::begin() {
    pinMode(_slaveSelectLowPin, OUTPUT);
    pinMode(_resetLowPin, OUTPUT);
    pinMode(_dataReadyLowPin, INPUT);
    
    digitalWrite(_resetLowPin, LOW);
    digitalWrite(_resetLowPin, HIGH);

    digitalWrite(_slaveSelectLowPin, HIGH);
    
    hardwareTimer.every(ADC_UPDATE_FREQUENCY, do_readChannels);
}


float MCP3901::getValue(int channel) {
    switch(channel){
        case 0:
            return _ch0Value;
            break;
        case 1:
            return _ch1Value;
            break;
    }
    return 0.0f;
}

float MCP3901::getVolts(int channel) {
    switch(channel){
        case 0:
            return _ch0Volts;
            break;
        case 1:
            return _ch1Volts;
            break;
    }
    return 0.0f;
}

void MCP3901::readChannels () {
    int i, j;
    /* Activate SPI device */
    digitalWrite(_slaveSelectLowPin, LOW);
    
    /* Send device 0, read command for address 0x0 */
    SPI.transfer(0x1);

    for(i=0; i<ADC_NUM_CHAN; i++){
        float value;
        unsigned int cnts = 0;
        
        for(j=0; j<ADC_WIDTH; j++){
            byte ret;
            ret = SPI.transfer(0x0);
            
            cnts += ret;
            cnts <<= (ADC_WIDTH - 1 - j) * CHAR_BIT;
            
        }
        
        value = convertCountToVolts(cnts);
        
        switch(i){
            case 0:
                _ch0Volts = value;
                _ch0Value = cnts;
                break;
            case 1:
                _ch1Volts = value;
                _ch1Value = cnts;
                break;
        }
        
    }
    
    /* Deactivate SPI device */
    digitalWrite(_slaveSelectLowPin, HIGH);
    
}

int MCP3901::printData() {
    // Printout channel 0 data
    Serial.print("ADC Channel 0: ");
    Serial.print("Value = ");
    Serial.print(_ch0Value);
    Serial.print(" Volts = ");
    Serial.println(_ch0Volts);
    
    // Printout channel 1 data
    Serial.print("ADC Channel 1: ");
    Serial.print("Value = ");
    Serial.print(_ch1Value);
    Serial.print(" Volts = ");
    Serial.println(_ch1Volts);
    
    return 2;
}


float convertCountToVolts(int counts)
{
    const int volt_per_cnt = 2.37f / (pow(2,16-1)) / 1 / 3;
    return counts * volt_per_cnt;
}

void do_readChannels() {
    mcp3901.readChannels();
}
