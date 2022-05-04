#include <avr/io.h> //Az I/O konyvtar
#include <util/delay.h> //A kesleltetes-beallitas konyvtar
#include <avr/sleep.h>
#include "lcd.h"



int main(void) //A foprogram kezdete
{
  DDRA = 0xFF; //A PORT A kimenet
  PORTA = 0xC0; //A PORT A (PA0-PA5) kimeneteit 0-ra allitjuk, a (PA6-PA7) - 1-re
  
  lcd4_init();
  
  
  }