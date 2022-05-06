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

#define PLAYER 0xFF
#define TARGET 0x2A

#define UP_BTN PE6
#define DOWN_BTN PE7
#define RIGHT_BTN PE5
#define LEFT_BTN PE4

#define DBOUNCETIME 25


//todo improve auto scrolling
//todo fix bug of biting the tail
//todo improve randomness
//todo improve end screen



int oldPos=128,newPos=128, targetPos,scoreCounter=1,rowIndex=0, snakeSize=1;
int numbers[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};
char endGame1[16]={'C','O','N','G','R','A','T','U','L','A','T','I','O','N','S','!'};
char endGame2[16]={' ',' ',' ',' ','Y','O','U',' ',' ','W','O','N',' ',' ',' ',' '};
char endGame3[16]={'H','I','G','H',' ','S','C','O','R','E',':',' ',' ',' ',' ',' '};
char endGame4[16]={'Y','O','U','R',' ','S','C','O','R','E',':',' ',' ',' ',' ',' '};
int playerPattern[8]={0x0E,0x0E,0x04,0x0E,0x15,0x04,0x0A,0x11};
int snake[16*4];
int headPos,tailPos;
int isEndGame=0,isTargetOK=1;
int val[5];

int rows[4]={0x80,0xC0,0x90,0xD0};

void lcd4_ram(unsigned char p);
unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
void createTarget(){
	
	while(1){
		isTargetOK=1;
		targetPos = rand() & 0xFF;
		if ((targetPos & 0xF0)<=0x80){
			targetPos=(targetPos & 0x0F)+0x80;
		}
		else if ((targetPos & 0xF0)<=0x90){
			targetPos=(targetPos & 0x0F)+0x90;
		}
		else if ((targetPos & 0xF0)<=0xC0){
			targetPos=(targetPos & 0x0F)+0xC0;
		}
		else {
			targetPos=(targetPos & 0x0F)+0xD0;
		}
		for(int i=0;i<snakeSize;i++){
			if(targetPos==snake[i]){
				isTargetOK=0;
			}
		}
		if(isTargetOK==1)
			break;
	}
	
	
	
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
	
	//createPlayer();
	snake[0]=oldPos;
	headPos=snake[0];
	tailPos=snake[snakeSize-1];
	
	PORTC = numbers[3];
	
	lcd4_com(0x0C); 	// turn off cursosr
	PORTC = numbers[2];
	
	lcd4_com(0x80);
	lcd4_dat(PLAYER); 	// instantiate the player
	PORTC = numbers[1];
	
	srand(EEARL);
	createTarget();
	PORTC = numbers[0];
	

}

void updateLCD(int _newPos){
	if (_newPos==snake[0])
		return;
	
	if (snakeSize>1){
		if (_newPos==snake[1])
			return;
	}
	for(int k=snakeSize;k>0;k--){
		if(snake[k]==_newPos){
			isEndGame=1;
			return;
		}
	}
	
	
	lcd4_com(oldPos);
	lcd4_dat(0x20);  //blank space
	lcd4_com(_newPos);
	lcd4_dat(PLAYER);
	for(int k=snakeSize;k>1;k--){
		snake[k-1]=snake[k-2];
	}
	snake[0]=_newPos;
	
	
	
	if (_newPos==targetPos){
		PORTC = numbers[scoreCounter];
		
		scoreCounter++;
		if (scoreCounter>=16){
			isEndGame=1;
		}
		
		snakeSize++;
		snake[snakeSize-1]=oldPos;
		lcd4_com(oldPos);
		lcd4_dat(PLAYER);
		createTarget();
		
		
	
	}
	oldPos=snake[snakeSize-1];
	//oldPos=_newPos;

}


void endGame(){
	int highScore;
	highScore=EEPROM_read(0x00);
	if (highScore==0xFF)
		highScore=0;
	if(scoreCounter-1>highScore){
		EEPROM_write(0x00,((scoreCounter-1) &0xFF));
	}
	lcd4_com(0x01);
	lcd4_com(0x80);
	for(int i=0; i<16;i++){  
  lcd4_dat(endGame1[i]);
  }
	lcd4_com(0xC0);
	for(int i=0; i<16;i++){  
  lcd4_dat(endGame2[i]);
  }
	lcd4_com(0x90);
	for(int i=0; i<11;i++){  
  lcd4_dat(endGame3[i]);
  }
	lcd4_com(0x9E);
	sprintf(val,"%d",highScore);
	lcd4_dat(val[0]);
	lcd4_dat(val[1]);
	lcd4_dat(val[3]);
	
	lcd4_com(0xD0);
	for(int i=0; i<11;i++){  
  lcd4_dat(endGame4[i]);
  }
	lcd4_com(0xDE);
	sprintf(val,"%d",scoreCounter-1);
	lcd4_dat(val[0]);
	lcd4_dat(val[1]);
	lcd4_dat(val[3]);
	
	

}
int main(void){
	initMCU(); 
	char dir='r';

  for(;;){
		
		if(((PINE&(1<<LEFT_BTN))==0)|| dir=='l'){
			_delay_ms(DBOUNCETIME);
			if((snake[0] & 0x0F)==0x00) //if pos is on first column
				newPos=(snake[0] & 0xF0)+0x0F;
			else
				newPos=(snake[0] & 0xFF)-0x01;
			dir='l';
		
		}
		
		if(((PINE&(1<<RIGHT_BTN))==0)|| dir=='r'){
			_delay_ms(DBOUNCETIME);
			if((snake[0] & 0x0F)==0x0F) //if pos is on last column
				newPos=(snake[0] & 0xF0)+0x00;
			else
				newPos=(snake[0] & 0xFF)+0x01;
			dir='r';
		}
		
		if(((PINE&(1<<DOWN_BTN))==0)|| dir=='d'){
			_delay_ms(DBOUNCETIME);
			rowIndex++;
			if (rowIndex>=4)
				rowIndex=0;
			newPos=(snake[0] & 0x0F)+rows[rowIndex];
			dir='d';
		}
		
		if(((PINE&(1<<UP_BTN))==0)|| dir=='u'){
			_delay_ms(DBOUNCETIME);
			rowIndex--;
			if (rowIndex<0)
				rowIndex=3;
			newPos=(snake[0] & 0x0F)+rows[rowIndex];
			dir='u';
		
		}
		
		updateLCD(newPos);
		
		if (isEndGame==1){
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

void EEPROM_write(unsigned int uiAddress, unsigned char ucData){
/* Wait for completion of previous write */
while(EECR & (1<<EEWE))
;
/* Set up address and data registers */
EEAR = uiAddress;
EEDR = ucData;
/* Write logical one to EEMWE */
EECR |= (1<<EEMWE);
/* Start eeprom write by setting EEWE */
EECR |= (1<<EEWE);
}
unsigned char EEPROM_read(unsigned int uiAddress){
/* Wait for completion of previous write */
while(EECR & (1<<EEWE))
;
/* Set up address register */
EEAR = uiAddress;
/* Start eeprom read by writing EERE */
EECR |= (1<<EERE);
/* Return data from data register */
return EEDR;
}
