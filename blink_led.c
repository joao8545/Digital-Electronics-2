#include <avr/io.h>
#include <util/delay.h>


int set_bit(int PORT, int bit){
int mask=1<<bit;
return PORT | mask;
}

int reset_bit(int PORT, int bit){
int mask=1<<bit;
return PORT & ~mask;
}


int counter[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};
int counter2[4]= {4,32,16,8};
int counter3[4]= {60,32,48,56};
int n;

int main(void){

DDRC=255;
DDRD=255;
PORTD=255;
//PORTD=reset_bit(PORTD,5);
while(1){
for(int i=0;i<16;i++){
_delay_ms(200);
PORTC = counter[i];
n=(i+1)%4;
PORTD=~counter3[n];
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
