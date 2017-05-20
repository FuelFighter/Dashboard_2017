/*
 * horn.c
 *
 * Created: 13.05.2017 10:00:38
 *  Author: Ultrawack
 */ 

#include "UniversalModuleDrivers/pwm.h"
#include "horn.h"
#include <avr/io.h>

void horn_init(){
	//Uninitialize pwm init
	TCCR2A = 0;
	
	DDRB |= (1 << PB4);
	TCCR2A |= (1 << WGM21);
	TCCR2A |= (1 << CS22);
	OCR2A = 0x90;
	//PORTB &= ~(1 << PB4);
}

void horn_set(hornToggle_t state){
	if (state == ON){
		TIMSK2 |= (1 << OCIE2A);
	}else{
		TIMSK2 &= ~(1 << OCIE2A);
		PORTB &= ~(1 << PB4);
	}
}
