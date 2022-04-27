#include<avr/io.h>
#include<avr/interrupt.h>


int counter=0;


ISR(TIMER0_OVF_vect){
counter++;
if (counter==5){
TCNT0=55;

}



if (counter>=10){
counter=0;
PORTB=~PORTB;

}

}





int main(){
DDRB|=(1<<PB5);
TCCR0=(1<<CS00)|(1<<CS01)|(1<<CS02);
TIMSK=(1<<TOIE0);
sei();
for(;;){
;
}




}