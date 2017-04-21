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

#define WW_PWM_TOP 5000
#define WW_TOP_ANGLE 2200
#define WW_BOTTOM_ANGLE 800


uint16_t ww_count = 0;
uint16_t ww_angle = WW_BOTTOM_ANGLE;
uint16_t ww_adc_val = 0;
uint8_t ww_dir = 0;
uint8_t ww_delay = 0;
uint8_t ww_speed = 0;

void window_wiper_init()
{
	//Windowwiper uses PE4
	//prescaler 8000000/8 = 1000000
	TCCR3B |= (1<<CS31);
	TCCR3B &= ~((1<<CS32)|(1<<CS30));
	
	//Top of PWM = WW_PWM_TOP;
	ICR3 = WW_PWM_TOP;
}

void window_wiper()
{
	ww_adc_val = adc_read(CH_ADC0);
	/*
	if (ww_count < ww_adc_val)
	{
		ww_count++;
		return;
	}
	*/
	
	if (ww_adc_val > 1000){
		ww_speed = 0;
	}else if(ww_adc_val > 700){
		ww_speed = 1;
	}else if(ww_adc_val > 300){
		ww_speed = 2;
	}else{
		ww_speed = 3;
	}
	
	if (ww_adc_val > 1000)
	{
		if (ww_angle > 800)
		{
			ww_angle = ww_angle - 10;
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
			ww_angle = ww_angle + ww_speed;
		}else if (ww_dir == 1)
		{
			ww_angle = ww_angle - ww_speed;
		}
		
		OCR3B = ww_angle;
	}
	//ww_count = 0;
}



