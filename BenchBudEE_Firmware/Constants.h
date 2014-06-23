//
// File			Constants.h
// Header
//
// Details		<#details#>
//	
// Project		 BenchBudEE_MenuSystem
//
// Author		Phillip Hall
// 				Phillip Hall
//
// Date			20/06/2014 9:15 pm
//
// Copyright	© Phillip Hall, 2014
//

// Core library
#ifndef Constants_h
#define Constants_h

// Constants

// Ardunio Pins
#define RELAY_ENABLE    6

#define DAC_CS_N        7
#define DAC_SHDN_N      2

#define ADC_CS_N        8
#define ADC_RESET_N     5
#define ADC_DR_N        4

#define  ADC_BIT_16         0xFFFF
#define  ADC_NUM_CHAN       2
#define  ADC_WIDTH          2
#define  ADC_VREF           2.37F
#define  ADC_BITS           16
#define  ADC_GAIN           1
#define  ADC_SINC_ORDER     3
#define  ADC_UPDATE_FREQUENCY 100

#define FAN_MODE        3
#define FAN_PWM         10
#define FAN_SPEED_STEP  20

#define VADJ_MON        A0

#define LED_PWM         9
#define LED_BRIGHTNESS_STEP 10

// Display modes
#define DISPLAY_MODE_MENU 0
#define DISPLAY_MODE_DATA 1
#define DISPLAY_MODE_SWITCH_DELAY 1500
#define DISPLAY_UPDATE_FREQUENCY 1000


#endif
