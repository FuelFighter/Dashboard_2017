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
	lights = PINB0,
	h_lights = PINB1,
	gen1 = PINB2,
	gen2 = PINB3,
} button_t;

typedef enum {
	wiper = CH_ADC0
} adc_t;

void buttons_init();
bool button_is_pressed(button_t button);

#endif /* BUTTONS_MANAGEMENT_H_ */