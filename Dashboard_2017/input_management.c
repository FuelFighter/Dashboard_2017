/*
 * button_init.c
 *
 * Created: 04.04.2017 16:52:44
 *  Author: ola
 */ 

#include <avr/io.h>
#include "input_management.h"

void buttons_init() {
	
	PORTB |= (1<<PB1); //Initiate (input) PB1, lights
	DDRB &= ~(1<<PB1);
	
	PORTB |= (1<<PB2); //Initiate (input) PB2, hazard lights
	DDRB &= ~(1<<PB2);
	
	PORTB |= (1<<PB0); //Initiate (input) PB0, lap
	DDRB &= ~(1<<PB0);
}

bool button_is_pressed(button_t button) {
	return !((1<<(int)button)&PINB);
}