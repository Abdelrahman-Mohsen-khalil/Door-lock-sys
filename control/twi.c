 /******************************************************************************
 *
 * Module: TWI
 *
 * File Name: twi.c
 *
 * Author: Abdelrahman mohsen
 *
 *******************************************************************************/
#include "twi.h"
#include "avr/io.h"
#include "common_macros.h"
void TWI_init(TWI_ConfigType * config){


	TWAR= config->address;
	TWBR = ((((F_CPU)/(config->bit_rate))-16)/(2*config->prescale));
//	TWSR = 0x00;
	TWCR =(1<<TWEN);
	switch(config->prescale){

	case 1:
		TWSR=0x00;
		break;

	case 4:
		TWSR=0x01;
		break;

	case 16:
		TWSR=0x02;
		break;

	case 64:
	 TWSR=0x03;
	   break;

	default:
		 TWSR=0x00;
	}

}

void TWI_start(void){

	TWCR =(1<<TWEN)|(1<<TWSTA)|(1<<TWINT);

	while(BIT_IS_CLEAR(TWCR,TWINT));

}


void TWI_stop(void){

	TWCR =(1<<TWEN)|(1<<TWSTO)|(1<<TWINT);


}

void TWI_writeByte(uint8 data){
	TWDR = data;
	TWCR =(1<<TWEN)|(1<<TWINT);
	while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void){

	TWCR =(1<<TWEN)|(1<<TWEA)|(1<<TWINT);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 TWI_readByteWithNACK(void){
	TWCR =(1<<TWEN)|(1<<TWINT);
	while(BIT_IS_CLEAR(TWCR,TWINT));
	return TWDR;
}

uint8 TWI_getStatus(void){

	return TWSR & 0XF8;
}
