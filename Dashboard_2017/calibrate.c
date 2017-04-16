/*
 * Calibrate.c
 *
 * Created: 05.04.2017 15:55:14
 *  Author: olaliu
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "calibrate.h"
#include "UniversalModuleDrivers/usbdb.h"
#include "UniversalModuleDrivers/adc.h"
#include "UniversalModuleDrivers/timer.h"

Cvalues_struct calibrate (void) {
	Cvalues_struct cal_vals;
	cal_vals.minWP = adc_read(CH_ADC0);
	cal_vals.maxWP = adc_read(CH_ADC0);
	
	printf("calibrating for 5 seconds...\n");
	
	timer_start(TIMER0);
	while(timer_elapsed_ms(TIMER0) < 5000) {
		uint16_t tempWP = adc_read(CH_ADC0);
		
		if (tempWP < cal_vals.minWP) {
			cal_vals.minWP = tempWP;
		} 
		else if (tempWP > cal_vals.maxWP) {
			cal_vals.maxWP = tempWP;
		}
	}
	timer_stop(TIMER0);
	printf("calibration complete\n");
	return cal_vals;
}