/*
 * HandleCanData.c
 *
 * Created: 25.04.2017 16:05:27
 *  Author: fuelfighter2
 */ 
#include "UniversalModuleDrivers/can.h"
#include "car.h"

#define RPMTOMMPS 28.798

CanMessage_t rxFrame;

/*void handle_can(Car_t *c)
{
	if (can_read_message_if_new(&rxFrame))
	{
		switch (rxFrame.id)
		{
			case ENCODER_CAN_ID:
			c->m1->rpm = (rxFrame.data[0] << 8) + rxFrame.data[1];
			c->m2->rpm = (rxFrame.data[2] << 8) + rxFrame.data[3];
			c->wheel_rpm = (rxFrame.data[4] << 8) + rxFrame.data[5];
			uint16_t newVel = c->wheel_rpm * RPMTOMMPS;
			uint16_t oldVel = c->velocity;
			c->acceleration = (oldVelMPS - newVelMPS)*10;
			c->velocity = newVelMPS;
			break;
			
			case STEERING_WHEEL_CAN_ID:
			c->i->buttons = rxFrame.data[1];
			c->i->throttle_left = rxFrame.data[2];
			c->i->throttle_right = rxFrame.data[3];
			c->i->joy_x = rxFrame.data[4];
			c->i->joy_y = rxFrame.data[5];
			break;
			
			case MOTOR_1_STATUS_CAN_ID:
			c->m1->status = rxFrame.data[0];
			c->m1->current = (rxFrame.data[1] << 8) + rxFrame.data[2];
			c->m1->pwm = (rxFrame.data[3] << 8) + rxFrame.data[4];
			c->m1->throttle = rxFrame.data[5];
			break;
			
			case MOTOR_2_STATUS_CAN_ID:
			c->m2->status = rxFrame.data[0];
			c->m2->current = (rxFrame.data[1] << 8) + rxFrame.data[2];
			c->m2->pwm = (rxFrame.data[3] << 8) + rxFrame.data[4];
			c->m2->throttle = rxFrame.data[5];
			break;
			
			case BMS_CELL_V_1_4_CAN_ID:
			c->b->cell_volt[0] = (rxFrame.data[0] << 8) + rxFrame.data[1];
			c->b->cell_volt[1] = (rxFrame.data[2] << 8) + rxFrame.data[3];
			c->b->cell_volt[2] = (rxFrame.data[3] << 8) + rxFrame.data[5];
			c->b->cell_volt[3] = (rxFrame.data[4] << 8) + rxFrame.data[7];
			break;
			
			case BMS_CELL_V_5_8_CAN_ID:
			c->b->cell_volt[4] = (rxFrame.data[0] << 8) + rxFrame.data[1];
			c->b->cell_volt[5] = (rxFrame.data[2] << 8) + rxFrame.data[3];
			c->b->cell_volt[6] = (rxFrame.data[4] << 8) + rxFrame.data[5];
			c->b->cell_volt[7] = (rxFrame.data[6] << 8) + rxFrame.data[7];
			break;
			
			case BMS_CELL_V_9_12_CAN_ID:
			c->b->cell_volt[8] = (rxFrame.data[0] << 8) + rxFrame.data[1];
			c->b->cell_volt[9] = (rxFrame.data[2] << 8) + rxFrame.data[3];
			c->b->cell_volt[10] = (rxFrame.data[4] << 8) + rxFrame.data[5];
			c->b->cell_volt[11] = (rxFrame.data[6] << 8) + rxFrame.data[7];
			break;
			
			case BMS_CELL_TEMP_CAN_ID:
			c->b->cell_temp[0] = (rxFrame.data[0] << 8) + rxFrame.data[1];
			c->b->cell_temp[1] = (rxFrame.data[2] << 8) + rxFrame.data[3];
			c->b->cell_temp[2] = (rxFrame.data[3] << 8) + rxFrame.data[5];
			c->b->cell_temp[3] = (rxFrame.data[4] << 8) + rxFrame.data[7];
			break;
			
			case BMS_VOLT_CURRENT_CAN_ID:
			c->b->current = (rxFrame.data[0] << 8) + rxFrame.data[1];
			c->b->voltage = (rxFrame.data[2] << 8) + rxFrame.data[3];
			break;
			
			case BMS_STATUS_CAN_ID:
			c->b->status = rxFrame.data[0];
			break;
			
			case BMS_ERROR_CAN_ID:
			c->b->error = (rxFrame.data[0] << 8) + rxFrame.data[1];
			break;
			
			case FRONT_LIGHTS_CAN_ID:
			c->front->status = rxFrame.data[0];
			c->front->light_level[0] = rxFrame.data[1];
			c->front->light_level[1] = rxFrame.data[2];
			c->front->light_level[2] = rxFrame.data[3];
			c->front->light_level[3] = rxFrame.data[4];
			break;
			
			case BACK_LIGHTS_CAN_ID:
			c->back->status = rxFrame.data[0];
			c->back->light_level[0] = rxFrame.data[1];
			c->back->light_level[1] = rxFrame.data[2];
			c->back->light_level[2] = rxFrame.data[3];
			c->back->light_level[3] = rxFrame.data[4];
			break;
		}
	}
}*/