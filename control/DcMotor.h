/*
 * DcMotor.h
 *
 *  Created on: Oct 8, 2023
 *      Author: abdo
 */

#ifndef GPIO_DCMOTOR_H_
#define GPIO_DCMOTOR_H_

#include"std_types.h"
#define DcMotor_IN1_PORT_ID		PORTB_ID
#define DcMotor_IN1_Pin_ID		PIN0_ID
#define DcMotor_IN2_PORT_ID		PORTB_ID
#define DcMotor_IN2_Pin_ID		PIN1_ID
#define DcMotor_EN1_PORT_ID		PORTB_ID
#define DcMotor_EN1_Pin_ID		PIN3_ID

typedef enum {
	Clockwise,Anti_Clockwise,Stop
}DcMotor_State;



void DcMotor_Init(void);


void DcMotor_Rotate(DcMotor_State state,uint8 speed);



#endif /* GPIO_DCMOTOR_H_ */
