/*
 * Pick_n_place.c
 *
 * Created: 5/10/2015 11:22:21 AM
 *  Author: Cobus Hoffmann
 */ 

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR ((F_CPU/16/BAUD)-1)

unsigned char analogString[10] = "Bey";
char str[10];

double sine[] = {127,139.68,152.23,164.53,176.46,187.89,198.71,208.82,218.1,226.48,233.87,240.18,245.37,249.37,252.15,253.68,253.95,252.94,250.68,247.18,242.48,236.63,229.68,221.7,212.78,203.01,192.47,181.28,169.54,157.38,144.92,132.28,119.59,106.97,94.546,82.451,70.8,59.711,49.294,39.654,30.886,23.079,16.31,10.647,6.1465,2.8537,0.80124,0.0097463,0.48709,2.2285,5.2166,9.4215,14.801,21.302,28.859,37.396,46.829,57.063,67.996,79.518,91.514,103.87,116.45
};
volatile int place=0;


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "UART.h"
#include "end_effector.h"

int main(void){
	//Initialize stuff here
	initUART(MYUBRR);
	initEF();		//Initialize the end effector
	sei();
	initTimer0();
	
	printStr(analogString);
	startADC0();	//Start conversion


	while(1){
		//Main loop
		
		itoa(analogRead(),str,10);
		printStr(str);
		startADC0();
		_delay_ms(1000);
	}
	return 0;

}

void initTimer0(){
	//Timers 8bit timer/counter0 must be initiated after sei()
	
	//Set CTC mode
	TCCR0A = (1<<WGM01);
	
	//number of ticks for 400Hz frequency
	OCR0A = 20;
	
	//Set the interrupt
	TIMSK0 = (1<<OCIE0A);
	
	//Set pre-scaler 1024, starts the timer
	TCCR0B =(1<<CS02)|(1<<CS00);	
}

ISR(TIMER0_COMPA_vect){
	//This service routine is run when Timer0 gets 40 ticks
	PORTC^=(1<<PORTC1);
	
}

