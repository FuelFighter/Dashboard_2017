/*
 * calibrate.h
 *
 * Created: 05.04.2017 15:55:34
 *  Author: olaliu
 */ 


#ifndef CALIBRATE_H_
#define CALIBRATE_H_

typedef struct {
	uint16_t minWP;
	uint16_t maxWP;
} Cvalues_struct ;

Cvalues_struct calibrate(void);

#endif /* CALIBRATE_H_ */