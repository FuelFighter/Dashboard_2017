/*
 * WindowWiper.c
 *
 * Created: 17.04.2017 20:24:22
 * Author : Ultrawack
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "UniversalModuleDrivers/adc.h"
#include "UniversalModuleDrivers/usbdb.h"
#include "UniversalModuleDrivers/pwm.h"

#define WW_PWM_TOP 20000 //50Hz
#define WW_TOP_ANGLE 2200
#define WW_BOTTOM_ANGLE 800
#define WW_ADC_TOP_THRESHOLD 1000
#define WW_FREQ 30


uint16_t ww_count = 0;
uint16_t ww_angle = WW_BOTTOM_ANGLE;
uint16_t ww_adc_val = 0;
uint8_t ww_dir = 0;
uint8_t ww_delay = 0;

void window_wiper_init()
{
	pwm_init();
	//Windowwiper uses PE4 -Timer 3
	//prescaler 8 -> 1000000Mhz
	pwm_set_prescale(SCALE_8, PWM_T3);
	//Top of PWM = WW_PWM_TOP;
	pwm_set_top_t3(WW_PWM_TOP);
	TCCR3A |= (1 << COM3A1)|(1 << COM3A0);
}

void window_wiper_set_adcVal(uint16_t value)
{
	ww_adc_val = value;
}

void window_wiper()
{
	
	//Increase step from 9 - 28 (or about 3 seconds per sweep to 1 second per sweep at ~30Hz)
	uint8_t step = 45 + (ww_adc_val * 140)/WW_ADC_TOP_THRESHOLD;
	
	if (1023 - ww_adc_val > WW_ADC_TOP_THRESHOLD)
	{
		if (ww_angle > WW_BOTTOM_ANGLE)
		{
			ww_angle = ww_angle - 70;
		} else {
			ww_angle = WW_BOTTOM_ANGLE;
		}
		pwm_set_duty_cycle(PWM_PE4, ww_angle);
	}
	else
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
			ww_angle = ww_angle + step;
		}else if (ww_dir == 1)
		{
			ww_angle = ww_angle - step;
		}
		pwm_set_duty_cycle(PWM_PE4, ww_angle);
	}
}

