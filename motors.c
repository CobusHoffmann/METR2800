/*
 * motors.c
 *
 * Created: 6/10/2015 12:00:12 AM
 *  Author: Cobus Hoffmann
 */ 

#include "motors.h"
void initMotors(){
	/************************************************************************/
	/* Using 8 bit Timer to run the motors, chosen frequency of 400Hz (400pps),
	   this will be done with a CTC Timer setup on Timer/Counter0.
	   This function must be run after sei()
	                                                                     */
	/************************************************************************/
	
	//Set CTC mode
	TCCR0A = (1<<WGM01);
	
	//number of ticks for 400Hz frequency
	OCR0A = 20;
	
	//Set the interrupt
	TIMSK0 = (1<<OCIE0A);
	
	//Set pre-scaler 1024, starts the timer
	TCCR0B =(1<<CS02)|(1<<CS00);
	
}

void move_forward(){
	dir = FORWARD;
}

void move_backward(){
	dir = REVERSE;
}

void stop(){
	dir = STOP;
	
}


void move(uint8_t state_flag){
	switch(state_flag){
		case 1:
		PORTB = (1<<PORTB2)|(1<<PORTB4); //state_1
		
		break;
		
		case 2:
		PORTB = (1<<PORTB2)|(1<<PORTB3); //state_2
		break;
		
		case 3:
		PORTB = (1<<PORTB1)|(1<<PORTB3); //state_3
		break;
		
		case 4:
		PORTB = (1<<PORTB1)|(1<<PORTB4); //state_4
		break;
	}

}


ISR(TIMER0_COMPA_vect){
	
	{
	/************************************************************************/
	/* This ISR will increment decrement or keep the state variable constant,
	   this will alow the move() function to not skip any steps.                                                                      */
	/************************************************************************/
	
	cli(); //clear the interrupt flag to allow this code to execute without interruption.
	switch (dir){
		case FORWARD:
		//increment the state variable
		if (state<4)
		{
			state ++;
		}else{
			state = 1;
		}
			break;
		
		case REVERSE:
		//Decrement the state variable
		if (state>0)
		{
			state --;
			}else{
			state = 4;
		}
			break;
		
		case STOP:
		//Do nothing
			break;
		
	}
	
	move(state);
	sei();	//set the interupt flag again 
}
}

