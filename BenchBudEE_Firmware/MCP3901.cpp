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

#define  ADC_BIT_16         0xFFFF
#define  ADC_NUM_CHAN       2
#define  ADC_WIDTH          2
#define  ADC_VREF           2.37f
#define  ADC_BITS           16
#define  ADC_GAIN           1
#define  ADC_SINC_ORDER     3
#define  ADC_UPDATE_FREQUENCY 100

#define R60 1000
#define R59 1000

#define  CHAR_BIT	8

const float volt_per_cnt = ADC_VREF / (pow(2,ADC_BITS-1)) / ADC_GAIN / ADC_SINC_ORDER;

extern Timer hardwareTimer;
extern MCP3901 mcp3901;

void do_readChannels ();
float convertCountToVolts(int counts);
float convertVoltsToDegree(float volts);

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
    
    _ch1VoltDivider = (float)R60 / (R59 + R60);
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
                
                _lmt84Volts = _ch1Volts / _ch1VoltDivider;
                _lmt84Temp = convertVoltsToDegree(_lmt84Volts);
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
    Serial.println(_ch0Volts, 4);
    
    // Printout channel 1 data
    Serial.print("ADC Channel 1: ");
    Serial.print("Value = ");
    Serial.print(_ch1Value);
    Serial.print(" Volts = ");
    Serial.println(_ch1Volts, 4);
    
    // Printout Temp
    Serial.print("LMT84: ");
    Serial.print("Volts = ");
    Serial.print(_lmt84Volts, 4);
    Serial.print(" Temp = ");
    Serial.print(_lmt84Temp, 2);
    Serial.println("ºC");
    return 3;
}


float convertCountToVolts(int counts)
{
    return counts * volt_per_cnt;
}

float convertVoltsToDegree(float volts)
{
    float millivolts = volts * 1000;
    
    float dividend = 5.506 - sqrt(pow(-5.506, 2) + (4 * 0.00176 * (870.6-millivolts)));
    float divisor = 2 * -0.00176;
    
    float degreesC = (dividend/divisor)+30;
    
    return degreesC;
    
}

void do_readChannels() {
    mcp3901.readChannels();
}
