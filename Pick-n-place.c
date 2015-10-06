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
		
}

ISR(TIMER0_COMPA_vect){
	//This service routine is run when Timer0 gets 40 ticks
	PORTC^=(1<<PORTC1);
	
}

