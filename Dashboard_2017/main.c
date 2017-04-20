/*
 * Dashboard_2017.c
 *
 * Created: 18/03/17 15:14:29
 * Author : Sondre
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UniversalModuleDrivers/adc.h"
#include "UniversalModuleDrivers/usbdb.h"
#include "input_management.h"
#include "windowwiper.h"
#include "UniversalModuleDrivers/pwm.h"
#include "UniversalModuleDrivers/timer.h"

int main(void)
{
	cli();
    buttons_init(); //see input_management for details
	adc_init();		
	usbdbg_init();
	pwm_init();
	window_wiper_init();
	timer_init();
	sei();
	
	//timer_start(TIMER0);
	
	while(1) 
	{
		/*if (timer_elapsed_ms(TIMER0) > 2000)
		{
			printf("ADC: %u\n", adc_read(CH_ADC0));
			//printf("lights: %d\n h_lights: %d\n gen1: %d\n", button_is_pressed(lights), button_is_pressed(h_lights), button_is_pressed(gen1));
			//printf("wiper: %d\n", adc_read(wiper));
			timer_start(TIMER0);
		}*/
		//For at window wiper skal fungere kan ikke while ha noen delay. Bruk metoder for delay der vi ikke blir stuck i en loop et sted. bruker timer.h fra Universal modules. 
		window_wiper();
	}
}

