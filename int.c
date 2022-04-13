#include <avr/io.h>
#include<avr/interrupt.h>


ISR(INT6_vect){
PORTD |=(1<<PD5);

}
ISR(INT7_vect){
PORTD &= ~(1<<PD5);

}

int main(void){
DDRD|=(1<<DDD5);

EIMSK |= ((1<<INT6)|(1<<INT7));
EICRB &=~((1<<ISC71)|(1<<ISC70)|(1<<ISC61)|(1<<ISC60));
sei();
for(;;){

;

}



return 0;
}