//
// Relay.cpp
// Class library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 20/06/2014 7:22 am
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014


// Library header
#include "Relay.h"

extern Timer hardwareTimer;
extern Relay relay;

// Code
Relay::Relay(int pin): _pin(pin) {
    _timer = -1;
    _state = false;
}

Relay::~Relay() {
	pinMode(_pin, LOW);
    pinMode(_pin, INPUT);
}

void Relay::begin() {
    _timer = -1;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
}

// Relay isOff --
//  Returns true if the relay is de-enervized.  Returns false otherwise.
//
bool Relay::isOff(void) const {
    return(!_state);
}

// Relay isOn --
//  Returns true if the relay is energized. Returns false otherwise.
//
bool Relay::isOn(void) const {
    return(_state);
}

// Relay off --
//  De-energizes the relay.
//
void Relay::off() {
    digitalWrite(_pin, LOW);
    _state  = false;
}

// Relay on --
//  Energizes the relay.
//
void Relay::on() {
    digitalWrite(_pin, HIGH);
    _state  = true;
}

// Relay toggle --
//  Toggles the relays on/off state
//
void Relay::toggle(void) {
    _state ? this->off() : this->on();
}

void Relay::startOscillate(unsigned long freq) {
    _freq = freq;
    if (_timer == -1) {
        _timer = hardwareTimer.every(_freq, doOscillate);
    }
}

void Relay::stopOscillate() {
    if(_timer != -1) {
        hardwareTimer.stop(_timer);
    }
    
    _timer = -1;
}

int Relay::printData() {
    Serial.print("Relay: State = ");
    if(_state) {
        Serial.println(" on");
    } else {
        Serial.println(" off");
    }
    
    return 1;
}

void doOscillate() {
    relay.toggle();
}