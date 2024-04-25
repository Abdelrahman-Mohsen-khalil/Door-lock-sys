 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Author: Abdelrahman mohsen
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"
typedef enum {
	Normal, CTC = 4
} Timer1_Mode;

typedef enum {
	no_clk,
	FCPU_1,
	FCPU_8,
	FCPU_64,
	FCPU_256,
	FCPU_1024,
	ex_clk_falling_edge,
	ex_clk_rising_edge
} Timer1_Prescaler;

typedef struct {
	uint16 initial_value;
	uint16 compare_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType *Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void (*a_ptr)(void));

#endif /* TIMER1_H_ */
