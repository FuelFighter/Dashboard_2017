/*
 * windowwiper.h
 *
 * Created: 20.04.2017 21:48:50
 *  Author: Ultrawack
 */ 


#ifndef WINDOWWIPER_H_
#define WINDOWWIPER_H_


void window_wiper_init();
void window_wiper();
void window_wiper_enable(bool var);
void window_wiper_stepsize(uint16_t adc_val);


#endif /* WINDOWWIPER_H_ */