#include <avr/io.h>
#include <util/delay.h>
//port initialization
void initPorts(){
DDRD|=(1<<DDD2)|(1<<DDD5);
PORTD |= (1<<PD2) |(1<<PD5);

DDRE &= ~(1<<DDE4) & ~(1<<DDE5);
PORTE |= (1<<PE4) |(1<<PE5);
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
PORTD &= ~((1<<PD2)|(1<<PD5));

//Button operation check
if((PINE &(1<<PINE4))==0){
PORTD |=_BV(PD2);
}
if((PINE &(1<<PINE5))==0){
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