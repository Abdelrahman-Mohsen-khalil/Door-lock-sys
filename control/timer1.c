 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Author: Abdelrahman mohsen
 *
 *******************************************************************************/
#include "timer1.h"
#include <avr/io.h>
#include "common_macros.h"
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;
ISR(TIMER1_OVF_vect) {
	if (g_callBackPtr != NULL_PTR) {

		(*g_callBackPtr)();
	}
}
ISR(TIMER1_COMPA_vect) {
	if (g_callBackPtr != NULL_PTR) {

		(*g_callBackPtr)();
	}
}

void Timer1_init(const Timer1_ConfigType *Config_Ptr) {
	TCNT1 = Config_Ptr->initial_value;
	OCR1A = Config_Ptr->compare_value;
	if (Config_Ptr->mode == Normal) {
		TIMSK = 1 << TOIE1;
	} else {
		TIMSK = 1 << OCIE1A;
		TCCR1A = (1 << FOC1A) | (1 << FOC1B)
				| ((TCCR1A & 0XFC) | (Config_Ptr->mode & 0x3));
		TCCR1B = ((TCCR1B & 0XE7) | ((Config_Ptr->mode & 0xC) << 1))
				| (Config_Ptr->prescaler);
	}
}
void Timer1_deInit(void) {
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	OCR1A = 0;
	TIMSK = 0;
}

void Timer1_setCallBack(void (*a_ptr)(void)) {
	g_callBackPtr = a_ptr;

}
