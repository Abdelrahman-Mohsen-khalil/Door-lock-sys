 /******************************************************************************
 *
 * Module: BUZZER
 * File Name: Buzzer.c
 *
 * Author: Abdelrahman mohsen
 *
 *******************************************************************************/
#include "Buzzer.h"
#include "gpio.h"

void Buzzer_init(){

	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);

}

void Buzzer_on(){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

void Buzzer_off(){
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
