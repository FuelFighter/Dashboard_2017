/*
 * horn.c
 *
 * Created: 13.05.2017 10:00:38
 *  Author: Ultrawack
 */ 

#include "UniversalModuleDrivers/pwm.h"
#include "horn.h"
#include <avr/io.h>

void horn_init(hornTone_t tone)
{
	TCCR2A &= ~((1<<WGM21)|(1<<WGM20));
	TCCR2A |= (1<<WGM20);
	TCCR2A &= ~((1<<COM2A1)|(1<<COM2A0));
	TCCR2A |= (1<<COM2A1)|(1<<COM2A0);
	
	horn_set(OFF);
	horn_set_tone(tone);
}

void horn_set_tone(hornTone_t tone)
{
	switch(tone)
	{
		case HZ_30:
		pwm_set_prescale(SCALE_1024, PWM_T2);
		break;
		
		case HZ_122:
		pwm_set_prescale(SCALE_256, PWM_T2);
		break;
		
		case HZ_244:
		pwm_set_prescale(SCALE_128_T2_ONLY, PWM_T2);
		break;
		
		case HZ_488:
		pwm_set_prescale(SCALE_64, PWM_T2);
		break;
		
		case HZ_976:
		pwm_set_prescale(SCALE_32_T2_ONLY, PWM_T2);
		break;
		
		case HZ_3906:
		pwm_set_prescale(SCALE_8, PWM_T2);
		break;
	}
	
}

void horn_set(hornToggle_t state)
{
	if (state == ON)
	{
		pwm_set_duty_cycle(PWM_PB4,0x80);
	} else if (state == OFF)
	{
		pwm_set_duty_cycle(PWM_PB4,0x00);	
	}
}
