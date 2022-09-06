/*
 * A1_e0.2.c
 *
 *  Created on: 6. sep. 2022
 *      Author: lpjensen
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stm32f30x_gpio.h"

int main(void)
{
	uart_init(9600);
	printf("Hello World - again!\n");

	while(1){}
}


