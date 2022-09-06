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

void initLed()
{
	//Enable GPIO Clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //Enable clock for GPIO Port A
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE); //Enable clock for GPIO Port B
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE); //Enable clock for GPIO Port C

	//GPIO PA9 (Blue)
    GPIO_InitTypeDef GPIO_InitStructA;
    GPIO_InitStructA.GPIO_Pin = GPIO_Pin_9; // bit to be set
    GPIO_InitStructA.GPIO_Mode = GPIO_Mode_OUT; // Input with pull-down resistor
    GPIO_InitStructA.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructA);

    //GPIO PB4(Red)
    GPIO_InitTypeDef GPIO_InitStructB;
    GPIO_InitStructB.GPIO_Pin = GPIO_Pin_4; // bit to be set
    GPIO_InitStructB.GPIO_Mode = GPIO_Mode_OUT; // Input with pull-down resistor
    GPIO_InitStructB.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructB);

    //GPIO PC7 (Green)
    GPIO_InitTypeDef GPIO_InitStructC;
    GPIO_InitStructC.GPIO_Pin = GPIO_Pin_7; // bit to be set
    GPIO_InitStructC.GPIO_Mode = GPIO_Mode_OUT; // Input with pull-down resistor
    GPIO_InitStructC.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructC);
}

void setLed(uint8_t red, uint8_t green, uint8_t blue)
{
	if(!red)
	{
		GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_SET); //Red
	}
	else
	{
		GPIO_WriteBit(GPIOB, GPIO_Pin_4, Bit_RESET);
	}
	if(!green)
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_SET); //Green
	}
	else
	{
		GPIO_WriteBit(GPIOC, GPIO_Pin_7, Bit_RESET); //Green
	}
	if(!blue)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_SET); //Blue
	}
	else
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_9, Bit_RESET); //Blue
	}
}

void initEXTINT()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource5); //Center
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource0); //Down
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4); //Up
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource0); //Right
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource1); //Left


	//define and set EXTI
	EXTI_InitTypeDef EXTI_InitStruct0;
	EXTI_InitStruct0.EXTI_Line = EXTI_Line0; // line 0 see [RM p. 215]
	EXTI_InitStruct0.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct0.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct0.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct0);

	EXTI_InitTypeDef EXTI_InitStruct1;
	EXTI_InitStruct1.EXTI_Line = EXTI_Line1; // line 1 see [RM p. 215]
	EXTI_InitStruct1.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct1.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct1.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct1);

	EXTI_InitTypeDef EXTI_InitStruct4;
	EXTI_InitStruct4.EXTI_Line = EXTI_Line4; // line 4 see [RM p. 215]
	EXTI_InitStruct4.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct4.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct4.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct4);

	EXTI_InitTypeDef EXTI_InitStruct9_5;
	EXTI_InitStruct9_5.EXTI_Line = EXTI_Line5; // line 5 see [RM p. 215]
	EXTI_InitStruct9_5.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct9_5.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct9_5.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct9_5);

	// setup NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitTypeDef NVIC0_InitStruct;
	NVIC0_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC0_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC0_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC0_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC0_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitTypeDef NVIC1_InitStruct;
	NVIC1_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC1_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC1_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC1_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC1_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitTypeDef NVIC4_InitStruct;
	NVIC4_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC4_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC4_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC4_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC4_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitTypeDef NVIC9_5_InitStruct;
	NVIC9_5_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC9_5_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC9_5_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC9_5_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC9_5_InitStruct);
}

void EXTI0_IRQHandler(void)
{
	printf("Right:%d |Up:%d | Center:%d | Left:%d | Down:%d \n",GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0),GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5),GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0));
	GPIO_WriteBit(GPIOC,GPIO_Pin_7,Bit_RESET);
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
	printf("Right:%d |Up:%d | Center:%d | Left:%d | Down:%d \n",GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0),GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5),GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0));
	GPIO_WriteBit(GPIOC,GPIO_Pin_7,Bit_SET);
	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI4_IRQHandler(void)
{
	printf("Right:%d |Up:%d | Center:%d | Left:%d | Down:%d \n",GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0),GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5),GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0));
	GPIO_WriteBit(GPIOC,GPIO_Pin_7,Bit_SET);
	EXTI_ClearITPendingBit(EXTI_Line4);
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		printf("Right:%d |Up:%d | Center:%d | Left:%d | Down:%d \n",GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0),GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5),GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1),GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0));
		GPIO_WriteBit(GPIOC,GPIO_Pin_7,Bit_SET);
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

int main(void)
{
	uart_init(9600);
	printf("Joystick position program!\n");
	initJoystick();
	initLed();
	initEXTINT();

	while(1)
	{
	}
}


