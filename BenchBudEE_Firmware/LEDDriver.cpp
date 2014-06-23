//
// LEDDriver.cpp
// Class library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 22/06/2014 2:19 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014


// Library header
#include "LEDDriver.h"

// Code
LEDDriver::LEDDriver(int pin) {
    _pin = pin;
    _brightness = 0;
}

void LEDDriver::begin() {
    pinMode(_pin, OUTPUT);
    analogWrite(_pin, _brightness);
}


void LEDDriver::on() {
    _brightness = 255;
    analogWrite(_pin, _brightness);
    _on = true;
}

void LEDDriver::off() {
    _brightness = 0;
    analogWrite(_pin, _brightness);
    _on = false;
}

void LEDDriver::setBrightness(int brightness) {
    if (brightness < 0) {
        brightness = 0;
    }
    _brightness = constrain(brightness, 0, 255);
    analogWrite(_pin, brightness);
}

int LEDDriver::getBrightness() {
    return _brightness;
}

int LEDDriver::printData() {
    Serial.print("LED: ");
    if (_on) {
        Serial.print("On - Brightness = ");
        Serial.println(_brightness);
    } else {
        Serial.println("Off ");
    }
    
    return 1;
}