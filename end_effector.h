/*
 * end_effector.h
 *
 *  Created on: 4 Oct 2015
 *      Author: Cobus
 *
 *      The Endeffector file will need to have the following
 *      capabilities:
 *      	-Turn Electromagnet on and off
 *      	-Turn IR_Leds on and off
 *      	-Start ADC Conversions & handel interrupts
 *
 */



#ifndef END_EFFECTOR_H_
#define END_EFFECTOR_H_

#define EM PORTC1
#define IR PORTC2

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>


void initEF();
void turnOnEM();
void turnOffEM();
void turnOnIR();
void turnOffIR();
void initADC();
void startADC0();
int analogRead();
ISR(ADC_vect);

#endif /* END_EFFECTOR_H_ */
