//
// VADJMonitor.cpp
// Class library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 21/06/2014 3:31 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014


// Library header
#include "VADJMonitor.h"
#include "Timer.h"

#define REFVOLTS 5.0
#define R22 3000
#define R23 1000

extern Timer hardwareTimer;
extern VADJMonitor vadjMonitor;

// Code
VADJMonitor::VADJMonitor(int vadjMonitorPin) {
    _vadjMonitorPin = vadjMonitorPin;
    _vadjMonitorTimer = -1;
    
    //Convert resistor values to division value
    //  Equation is previously mentions voltage divider equation
    //  R2 / (R1 + R2)
    _denominator = (float)R23 / (R22 + R23);
}

VADJMonitor::~VADJMonitor() {
    if(_vadjMonitorTimer != -1)
        hardwareTimer.stop(_vadjMonitorTimer);
    _vadjMonitorTimer = -1;
}

void VADJMonitor::begin() {
    // Configure the Arduino pins
    pinMode(_vadjMonitorPin, INPUT);
    _vadjMonitorTimer = hardwareTimer.every(100, vadjMonitorRead);
}

void VADJMonitor::end() {
    if(_vadjMonitorTimer != -1)
        hardwareTimer.stop(_vadjMonitorTimer);
    _vadjMonitorTimer = -1;
}

void VADJMonitor::read() {
    //Obtain RAW voltage data
    value = analogRead(_vadjMonitorPin);
    
    //Convert to actual voltage (0 - 5 Vdc)
    voltage = (value / 1024) * REFVOLTS;
    
    //Convert to voltage before divider
    //  Divide by divider = multiply
    voltage = voltage / _denominator;
}

int VADJMonitor::printData() {
    Serial.print("VADJ: ");
    Serial.print("Value = ");
    Serial.print(value);
    Serial.print(" Voltage = ");
    Serial.println(voltage);
    
    return 1;
}

void vadjMonitorRead() {
    vadjMonitor.read();
}