 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Author: Abdelrahman mohsen
 *
 *******************************************************************************/
#ifndef UART_H_
#define UART_H_

#include "std_types.h"
typedef enum {
	d_5bit = 0, d_6bit = 1, d_7bit = 2, d_8bit = 3, d_9bit = 7
} UART_BitData;

typedef enum {
	disable = 0, even = 2, odd = 3

} UART_Parity;

typedef enum {
	one_bit,two_bit
}stop_bit;


typedef struct {
	UART_BitData numdata;
	UART_Parity parity;
	stop_bit Stopbit;
	uint32 baud_rate;
} UART_ConfigType;

void UART_init(const UART_ConfigType *Config_Ptr);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
