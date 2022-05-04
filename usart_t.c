#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


int numbers[16] ={~237,~72,~103,~110,~202,~174,~175,~104,~239,~238,~235,~143,~165,~79,~167,~163};
int counter=0;
void main(void){
UCSR0B|= (1<<RXEN0)|(1<<TXEN0);
UCSR0C |= (1<<USBS)|(3<<UCSZ0);			//=(1<<UMSEL0);
USART_Init ( MYUBRR );

DDRC=255;


for(;;){
USART_Transmit("a");
PORTC=numbers[counter];
_delay_ms(100);
;
}
}

void USART_Transmit( unsigned char data )
{
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
;
/* Put data into buffer, sends the data */
UDR0 = data;
counter++;
if(counter>15)
counter=0;
}
void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;

}
