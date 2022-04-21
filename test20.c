#include<avr/io.h>
#include<avr/interrupt.h>
//Joao Anastacio E87ROH


ISR(INT6_vect){
turn_on();

}


void turn_on(){
PORTC=~((1<<PC3)|(1<<PC6));
PORTB|=(1<<PB5);

}


void turn_off(){
PORTC=255;
PORTB&=~(1<<PB5);

}


int main(void){

EIMSK |= (1<<INT6);
DDRC|=255;
DDRB|=(1<<DDB5);
PORTC=255;
//DDRE|=~(1>>PE7);


sei();

for(;;){


if((PINE&(1<<PE7))==0){
turn_off();
}

}
return 0;

}