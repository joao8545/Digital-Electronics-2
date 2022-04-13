#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>




int main(void){
//int mask=0b00111100;
//DDRC  = 255;
DDRD |=0b00111100;

//PORTC  = 255;
PORTD |= 0b00100100;


for(;;){

PORTD &= ~(0b00100100);
PORTD |= (0b00011000);

_delay_ms(500);
PORTD |= (0b00100100);
PORTD &= ~(0b00011000);
_delay_ms(500);

}


return 0;

}