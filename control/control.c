/*
 *
 *
 *
 *
 *
 * Abdelrahman_mohsen
 *
 *
 *
 *
 * */
#include "Buzzer.h"
#include "DcMotor.h"
#include "std_types.h"
#include "timer1.h"
#include "uart.h"
#include "avr/io.h"
#include "external_eeprom.h"
#include "util/delay.h"
#include "pwm.h"
#include "twi.h"
#define failed 0
#define succeeded 1
#define wrong_pass 2
#define right_pass 3
#define Checkpass 4
#define save_newpass 5
#define open 6
#define buzzeron 7
#define buzzerOff 8
uint8 count =0;
uint8 pass[5], pass2[5],pass_memory[5];
uint8 i=0;
/*
 * if two pass are same it will save it*/
uint8 check_pass(uint8 pass[], uint8 pass2[]){
	for ( i=0; i<5; i++){
		if(pass[i]!=pass2[i])
			return failed;

	}
	return succeeded;


}
void write_memory(uint8 pass[]){

	for( i =0;i<5;i++){

		EEPROM_writeByte(0x0311+i, pass[i]);
		_delay_ms(10);
/* delay required to save in eeprom*/

}
}
/*used to check the pass eneter in open and chane func*/
uint8 verfiy_memory_pass(uint8 pass[]){

	for ( i = 0;i<5;i++){

		EEPROM_readByte(0x0311+i, pass_memory+i);
		_delay_ms(10);
	}
	for( i =0;i<5;i++){

		if(pass[i]!=pass_memory[i])
			return wrong_pass;

	}
	return right_pass;
}


void sec_3(){
	count++;
	if (count == 3){

		Timer1_deInit();
		DcMotor_Rotate(Anti_Clockwise, 100);

	}

}

void sec_15(){
	count++;
	if(count==15){

		Timer1_deInit();
		DcMotor_Rotate(Stop, 100);

	}
}
/*
 * set the call bace func of timer1
 * */
void timer1delay(uint8 sec){

	count =0;
	Timer1_ConfigType config_t1={0,31250,FCPU_256,CTC};
	Timer1_init(&config_t1);

	switch (sec){
	case 3 :

		Timer1_setCallBack(sec_3);
		break;
	case 15:

		Timer1_setCallBack(sec_15);
		break;
	}

}

int main(){

	TWI_ConfigType configt ={0b00000010,400000,1};
	TWI_init( & configt);/* to set configration of twi*/
	UART_ConfigType configx ={d_8bit,disable,one_bit,9600};/* to set configration of uart*/
	UART_init(& configx);
	DcMotor_Init();
	Buzzer_init();
	SREG|=1<<7;
	uint8 status=failed;
	uint8 state=failed;

	uint8 choose;

	while(status == failed){

		for ( i=0; i<5;i++)
			pass[i]=UART_recieveByte();

		for ( i=0; i<5;i++)
			pass2[i]=UART_recieveByte();

		status = check_pass(pass, pass2);
              if(status==succeeded){
            	  write_memory(pass);
		       UART_sendByte(succeeded);
              }
             else{
       		   UART_sendByte(failed);

              }

	}


	while(1){
		choose = UART_recieveByte();


		if(choose==Checkpass)
		{
			for( i=0;i<5;i++){
				pass[i]= UART_recieveByte();
			}
			status = verfiy_memory_pass(pass);
			UART_sendByte(status);
		}



		else if(choose==save_newpass)
		{
               if(state==failed){
				for ( i=0; i<5;i++){
					pass[i]=UART_recieveByte();
				}
				for ( i=0; i<5;i++){
					pass2[i]=UART_recieveByte();
				}
				state = check_pass(pass, pass2);
			      if(state==succeeded){

			            	  write_memory(pass);

				          UART_sendByte(succeeded);

			              }
			      else{
			    	  UART_sendByte(failed);
			      }
               }


		}


		else if(choose==open)
		{
			DcMotor_Rotate(Clockwise, 100);
			timer1delay(15);
			while(count!=15){}
			timer1delay(3);
			while(count!=3){}
			timer1delay(15);
			while(count!=15){}
	     }


		else if(choose==buzzeron)
		{
			Buzzer_on();
		}


		else if(choose== buzzerOff){

			Buzzer_off();

		}
	}



}
