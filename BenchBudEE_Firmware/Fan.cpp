//
// Fan.cpp 
// Class library C++ code
// ----------------------------------
// Developed with embedXcode 
// http://embedXcode.weebly.com
//
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 21/06/2014 9:20 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014
// License     <#license#>
//
// See 			Fan.h and ReadMe.txt for references
//


// Library header
#include "Fan.h"
#include "MCP4801.h"

extern MCP4801 mcp4801;

// Code
Fan::Fan(int enablePin, int pwmPin) {
    _enablePin = enablePin;
    _pwmPin = pwmPin;
}

void Fan::begin() {
    pinMode(_enablePin, OUTPUT);
    digitalWrite(_enablePin,LOW);
    
    pinMode(_pwmPin, OUTPUT);
    _on = false;
}

void Fan::on() {
    mcp4801.setValue(10);
    digitalWrite(_enablePin,HIGH);
    setSpeed(254);
    _on = true;
}

void Fan::off() {
    mcp4801.setValue(0);
    digitalWrite(_enablePin,LOW);
    pinMode(_pwmPin, LOW);
    _on = false;
}

void Fan::setSpeed(int speed) {
    
    _speed = constrain(speed, 0, 254);
    
    int pwm = abs(_speed - 254);

    analogWrite(_pwmPin, pwm);
}

int Fan::getSpeed() {
    return _speed;
}

int Fan::printData() {
    Serial.print("Fan: ");
    if (_on) {
        Serial.print("On - Speed = ");
        Serial.println(_speed);
    } else {
        Serial.println("Off ");
    }
    
    return 1;
}
