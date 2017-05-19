/*
 * WindowWiper.c
 *
 * Created: 17.04.2017 20:24:22
 * Author : Ultrawack
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include "UniversalModuleDrivers/adc.h"
#include "UniversalModuleDrivers/usbdb.h"
#include "UniversalModuleDrivers/pwm.h"

// Window Wiper values
#define WW_PWM_TOP 20000 //50Hz
#define WW_TOP_ANGLE 1834
#define WW_BOTTOM_ANGLE 1166

uint16_t ww_angle = WW_BOTTOM_ANGLE;
uint16_t window_wiper_adcVal = 0;
uint8_t ww_dir = 0;
uint8_t ww_step = 0;
uint8_t ww_off = 1;

void window_wiper_enable(bool var)
{
	if (var)
	{
		ww_off = 0;
	} else if (!var){
		ww_off = 1;
	}
}

void window_wiper_stepsize(uint16_t adc_val)
{
	float scaled_adc = adc_val/38;
	ww_step = (int)(6 + scaled_adc);
}

void window_wiper_init()
{
	pwm_set_prescale(SCALE_8,PWM_T3);
	//Set the frequency to 50Hz
	pwm_set_top_t3(WW_PWM_TOP);
	//Idle position
	pwm_set_duty_cycle(PWM_PE4,WW_BOTTOM_ANGLE);
	//Set High on Compare Match
	TCCR3A |= (1<<COM3B1)|(1<<COM3B0);
}

void window_wiper()
{
	if (ww_off)
	{
		if (ww_angle > WW_BOTTOM_ANGLE)
		{
			ww_angle = ww_angle - 16;
			} else {
			ww_angle = WW_BOTTOM_ANGLE;
		}
		pwm_set_duty_cycle(PWM_PE4, ww_angle);
	}
	else if (!ww_off)
	{
		if (ww_angle <= WW_BOTTOM_ANGLE)
		{
			ww_dir = 0;
		}else if ( ww_angle >= WW_TOP_ANGLE)
		{
			ww_dir = 1;
		}
		
		if (ww_dir == 0)
		{
			ww_angle = ww_angle + ww_step;
		}else if (ww_dir == 1)
		{
			ww_angle = ww_angle - ww_step;
		}
		pwm_set_duty_cycle(PWM_PE4, ww_angle);
	}
}

