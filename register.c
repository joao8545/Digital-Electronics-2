#include <avr/io.h>
#include <util/delay.h>
//delay_ms(200);

char MASK_1 = 4;

int main(void){
DDRC=255;
DDRD=DDRD | 0b00111100;
PORTD=255;
PORTD=PORTD & (~MASK_1);
PORTC=0;

return 0;
}