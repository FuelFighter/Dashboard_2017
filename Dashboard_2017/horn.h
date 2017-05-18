/*
 * horn.h
 *
 * Created: 13.05.2017 10:00:22
 *  Author: Ultrawack
 */ 


#ifndef HORN_H_
#define HORN_H_

typedef enum {
	HZ_3906 = 0,
	HZ_976,
	HZ_488,
	HZ_244,
	HZ_122,
	HZ_30
} hornTone_t;

typedef enum {
	OFF = 0,
	ON
} hornToggle_t;

void horn_init(hornTone_t tone);
void horn_set_tone(hornTone_t tone);
void horn_set(hornToggle_t state);

#endif /* HORN_H_ */