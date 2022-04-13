#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT5_vect){
turn_on();

}


ISR(INT4_vect){
turn_off();

}

int init_io(){
DDRD  |= (1<<PD2);
PORTD |= (1<<PD2);
return (0);
}

int button_init(){
EIMSK |= (1<<INT5);
EICRB |= (1<< ISC50);
EICRB |= (1<< ISC51);

EIMSK |= (1<<INT4);
EICRB |= (1<< ISC40);
EICRB |= (1<< ISC41);
}

void turn_on(){PORTD &= ~(1<<PD2);}
void turn_off(){PORTD |= (1<<PD2);}

int main(void){
sei();
button_init();
init_io();
for(;;){
}

return 0;

}