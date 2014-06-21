// 
// BenchBudEE_MenuSystem 
//
// BenchBudEE Menu System
// Developed with [embedXcode](http://embedXcode.weebly.com)
// 
// Author	 	Phillip Hall
// 				Phillip Hall
//
// Date			19/06/2014 9:47 pm
// Version		1.0
// 
// Copyright	© Phillip Hall, 2014

// This sketch runs a number of timers perform the following tasks
//    - collect data from the hardware devices
//    - execute repetitive tasks
//
// The display system will be in one of two modes;
//    - Data mode (Displays information from the hardware devices on screen)
//    - Menu mode (Displays the menu system)
// The modes are switched out via key presses.  The Display starts in Data mode and when a keypress
// is registered it will switch to Menu mode.  Then when no key presses are registered for 3 seconds
// the display mode will switch back to Data mode


// Core library for code-sense
#include "Arduino.h"
#include "Constants.h"
#include "MenuSystem.h"
#include "Timer.h"
#include "SPI.h"

// Menu modules
#include "FanMenu.h"
#include "LEDMenu.h"
#include "RelayMenu.h"

// Hardware Objects
#include "Relay.h"
#include "MCP4801.h"
#include "Fan.h"
#include "VADJMonitor.h"

// Utilities
#include "Display.h"

//
// Brief	Setup
// Details  Define variables and constants
Timer hardwareTimer;
Timer displayTimer;

int serialHandlerLastKeyPressed; // When was the last key press registered.

//
// Brief	Setup
// Details	Create system objects
MenuSystem menuSystem;
Menu rootMenu("BenchBudEE");

//
// Brief	Setup
// Details	Create hardware objects
Relay relay(RELAY_ENABLE);
MCP4801 mcp4801(DAC_CS_N, DAC_SHDN_N);
Fan fan(FAN_MODE, FAN_PWM);
VADJMonitor vadjMonitor(VADJ_MON);

//
// Brief	Setup
void setup() {
    Serial.begin(9600);

    SPI.setClockDivider(SPI_CLOCK_DIV128);
    SPI.setDataMode(SPI_MODE0);
    SPI.begin();
    
    rootMenu.add_menu(fanMenuSetup());
    rootMenu.add_menu(ledMenuSetup());
    rootMenu.add_menu(relayMenuSetup());

    menuSystem.set_root_menu(&rootMenu);
    
    relay.begin();
    mcp4801.begin();
    fan.begin();
    vadjMonitor.begin();
    
    displayStartDataTimer();
    
}

//
// Brief	Loop

void serialHandler();

void loop() {
    hardwareTimer.update();
    displayTimer.update();
    
    serialHandler();
}

void serialHandler() {
    char inChar;
    if((inChar = Serial.read())>0) {
        if (displayMode() == DISPLAY_MODE_DATA) {
            displayStopDataTimer();
            displayRedrawMenu();
            
        } else {
            switch (inChar) {
                case 'w': // Previous item
                    menuSystem.prev();
                    displayRedrawMenu();
                    break;
                case 's': // Next item
                    menuSystem.next();
                    displayRedrawMenu();
                    break;
                case 'a': // Back pressed
                    menuSystem.back();
                    displayRedrawMenu();
                    break;
                case 'd': // Select pressed
                    menuSystem.select(false);
                    displayRedrawMenu();
                    break;
                default:
                    break;
            }
        }
        
        displayDelayDataTimer();
    }
}
