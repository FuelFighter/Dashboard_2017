/*
 * horn.h
 *
 * Created: 13.05.2017 10:00:22
 *  Author: Ultrawack
 */ 


#ifndef HORN_H_
#define HORN_H_

typedef enum {
	OFF = 0,
	ON = 1
} hornToggle_t;

void horn_init();
void horn_set(hornToggle_t state);

#endif /* HORN_H_ */