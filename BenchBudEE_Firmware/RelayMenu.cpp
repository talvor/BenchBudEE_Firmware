//
// RelayMenu.cpp
// Library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 19/06/2014 9:51 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014


// Library header
#include "RelayMenu.h"

extern Relay relay;

// Code
void relay_TurnOn(MenuItem* menu_item) {
    relay.on();
}

void relay_TurnOff(MenuItem* menu_item) {
    relay.off();
}

void relay_Toggle(MenuItem* menu_item) {
    relay.toggle();
}

void relay_StartOscillate(MenuItem* menu_item) {
    relay.startOscillate(1000);
}

void relay_StopOscillate(MenuItem* menu_item) {
    relay.stopOscillate();
    relay.off();
}

Menu* relayMenuSetup() {
    Menu *menu = new Menu("Relay");
    
    MenuItem *menuItem = new MenuItem("Turn on");
    menu->add_item(menuItem, &relay_TurnOn);
    
    menuItem = new MenuItem("Turn off");
    menu->add_item(menuItem, &relay_TurnOff);
    
    menuItem = new MenuItem("Toggle on/off");
    menu->add_item(menuItem, &relay_Toggle);
    
    menuItem = new MenuItem("Start continuous toggling");
    menu->add_item(menuItem, &relay_StartOscillate);

    menuItem = new MenuItem("Stop continuous toggling");
    menu->add_item(menuItem, &relay_StopOscillate);

    return menu;
}
