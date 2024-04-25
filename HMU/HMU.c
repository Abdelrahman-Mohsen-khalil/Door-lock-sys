/*
 *
 *
 *
 * Abdelrahman_mohsen
 *
 *
 *
 */
#include"keypad.h"
#include "LCD.h"
#include "std_types.h"
#include "Timer1.h"
#include "uart.h"
#include "util/delay.h"
#include "avr/io.h"
#define failed 0
#define succeeded 1
#define wrong_pass 2
#define right_pass 3
#define Checkpass 4
#define save_newpass 5
#define open 6
#define buzzeron 7
#define buzzeroff 8

uint8 pass[5], pass2[5],count=0;
uint8 temp;
//uint8 i=0;
/* funcion that create a password
 *  and repeated password and
 *  save it in 2 arrs[]*/
void Create_password(uint8 pass[], uint8 pass2[]){

	LCD_clearScreen();
	_delay_ms(200);
	LCD_displayString("Plz enter Pass: ");
	LCD_moveCursor(1,0);

//	 temp=KEYPAD_getPressedKey();
	for(uint8 i=0;i<5;)
	{
		temp=KEYPAD_getPressedKey();
		if( (temp>= 0 && temp<= 9) )
		{

				pass[i]=temp;
//				LCD_intgerToString(pass[i]);
				LCD_displayCharacter('*');
				i++;

			_delay_ms(500);
		}
	}while(KEYPAD_getPressedKey()!='=');
//	c=0;

	LCD_clearScreen();
	_delay_ms(200);
	LCD_displayString("Plz re-enter the ");
	LCD_moveCursor(1, 0);
	LCD_displayString("same pass:");


//	temp=KEYPAD_getPressedKey();
	for(uint8 i=0;i<5;)
	{
		temp=KEYPAD_getPressedKey();
		if( (temp>= 0 && temp<= 9) )
		{

				pass2[i]=temp;
//				LCD_intgerToString(pass2[i]);
				LCD_displayCharacter('*');

				i++;

			_delay_ms(500);
		}
	}while(KEYPAD_getPressedKey()!='=');
//	c=0;

	LCD_clearScreen();
}

/* send to arrays to mcu controller
 by using uart to check two pass are same to
 save it in rom if they are same */
void send_password(uint8 pass[], uint8 pass2[]){
	uint8 i =0;
	uint8 status;
	for( i =0;i<5;i++){
		UART_sendByte(pass[i]);
	}
	for( i =0;i<5;i++){
		UART_sendByte(pass2[i]);
	}





}
/*
 *func to check the pass that enterd == eeprom
 * */
void check_password(uint8 pass[]){
	uint8 i =0;
	UART_sendByte(Checkpass);
	for( i =0;i<5;i++){

		UART_sendByte(pass[i]);
	}

}


void sec_18(){
	count++;
	if(count==18){
		Timer1_deInit();

		LCD_clearScreen();

		LCD_displayString("Door is locking");
	}
}

void sec_15(){
	count++;
	if(count==15){
		Timer1_deInit();

		LCD_clearScreen();
	}
}

/*
 * for buzzer
 * */
void sec_60(){
	count++;
	if(count==60){
		Timer1_deInit();

		LCD_clearScreen();

		UART_sendByte(buzzeroff);

	}
}

/*
 * set the call bace func of timer1
 * */
void timer1delay(uint8 sec){

	count =0;
	Timer1_ConfigType config_t1={0,31250,FCPU_256,CTC}; //this config count one second
	Timer1_init(&config_t1);

	switch (sec){
	case 15:
		Timer1_setCallBack(sec_15);
		break;
	case 18:
		Timer1_setCallBack(sec_18);
		break;
	case 60:
		Timer1_setCallBack(sec_60);
		break;

	}

}

int main(){

	SREG|=(1<<7);

	LCD_init();

	UART_ConfigType config={d_8bit,disable,one_bit,9600};

	UART_init(&config);

	uint8 status=failed;
		uint8 choose;
		uint8 f=0;
		uint8 state;
		uint8 i=0;
		 uint8 statx ;
		 uint8 staty=failed;

/*
 * to create pass*/
	while(status== failed){

		Create_password(pass, pass2);

		send_password(pass, pass2);
		status=UART_recieveByte();


		if (status == failed){

			LCD_displayString("unMatched");


			_delay_ms(1500);

			LCD_clearScreen();

		}

	}


	while(1){
		LCD_clearScreen();
		LCD_displayString("+ : Open Door");
		LCD_displayStringRowColumn(1, 0, "- : Change Pass");
		choose = KEYPAD_getPressedKey();

		if(choose=='+'){

			f=0;
			while(f<3){

				LCD_clearScreen();
				_delay_ms(200);
				LCD_displayString("plz enter Pass: ");
				LCD_moveCursor(1, 0);
		//		 temp=KEYPAD_getPressedKey();

					for( i=0;i<5;)
					{
						temp=KEYPAD_getPressedKey();
						if( (temp>= 0 && temp<= 9) )
						{

								pass[i]=temp;
//								LCD_intgerToString(pass[i]);
								LCD_displayCharacter('*');

								i++;

							_delay_ms(500);
						}
					}while(KEYPAD_getPressedKey()!='=');
		//		c=0;
		        /* status bit to same the the pass condition if right pass or wrong */
					check_password(pass);
					state = UART_recieveByte();

				if (state == right_pass )
				{

					LCD_clearScreen();
					LCD_displayStringRowColumn(0, 5, "Door is");
					LCD_displayStringRowColumn(1, 4, "unlocking");

					UART_sendByte(open);
					/*send by uart to rotate the motor */
					timer1delay(18);
					/*waiting until count reach to 18*/
					while(count!=18){}
					timer1delay(15);
					/*waiting until count reach to 15*/

					while(count!=15){}
					break;
				}
				else
				{
					f++; // increment it tell reaching 3
				}
			}
			if(f==3){
                 f=0;
				LCD_clearScreen();
				LCD_displayString("ERROR");
				UART_sendByte(buzzeron);
				timer1delay(60);
				while(count!=60){}
			}
		}

		else if(choose=='-'){
			f=0;
		// temp=KEYPAD_getPressedKey();

			while(f<3){

				LCD_clearScreen();
				_delay_ms(200);
				LCD_displayString("plz enter Pass: ");
				LCD_moveCursor(1, 0);

				for( i=0;i<5;)
				{
					temp=KEYPAD_getPressedKey();
					if( (temp>= 0 && temp<= 9) )
					{

							pass[i]=temp;
//							LCD_intgerToString(pass[i]);
							LCD_displayCharacter('*');

							i++;

						_delay_ms(500);
					}
				}while(KEYPAD_getPressedKey()!='=');
		//		c=0;


				check_password(pass);
				statx = UART_recieveByte();
				if (statx == right_pass )

				{
//					staty=failed;

					while(staty== failed){
						LCD_clearScreen();

						_delay_ms(200);

						Create_password(pass, pass2);

						UART_sendByte(save_newpass);
						 send_password(pass, pass2);
						 staty=UART_recieveByte();
						if (staty == failed){

							LCD_displayString("unMatched");

							_delay_ms(1000);

							LCD_clearScreen();

						}
					}
					staty=failed;
					break;
				}
				else
				{
					f++;
				}
			}
			if(f==3){
				f=0;
				LCD_clearScreen();

				LCD_displayString("ERROR");

				UART_sendByte(buzzeron);

				timer1delay(60);

				while(count!=60){}

			}

		}
	}


}


