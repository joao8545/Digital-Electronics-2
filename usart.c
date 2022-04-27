#include <avr/interrupt.h>
#include <avr/io.h>

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void main(void){
UCSR0B|= (1<<RXEN0)|(1<<TXEN0);
UCSR0C |=(1<<UMSEL0);
USART_Init ( MYUBRR );



for(;;){
USART_Transmit("a");
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
}
void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;

}
