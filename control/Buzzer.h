 /******************************************************************************
 *
 * Module: BUZZER
 * File Name: Buzzer.h
 *
 * Author: Abdelrahman mohsen
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"

#define BUZZER_PORT_ID	PORTB_ID
#define BUZZER_PIN_ID	PIN2_ID


void Buzzer_init();
void Buzzer_on();
void Buzzer_off();

#endif /* BUZZER_H_ */
