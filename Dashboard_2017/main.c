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
#include "horn.h"
#include "UniversalModuleDrivers/pwm.h"
#include "UniversalModuleDrivers/timer.h"

#define RX_BUFFER_SIZE 200
#define CAN_MESSAGE_ID_LENGTH 3
#define CAN_MESSAGE_LENGTH_LENGTH 1
#define HORN_BUTTON_BIT 1

CanMessage_t txFrame;
CanMessage_t rxFrame;
CanMessage_t tempFrame;

CanMessage_t buttonMsg;
CanMessage_t brakeMsg;

char uartTxBuffer[50];
char uartRxBuffer[RX_BUFFER_SIZE];
int rxIndex = 0;
int parseIndex = 0;
int newUartMessages = 0;
uint8_t error = 0;
uint8_t buttons = 0;

uint8_t ascii_to_dec(char c);
void handling_error();
void transmit_serial_to_can();
void transmit_can_to_serial(CanMessage_t *dataFrame);

int main(void)
{		
	usbdbg_init();
	adc_init();
	window_wiper_init();
	horn_init(HZ_976);
	buttons_init();
	timer_init();
	can_init(0,0);
	sei();
	
	timer_start(TIMER1);
	timer_start(TIMER2);	

	buttonMsg.id = DASHBOARD_CAN_ID;
	buttonMsg.length = 3;

	brakeMsg.id = BRAKE_CAN_ID;
	brakeMsg.length = 1;
	
	uint16_t window_wiper_adcVal = 0;
	uint16_t light_level_adcVal = 0;
	
	while(1)
	{
		if (timer_elapsed_ms(TIMER1) > 100)
		{
			brakeMsg.data[0] = (PIND & (1 << PD0)) ? 1 : 0;
			can_send_message(&brakeMsg);
			transmit_can_to_serial(&brakeMsg);				
			
			window_wiper_adcVal = adc_read(wiper);
			light_level_adcVal = adc_read(light_lvl);

			buttonMsg.data[0] = buttons_are_pressed();
			buttonMsg.data[1] = light_level_adcVal/4;
			buttonMsg.data[2] = window_wiper_adcVal/4;
			can_send_message(&buttonMsg);
			transmit_can_to_serial(&buttonMsg);
			window_wiper_set_adcVal(window_wiper_adcVal);
			timer_start(TIMER1);
		}
		
		if (timer_elapsed_ms(TIMER2) >= 32)
		{
			window_wiper();
			timer_start(TIMER2);
		}
		
		// Eat all the can data
		if (can_read_message_if_new(&rxFrame))
		{
			if (rxFrame.data[0] == STEERING_WHEEL_CAN_ID)
			{
				if (rxFrame.data[1] & (1 << HORN_BUTTON_BIT))
				{
					horn_set(ON);
				} else {
					horn_set(OFF);
				}
			}

			transmit_can_to_serial(&rxFrame);
		}
	}
}

void transmit_can_to_serial(CanMessage_t *dataFrame)
{
	printf("[%03X:%d:", dataFrame->id,dataFrame->length);
	
	for(int i = 0; i < dataFrame->length; i++)
	{
		printf("%02X", dataFrame->data[i]);
	}
	
	printf("]\n");
}


