//
// MCP4801.cpp
// Class library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 20/06/2014 9:02 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014


// Library header
#include "SPI.h"
#include "MCP4801.h"

// Code
MCP4801::MCP4801(int slaveSelectLowPin, int shutdownLowPin) {
    //initialize the pin mapping
    _slaveSelectLowPin = slaveSelectLowPin;
    _shutdownLowPin    = shutdownLowPin;
}

MCP4801::~MCP4801() {
    digitalWrite(_shutdownLowPin, LOW);
    digitalWrite(_slaveSelectLowPin, HIGH);
}

void MCP4801::begin() {
    // Configure the Arduino pins
    pinMode(_shutdownLowPin, OUTPUT);
    pinMode(_slaveSelectLowPin, OUTPUT);
    
    digitalWrite(_shutdownLowPin, HIGH);     //activate
    digitalWrite(_slaveSelectLowPin, HIGH);  //comm. off
}

void MCP4801::end() {
    //turn all pins off
    digitalWrite(_shutdownLowPin, LOW);
    digitalWrite(_slaveSelectLowPin, HIGH);
}

int MCP4801::setValue(int value) {
    word packet = 0;
	packet = value << 4;  //shift voltage setting digits
    packet |= 1 << 12;          //add software activate
    packet |= 1 << 13;   //add gain setting
    
    digitalWrite(_slaveSelectLowPin, LOW);   //set chip as listener
    SPI.transfer(highByte(packet));          //send packet
    SPI.transfer(lowByte(packet));
    digitalWrite(_slaveSelectLowPin, HIGH);  //release chip select

    return 0;
}

int MCP4801::setVoltageOutput(float voltage){
    int              gain_bit = 0;
    unsigned int  volt_digits = 0;
    word packet = 0;
    
    //choose smallest possible range
    if(voltage < VREF){
        gain_bit = 1;
        volt_digits = int( voltage/VREF*RES8BIT );
    }
    else{
        gain_bit = 0;
        volt_digits = int( 0.5*voltage/VREF*RES8BIT );
    }
    
    packet = volt_digits << 4;  //shift voltage setting digits
    packet |= 1 << 12;          //add software activate
    packet |= gain_bit << 13;   //add gain setting
    
    digitalWrite(_slaveSelectLowPin, LOW);   //set chip as listener
    SPI.transfer(highByte(packet));          //send packet
    SPI.transfer(lowByte(packet));
    digitalWrite(_slaveSelectLowPin, HIGH);  //release chip select
    
    return 0;
}