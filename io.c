#include <avr/io.h>
#include <util/delay.h>

int init_io(){
DDRD  |= (1<<PD2);
PORTD |= (1<<PD2);
return (0);
}

int main(void){
init_io();

}