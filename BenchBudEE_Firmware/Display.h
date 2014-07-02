//
// File			Display.h
// Header
//
// Details		<#details#>
//	
// Project		 BenchBudEE_MenuSystem
//
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			20/06/2014 12:53 pm
// Version		<#version#>
// 
// Copyright	© Phillip Hall, 2014


// Core library
#include "Arduino.h"
#include "Constants.h"

#ifndef Display_h
#define Display_h

#define DISPLAY_MODE_MENU 0
#define DISPLAY_MODE_DATA 1

#define TERM_NUM_LINES 23

int displayMode();

void displayStartDataTimer();
void displayStopDataTimer();
void displayDelayDataTimer();

void displayRedrawData();
void displayRedrawMenu();

#endif
