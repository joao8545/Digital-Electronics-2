#include <avr/interrupt.h>
#include <avr/io.h>

volatile static long adcResult=1000;
volatile static int counter =0;

int numbers[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};
ISR(ADC_vect){


adcResult=(ADCH<<8)|ADCL;
PORTC = numbers[(int)(adcResult/100)];

}

ISR(TIMER0_OVF_vect){
counter++;
if (counter>(int)(adcResult/10)){
PORTB=~PORTB;
counter=0;
}

}

int main(void){
//init reguisters

DDRB|=(1<<PB5);
DDRD |=(1<<PD2);
DDRC |=255;


TCCR0|=(1<<CS00)|(1<<CS01)|(1<<CS02);
TIMSK|=(1<<TOIE0);

ADMUX|=(1<< REFS0) |(1<<MUX0) |(1<<MUX1);
ADCSRA|=(1<< ADEN) |(1<< ADSC)|(1<<ADFR)|(1<< ADIE);


sei();



for(;;){
//read adc

if(adcResult>800)
PORTD=255;
if(adcResult<500)
PORTD=0;
;
}
return 0;

}
