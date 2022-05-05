/******************************************************************************/
/*                                   lcd_game.c                               */
/*      A Simple game developed for an AVR Microcontroller and a LCD          */
/*         using four buttons the player moves a man chasing a '*'            */
/*                     after 16 points the game ends                          */
/*                                                                            */
/*                Copyright (c) 2022 by Joao Anastacio Almeida                */
/*                                                                            */
/******************************************************************************/


#include <avr/io.h> 
#include <util/delay.h> 
#include <avr/sleep.h>
#include "lcd.h"

#define PLAYER 0x00//0x40
#define TARGET 0x2A

#define UP_BTN PE6
#define DOWN_BTN PE7
#define RIGHT_BTN PE5
#define LEFT_BTN PE4

#define DBOUNCETIME 25

int oldPos=128,newPos=128, targetPos,scoreCounter=1;
int numbers[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};
char endGame1[16]={'C','O','N','G','R','A','T','U','L','A','T','I','O','N','S','!'};
char endGame2[16]={' ',' ',' ',' ','Y','O','U',' ',' ','W','O','N',' ',' ',' ',' '};
int playerPattern[8]={0x0E,0x0E,0x04,0x0E,0x15,0x04,0x0A,0x11};

void lcd4_ram(unsigned char p);
void createTarget(){
	
	targetPos = rand() & 0xFF;
	
	if ((targetPos & 0xF0)>0x80)
		targetPos=(targetPos & 0x0F)+0xC0;
	else
		targetPos=(targetPos & 0x0F)+0x80;
		
	if ((targetPos & 0x0F)==(oldPos & 0x0F))
		targetPos=(targetPos & 0xF0)+(~(targetPos & 0x0F));
		
	lcd4_com(targetPos);
	lcd4_dat(TARGET);

}


void createPlayer(){
	for(int addr=0;addr<8;addr++){

	lcd4_com(0x40+addr);
	lcd4_ram(playerPattern[addr]);
	}
	_delay_ms(100);

}


void initMCU(){
	DDRC = 0xFF;
	DDRA = 0xFF;
	DDRE &= ~((1<<DDE4) | (1<<DDE5) | (1<<DDE6) | (1<<DDE7));

 
	PORTA = 0xC0; 
	PORTC = numbers[5];
	
	lcd4_init(); 
	PORTC = numbers[4];
	
	createPlayer();
	PORTC = numbers[3];
	
	lcd4_com(0x0C); 	// turn off cursosr
	PORTC = numbers[2];
	
	lcd4_com(0x80);
	lcd4_dat(PLAYER); 	// instantiate the player
	PORTC = numbers[1];
	
	srand(TCNT0);
	createTarget();
	PORTC = numbers[0];
	

}

void updateLCD(int _newPos){
	if(oldPos==_newPos)
		return;
	lcd4_com(oldPos);
	lcd4_dat(0x20);  //blank space
	lcd4_com(_newPos);
	lcd4_dat(PLAYER);
	oldPos=_newPos;
	
	if (oldPos==targetPos){
		PORTC = numbers[scoreCounter];
		createTarget();
		scoreCounter++;
		
	
	}

}


void endGame(){
	lcd4_com(0x01);
	lcd4_com(0x80);
	for(int i=0; i<16;i++){  
  lcd4_dat(endGame1[i]);
  }
	lcd4_com(0xC0);
	for(int i=0; i<16;i++){  
  lcd4_dat(endGame2[i]);
  }
	

}
int main(void){
	initMCU(); 

  for(;;){
		
		if((PINE&(1<<LEFT_BTN))==0){
			_delay_ms(DBOUNCETIME);
			if((oldPos & 0x0F)==0x00) //if pos is on first column
				newPos=(oldPos & 0xF0)+0x0F;
			else
				newPos=(oldPos & 0xFF)-0x01;
		
		}
		
		if((PINE&(1<<RIGHT_BTN))==0){
			_delay_ms(DBOUNCETIME);
			if((oldPos & 0x0F)==0x0F) //if pos is on last column
				newPos=(oldPos & 0xF0)+0x00;
			else
				newPos=(oldPos & 0xFF)+0x01;
		
		}
		
		if((PINE&(1<<UP_BTN))==0){
			_delay_ms(DBOUNCETIME);
			if((oldPos & 0xF0)<=0x80) //if pos is on first line
				newPos=(oldPos & 0x0F)+0xC0;
			else
				newPos=(oldPos & 0x0F)+0x80;
			
		}
		
		if((PINE&(1<<DOWN_BTN))==0){
			_delay_ms(DBOUNCETIME);
			if((oldPos & 0xF0)>0x80) //if pos is not on first line
				newPos=(oldPos & 0x0F)+0x80;
			else
				newPos=(oldPos & 0x0F)+0xC0;
		
		}
		
		updateLCD(newPos);
		if (scoreCounter>=16){
			endGame();
			return (0);
		}
	
  }
 
  return(0); 

}

void lcd4_ram(unsigned char p){

  PORTA |= _BV(RS); //RS = 1 jel 

	
  PORTA |= _BV(EN); //EN = 1 jel
  PORTA &= 0xC3;

//A 8 bites LCD kijelzo-utasitas felso nibble-jenek kiadasa a
//DB4-DB7 adatsinre
  PORTA |= ((p & 0xF0) >> 2);
  _delay_ms(TIME); //Az EN jel idotartartamanak megadasa

  PORTA &= ~_BV(EN); //EN = 0. Az LCD kijelzo-utasitas beirasanak frontja
  _delay_ms(5 * TIME); //A kijelzo-utasitas vegrehajtasi idonek megadasa
 
	
  PORTA |= _BV(EN); //EN = 1 jel
  PORTA &= 0xC3;

//A 8 bites LCD kijelzo-utasitas also nibble-jenek kiadasa a
//DB4-DB7 adatsinre
  PORTA |= ((p & 0x0F) << 2); 
  _delay_ms(TIME); //Az EN jel idotartartamanak megadasa
  
	
	
  PORTA &= ~_BV(EN); //EN = 0. Az LCD kijelzo-utasitas beirasanak frontja
  _delay_ms(5 * TIME); //A kijelzo-utasitas vegrehajtasi idonek megadasa
	PORTA &= ~_BV(RS); //RS = 0 jel

}