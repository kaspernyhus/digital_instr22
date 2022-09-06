/*
 * A1_e1.1.c
 *
 *  Created on: 6. sep. 2022
 *      Author: lpjensen
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "stm32f30x_gpio.h"

void initJoystick()
{
	//Enable GPIO Clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //Enable clock for GPIO Port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE); //Enable clock for GPIO Port B
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE); //Enable clock for GPIO Port C

	//GPIO PA4 (Up)
    GPIO_InitTypeDef GPIO_InitStructA;
    GPIO_InitStructA.GPIO_Pin = GPIO_Pin_4; // bit to be set
    GPIO_InitStructA.GPIO_Mode = GPIO_Mode_IN; // Input with pull-down resistor
    GPIO_InitStructA.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructA);

    //GPIO PB0(Down) and PB5 (Center)
    GPIO_InitTypeDef GPIO_InitStructB;
    GPIO_InitStructB.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_5; // bit to be set
    GPIO_InitStructB.GPIO_Mode = GPIO_Mode_IN; // Input with pull-down resistor
    GPIO_InitStructB.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructB);

    //GPIO PC0 (Right) and PC1 (Left)
    GPIO_InitTypeDef GPIO_InitStructC;
    GPIO_InitStructC.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // bit to be set
    GPIO_InitStructC.GPIO_Mode = GPIO_Mode_IN; // Input with pull-down resistor
    GPIO_InitStructC.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructC);

}

uint8_t readJoystick()
{
	uint8_t joystickPos = 0x00;

	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)) //Center
	{
		joystickPos = 0x10;
		//printf("Center\n");
	}
	else if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)) //Up
	{
		joystickPos = 0x01;
	}
	else if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)) //Down
	{
		joystickPos = 0x02;
		//printf("Down\n");
	}
	else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)) //Left
	{
		joystickPos = 0x04;
		//printf("Left\n");
	}
	else if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0)) //Right
	{
		joystickPos = 0x08;
		//printf("Right\n");
	}
	else
	{
		joystickPos = 0x00;
	}

	return(joystickPos);
}

int main(void)
{
	uart_init(9600);
	printf("Joystick position program!\n");
	initJoystick();

	uint8_t oldJoyPos = 0x01;
	uint8_t joyPos = 0x00;

	while(1)
	{

		joyPos = readJoystick();

		if(joyPos != oldJoyPos)
		{
			printf("Joystick Position: ");
			if (joyPos == 0x00 || joyPos == 0x10) //Center
			{
				printf("Center");
			}
			else if (joyPos == 1) //Up
			{
				printf("Up");
			}
			else if (joyPos == 2) //Down
			{
				printf("Down");
			}
			else if (joyPos == 4) //Left
			{
				printf("Left");
			}
			else if (joyPos == 8) //Right
			{
				printf("Right");
			}

			if (joyPos == 16)
			{
				printf(" - Button pressed!\n");
			}
			else
			{
				printf("\n");
			}
		}
		oldJoyPos = joyPos;
	}
}

