#include <MemoryFree.h>

//
// Display.cpp 
// C++ code
// ----------------------------------
// Project 		BenchBudEE_MenuSystem
//
// Created by 	Phillip Hall, 20/06/2014 1:16 pm
// 				Phillip Hall
//
// Copyright	© Phillip Hall, 2014



// Core library
#include "Display.h"
#include "MenuSystem.h"
#include "Relay.h"
#include "Fan.h"
#include "VADJMonitor.h"
#include "Timer.h"
#include "LEDDriver.h"
#include "MCP3901.h"
//#include "MemoryFree.h"

// Display modes
#define DISPLAY_MODE_SWITCH_DELAY 1500
#define DISPLAY_UPDATE_FREQUENCY 200

extern MenuSystem menuSystem;
extern Relay relay;
extern VADJMonitor vadjMonitor;
extern Fan fan;
extern Timer displayTimer;
extern LEDDriver led;
extern MCP3901 mcp3901;

int _lineCount = 0;
int _timer = -1;
int _displayMode = -1;

// Code
void printHelp() {
    Serial.println("***************");
    _lineCount++;
    Serial.println("w: up");
    _lineCount++;
    Serial.println("s: down");
    _lineCount++;
    Serial.println("a: previous");
    _lineCount++;
    Serial.println("d: select");
    _lineCount++;
    Serial.println("***************");
    _lineCount++;
    Serial.println("");
    _lineCount++;
}

void clearScreen() {
    _lineCount = 0;
    
    // Clear the screen
    for (int i=0; i < TERM_NUM_LINES; i++) {
        Serial.println("");
    }
}

void padScreen() {
    // Pad out the screen
    for (int i=0; _lineCount < TERM_NUM_LINES; _lineCount++) {
        Serial.println("");
    }
}

void displayRedrawData() {
    clearScreen();
    
    _lineCount = _lineCount + relay.printData();
    _lineCount = _lineCount + fan.printData();
    _lineCount = _lineCount + led.printData();
    _lineCount = _lineCount + mcp3901.printData();
    _lineCount = _lineCount + vadjMonitor.printData();
    
    //Serial.print("Free memory = ");
    //Serial.print(freeMemory());
    //Serial.println(" bytes");
    //_lineCount = _lineCount + 1;
    
    padScreen();
}

void displayRedrawMenu() {
    displayStopDataTimer();
    
    clearScreen();
    printHelp();
    
    Menu const* cp_menu = menuSystem.get_current_menu();
    
    Serial.print("-----+ ");
    Serial.print(cp_menu->get_name());
    Serial.println(" +-----");
    _lineCount++;
    
    MenuComponent const* cp_menu_sel = cp_menu->get_selected();
    for (int i = 0; i < cp_menu->get_num_menu_components(); ++i)
    {
        MenuComponent const* cp_m_comp = cp_menu->get_menu_component(i);
        
        if (cp_menu_sel == cp_m_comp) {
            Serial.print("* ");
        } else {
            Serial.print("  ");
        }
        
        Serial.println(cp_m_comp->get_name());
        _lineCount++;
    }
    
     padScreen();
}

void displayStartDataTimer() {
    _displayMode = DISPLAY_MODE_DATA;
    _timer = displayTimer.every(DISPLAY_UPDATE_FREQUENCY, displayRedrawData);
}

void displayStopDataTimer() {
    displayTimer.stop(_timer);
    _timer = -1;
    _displayMode = DISPLAY_MODE_MENU;
}

int displayMode() {
    return _displayMode;
}

void displayDelayDataTimer() {
    displayTimer.stop(_timer);
    _timer = displayTimer.after(DISPLAY_MODE_SWITCH_DELAY, displayStartDataTimer);
}
