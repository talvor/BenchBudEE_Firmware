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
#include "LEDDriver.h"

#define LED_BRIGHTNESS_STEP 10

extern LEDDriver led;

// Code
void led_turnOn(MenuItem* menu_item) {
    led.on();
}

void led_turnOff(MenuItem* menu_item) {
    led.off();
}

void led_increaseSpeed(MenuItem* menu_item) {
    int brightness = led.getBrightness();
    brightness = brightness + LED_BRIGHTNESS_STEP;
    led.setBrightness(brightness);
}

void led_decreaseSpeed(MenuItem* menu_item) {
    int brightness = led.getBrightness();
    brightness = brightness - LED_BRIGHTNESS_STEP;
    led.setBrightness(brightness);
}


Menu* ledMenuSetup() {
    Menu *menu = new Menu("LED");
    
    MenuItem *menuItem = new MenuItem("Turn on");
    menu->add_item(menuItem, &led_turnOn);
    
    menuItem = new MenuItem("Turn off");
    menu->add_item(menuItem, &led_turnOff);
    
    menuItem = new MenuItem("Increase Brightness");
    menu->add_item(menuItem, &led_increaseSpeed);
    
    menuItem = new MenuItem("Decrease Brightness");
    menu->add_item(menuItem, &led_decreaseSpeed);

    return menu;
}