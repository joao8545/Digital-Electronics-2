#include <avr/io.h>
#include <util/delay.h>


int counter[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};
int counter2[4]= {4,32,16,8};
int n;
int main(void){

DDRC=255;
DDRD=255;
while(1){
for(int i=0;i<16;i++){
_delay_ms(200);
PORTC = counter[i];
n=(i+1)%4;
PORTD=~counter2[n];
//PORTD=(~i)<<2;
_delay_ms(200);
}
for(int i=15;i>-1;i--){
_delay_ms(200);
PORTC = counter[i];
n=(i+1)%4;
PORTD=~counter2[n];
//PORTD=(~i)<<2;
_delay_ms(200);
}
}
return 0;

} 
