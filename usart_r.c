#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 8000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int numbers[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};
int counter=0,i;
unsigned char rcv;

void USART_Transmit( unsigned char data ){
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = data;
counter++;
if(counter>15)
counter=0;
}
void USART_Init( unsigned int ubrr ){
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;

}

unsigned char USART_Receive( void ){
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;
}

int main(void){
UCSR0B|= (1<<RXEN0)|(1<<TXEN0);
UCSR0C |= (1<<USBS)|(3<<UCSZ0);			//=(1<<UMSEL0);
USART_Init( MYUBRR );

DDRC=255;


for(;;){
//USART_Transmit("a");
rcv=USART_Receive();
i=rcv-61;
if(i>=0 && i<=15){

PORTC=numbers[i];
}
//_delay_ms(100);
;
}
return 0;
}

