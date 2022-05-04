//LCD kijelzo mukodesenek ellenorzese

//PA0 - az LCD kijelzo RS (Reset / Torlo) laba (4 lab)
//Fold - R/~W (Read / ~Write) csak irni tudunk az LCD kijelzobe(5 lab)
//PA1 - E (Enable / Engedelyezo) lab (6 lab)

//PA2-PA5 - az LCD kijelzo DB4-DB7 adatbemenetei

/******************************************************/

#include <avr/io.h> //Az I/O konyvtar
#include <util/delay.h> //A kesleltetes-beallitas konyvtar
#include <avr/sleep.h>
#include "lcd.h"
int i;
int val[3];

//-----------A foprogram------------
int main(void) //A foprogram kezdete
{
  DDRA = 0xFF; //A PORT A kimenet
  PORTA = 0xC0; //A PORT A (PA0-PA5) kimeneteit 0-ra allitjuk, a (PA6-PA7) - 1-re
  
  lcd4_init(); //Az LCD kijelzo inicializalasa (4 bit, 2 sor)

  for(i=0; i<16;i++){  
  lcd4_dat(i);
  }
  lcd4_dat(0b11000100);
  for(;;){
  for(i=16; i<256;i++){  
  lcd4_com(128);
  lcd4_dat(i);
  lcd4_com(192);
  lcd4_dat('0');
  lcd4_dat('x');
  sprintf(val,"%x",i&0xf0);
  lcd4_dat(val[0]);
   sprintf(val,"%x",i&0x0f);
  lcd4_dat(val[0]);
  //lcd4_dat(i&0x0f);
  _delay_ms(4000);
  }
  
  }

  
  lcd4_com(207); 
  
  lcd4_dat(0x48);
  //lcd4_com(128);
  //lcd4_dat(0x48);
 

  sleep_cpu(); //A MPU "elaltatasa"
  return(0); //A "main" program sikeres befejezese 

}
