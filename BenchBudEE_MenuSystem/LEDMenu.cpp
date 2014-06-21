//
// LEDMenu.cpp 
// Library C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 19/06/2014 10:43 pm
// 				Phillip Hall
//
// Copyright 	© Phillip Hall, 2014

// Library header
#include "LEDMenu.h"

// Code
void on_LEDMenu(MenuItem* menu_item) {

}

Menu* ledMenuSetup() {
    Menu *menu = new Menu("LED");
    
    MenuItem *menuItem = new MenuItem("Turn on");
    menu->add_item(menuItem, &on_LEDMenu);
    
    menuItem = new MenuItem("Turn off");
    menu->add_item(menuItem, &on_LEDMenu);
    
    menuItem = new MenuItem("Toggle on/off");
    menu->add_item(menuItem, &on_LEDMenu);

    menuItem = new MenuItem("PWM Ramp up");
    menu->add_item(menuItem, &on_LEDMenu);

    return menu;
}