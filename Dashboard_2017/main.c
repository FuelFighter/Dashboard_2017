/*
 * Dashboard_2017.c
 *
 * Created: 18/03/17 15:14:29
 * Author : Sondre
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "UniversalModuleDrivers/adc.h"
#include "UniversalModuleDrivers/usbdb.h"
#include "input_management.h"

int main(void)
{
    buttons_init(); //see input_management for details
	adc_init();		
	usbdbg_init();
	while(true) {
		printf("lights: %d\nh_lights: %d\ngen1: %d\n", button_is_pressed(lights), button_is_pressed(h_lights), button_is_pressed(gen1));
		printf("wiper: %d\n", adc_read(wiper));
		_delay_ms(100);
	}
}

