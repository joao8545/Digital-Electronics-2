#include <avr/io.h>
#include <util/delay.h>
//port initialization
void initPorts(){
DDRC  |= (1<<DDC0)|(1<<DDC1)|(1<<DDC2)|(1<<DDC3)|(1<<DDC4)|(1<<DDC5)|(1<<DDC6)|(1<<DDC7);
PORTC |= (1<<PC0) |(1<<PC1) |(1<<PC2) |(1<<PC3) |(1<<PC4) |(1<<PC5) |(1<<PC6) |(1<<PC7);

DDRD|=(1<<DDD2)|(1<<DDD3)|(1<<DDD4)|(1<<DDD5);
PORTD |= (1<<PD2) |(1<<PD3)|(1<<PD4)|(1<<PD5);

DDRE &= ~(1<<DDE4) & ~(1<<DDE5) & ~(1<<DDE6) &~(1<<DDE7);
PORTE |= (1<<PE4) |(1<<PE5) |(1<<PE6) |(1<<PE7);
}
//external interrupt initialization

void initEI(){
EIMSK |= (1<<INT5);
EICRB &= ~(1<< ISC50);
EICRB &= ~(1<< ISC51);

EIMSK |= (1<<INT4);
EICRB &= ~(1<< ISC50);
EICRB &= ~(1<< ISC51);

}

void checkHardware(){
//LED operation check
PORTD &= ~((1<<PD2)|(1<<PD3)|(1<<PD4)|(1<<PD5));

//7SEG operation check
PORTC &= ~((1<<PC0)|(1<<PC1)|(1<<PC2)|(1<<PC3)|(1<<PC4)|(1<<PC5)|(1<<PC6)|(1<<PC7));


//Button operation check
if((PINE &(1<<PINE4))==0){
PORTD |=_BV(PD2);
}
if((PINE &(1<<PINE5))==0){
PORTD |=_BV(PD3);
}
if((PINE &(1<<PINE6))==0){
PORTD |=_BV(PD4);
}
if((PINE &(1<<PINE7))==0){
PORTD |=_BV(PD5);
}
}

int main(void){
initPorts();
//initEI();

for(;;){
checkHardware();



}

return 0;
}