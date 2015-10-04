/*
 * main.c
 *
 *  Created on: 4 Oct 2015
 *      Author: Cobus
 */

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR ((F_CPU/16/BAUD)-1)
unsigned char analogString[10] = "Bye";


#include <avr/io.h>
#include <util/delay.h>

#include "UART.h"
#include "end_effector.h"

int main(void){
	//Initialize stuff here
	initUART(MYUBRR);
	printStr("Hello");
	initEF();		//Initialize the end effector
	startADC0();	//Start conversion


	while(1){
		//Main loop
		itoa(analogRead,analogString,10);
		printStr(analogString);
		startADC0();
		_delay_ms(1000);
	}
	return 0;

}

