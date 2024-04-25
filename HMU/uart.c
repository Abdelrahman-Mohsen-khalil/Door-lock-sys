 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Author: Abdelrahman mohsen
 *
 *******************************************************************************/
#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "common_macros.h" /* To use the macros like SET_BIT */

void UART_init(const UART_ConfigType *Config_Ptr) {
	uint16 ubrr_value = 0;
	ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);
	UCSRA =(1<<U2X);
	UCSRB=(1<<TXEN)|(1<<RXEN);
	UCSRC=(1<<URSEL)|((Config_Ptr->numdata)<<1)|((Config_Ptr->Stopbit)<<3)|((Config_Ptr->parity)<<4);
	UBRRH=(ubrr_value>>8);
	UBRRL=(ubrr_value);
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data) {
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	UDR=data;
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void) {
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str) {
	uint8 i = 0;

	/* Send the whole string */
	while (Str[i] != '\0') {
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	 while(*Str != '\0')
	 {
	 UART_sendByte(*Str);
	 Str++;
	 }
	 *******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str) {
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while (Str[i] != '#') {
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
