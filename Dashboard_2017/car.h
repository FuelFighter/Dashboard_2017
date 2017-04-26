/*
 * car.h
 *
 * Created: 25.04.2017 15:42:24
 *  Author: fuelfighter2
 */ 

#include <stdbool.h>
#include <stdint.h>

#ifndef CAR_H_
#define CAR_H_

typedef struct
{
	uint8_t status;
	uint16_t rpm;
	uint16_t current;
	uint16_t pwm;
	uint16_t throttle;
} Motor_t;

typedef struct
{
	uint8_t status;
	uint16_t error;
	uint16_t current;
	uint16_t voltage;
	uint16_t cell_volt [12];
	uint16_t cell_temp [4];
} Battery_t;

typedef struct  
{
	uint8_t buttons;
	uint8_t switches;
	uint8_t throttle_left;
	uint8_t throttle_right;
	uint8_t joy_x;
	uint8_t joy_y;	
}Interface;

typedef struct  
{
	uint8_t status;
	uint16_t light_level [4];
} Light_t;

typedef struct
{
	uint16_t velocity; // in mm/s for higher accuracy, max velocity of 36km/h gives 10000 mm/s
	int16_t acceleration; //in mm/s^2 for higher accuracy
	uint16_t wheel_rpm;
	bool deadmanswitch;
	bool brake;
	Interface i;
	Motor_t m1;
	Motor_t m2;
	Battery_t b;
	Light_t front;
	Light_t back;
} Car_t;

#endif /* CAR_H_ */