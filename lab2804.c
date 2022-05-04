#include <avr/interrupt.h>
#include <avr/io.h>

char isPressed;
int counter=0;
int numbers[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};

ISR(INT7_vect){
//off

PORTB &= ~(1<<PB5);
PORTC= numbers[0];




}

ISR(INT6_vect){
//on
EIMSK &= ~(1<<INT6);



PORTB |= (1<<PB5);
PORTC= numbers[counter];
counter++;

EIMSK |= (1<<INT6);

}

int main(void){

DDRB |= (1<<DDB5);
EIMSK |= (1<<INT7) | (1<<INT6);
//EICRB |=
DDRC |=255;


sei();

for(;;) {
;
}

}