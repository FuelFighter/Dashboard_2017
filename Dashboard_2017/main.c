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
	
	// Car_t c;
	timer_start(TIMER1); // start timer1
	CanMessage_t msg;
	
	while(1)
	{
		if (timer_elapsed_ms(TIMER1) >= 10) {
			msg.id = 1;
			msg.length = 3;
			msg.data[0] = button_is_pressed(lights);
			msg.data[1] = adc_read(CH_ADC1);
			msg.data[2] = button_is_pressed(h_lights);
			can_send_message(&msg);
			timer_start(TIMER1); // restart timer1
		}
		// handle_can(&c);
	}
}



