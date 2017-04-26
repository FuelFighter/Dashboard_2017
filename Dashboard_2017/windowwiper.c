/*
 * WindowWiper.c
 *
 * Created: 17.04.2017 20:24:22
 * Author : Ultrawack
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "UniversalModuleDrivers/adc.h"
#include "UniversalModuleDrivers/usbdb.h"

#define WW_PWM_TOP 20000 //50Hz
#define WW_TOP_ANGLE 2200
#define WW_BOTTOM_ANGLE 800


uint16_t ww_count = 0;
uint16_t ww_angle = WW_BOTTOM_ANGLE;
uint16_t ww_adc_val = 0;
uint8_t ww_dir = 0;
uint8_t ww_delay = 0;

void window_wiper_init()
{
	//Windowwiper uses PE4
	//prescaler 8000000/8 = 1000000
	TCCR3B |= (1<<CS31);
	TCCR3B &= ~((1<<CS32)|(1<<CS30));
	TIMSK3 |= (1<<TOIE3);
	//Top of PWM = WW_PWM_TOP;
	ICR3 = WW_PWM_TOP;
}

void window_wiper()
{
	ww_adc_val = adc_read(CH_ADC0);
	
	//Increase step from 9 - 28 (or about 3 seconds per sweep to 1 second per sweep at 50Hz)
	uint8_t step = 9 + ((1000 - ww_adc_val) * 19)/1000;
	
	if (ww_adc_val > 1000)
	{
		if (ww_angle > 800)
		{
			ww_angle = ww_angle - 70;
		} else {
			ww_angle = 800;
		}
		
		OCR3B = ww_angle;
		
	}
	else
	{
		if (ww_angle == WW_BOTTOM_ANGLE)
		{
			ww_dir = 0;
		}else if ( ww_angle == WW_TOP_ANGLE)
		{
			ww_dir = 1;
		}
		
		if (ww_dir == 0)
		{
			ww_angle = ww_angle + step;
		}else if (ww_dir == 1)
		{
			ww_angle = ww_angle - step;
		}
		
		OCR3B = ww_angle;
	}
	ww_count = 0;
}

ISR(TIMER3_OVF_vect)
{
	window_wiper();
}

