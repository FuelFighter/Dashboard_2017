/*
 * Dashboard_2017.c
 *
 * Created: 18/03/17 15:14:29
 * Author : Sondre
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "UniversalModuleDrivers/adc.h"
#include "UniversalModuleDrivers/usbdb.h"
#include "UniversalModuleDrivers/can.h"
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
	//WindowWiper is Interrupt driven at 50Hz, and will be enabled when the value of ADC0 is less than 1000(0-1023). Will go from 3 seconds per sweep to 1 second per sweep.
	window_wiper_init();
	timer_init();
	sei();
	
	Car_t c;
	
	while(1) 
	{
		handle_can(&c);
	}
}



