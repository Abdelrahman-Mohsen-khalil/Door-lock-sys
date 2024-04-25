/*
 * DcMotor.c
 *
 *  Created on: Oct 8, 2023
 *      Author: abdo
 */

#include"std_types.h"
#include "DcMotor.h"
#include "gpio.h"
#include "pwm.h"

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DcMotor_IN1_PORT_ID, DcMotor_IN1_Pin_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DcMotor_IN2_PORT_ID, DcMotor_IN2_Pin_ID, PIN_OUTPUT);
	GPIO_writePin(DcMotor_IN2_PORT_ID, DcMotor_IN2_Pin_ID, LOGIC_LOW);
	GPIO_writePin(DcMotor_IN1_PORT_ID, DcMotor_IN1_Pin_ID, LOGIC_LOW);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){

	switch(state)
	{
	case Clockwise:
		GPIO_writePin(DcMotor_IN2_PORT_ID, DcMotor_IN2_Pin_ID, LOGIC_LOW);
		GPIO_writePin(DcMotor_IN1_PORT_ID, DcMotor_IN1_Pin_ID, LOGIC_HIGH);
		break;
	case Anti_Clockwise:
		GPIO_writePin(DcMotor_IN1_PORT_ID, DcMotor_IN1_Pin_ID, LOGIC_LOW);
		GPIO_writePin(DcMotor_IN2_PORT_ID, DcMotor_IN2_Pin_ID, LOGIC_HIGH);
		break;
	case Stop:
		GPIO_writePin(DcMotor_IN2_PORT_ID, DcMotor_IN2_Pin_ID, LOGIC_LOW);
		GPIO_writePin(DcMotor_IN1_PORT_ID, DcMotor_IN1_Pin_ID, LOGIC_LOW);
		break;
	}

	PWM_Timer0_Start(speed);

}
