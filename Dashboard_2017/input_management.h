/*
 * buttons_management.h
 *
 * Created: 04.04.2017 16:55:26
 *  Author: ola
 */ 


#ifndef BUTTONS_MANAGEMENT_H_
#define BUTTONS_MANAGEMENT_H_
#include <stdbool.h>
#include "UniversalModuleDrivers/adc.h"

typedef enum {
	lap = PINB0,
	brake = PIND0,
	lights = PINB1,
	hazard_lights = PINB2
} button_t;

typedef enum {
	wiper = CH_ADC0,
	light_lvl = CH_ADC1
} adc_t;

void buttons_init();
bool button_is_pressed(button_t button);
uint8_t buttons_are_pressed(); 

#endif /* BUTTONS_MANAGEMENT_H_ */