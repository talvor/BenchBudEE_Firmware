//
// FanMenu.cpp
// Library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 19/06/2014 10:04 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014


// Library header
#include "FanMenu.h"
#include "Fan.h"

extern Fan fan;

int fanSpeed = 255;

// Code

void fan_turnOn(MenuItem* menu_item) {
    fan.on();
}

void fan_turnOff(MenuItem* menu_item) {
    fan.off();
}

void fan_increaseSpeed(MenuItem* menu_item) {
    int speed = fan.getSpeed();
    speed = speed + FAN_SPEED_STEP;
    fan.setSpeed(speed);
}

void fan_decreaseSpeed(MenuItem* menu_item) {
    int speed = fan.getSpeed();
    speed = speed - FAN_SPEED_STEP;
    fan.setSpeed(speed);
}

Menu* fanMenuSetup() {
    Menu *menu = new Menu("Fan");
    
    MenuItem *menuItem = new MenuItem("Turn on");
    menu->add_item(menuItem, &fan_turnOn);
    
    menuItem = new MenuItem("Turn off");
    menu->add_item(menuItem, &fan_turnOff);
    
    menuItem = new MenuItem("Increase Speed");
    menu->add_item(menuItem, &fan_increaseSpeed);

    menuItem = new MenuItem("Decrease Speed");
    menu->add_item(menuItem, &fan_decreaseSpeed);
    
    return menu;
}