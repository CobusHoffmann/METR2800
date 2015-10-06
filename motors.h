/*
 * motors.h
 *
 * Created: 5/10/2015 11:58:44 PM
 *  Author: Cobus Hoffmann
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_

#include <avr/interrupt.h>

volatile uint8_t state =1;

#define FORWARD 1
#define REVERSE 2
#define STOP 0

volatile uint8_t dir=STOP;  //0 for stop, 1for forward, 2 for reverse
volatile uint32_t steps;

void initMotors();
void move_forward();
void move_backward();
void stop();
void move(uint8_t state_flag);


ISR(TIMER0_COMPA_vect);

#endif /* MOTORS_H_ */