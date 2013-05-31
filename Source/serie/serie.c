//Funciones para la transmición/recepción de datos a través de RS232

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define USART_BAUDRATE 	9600
#define BAUD_PRESCALE 	(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)		//Primer duda existencial, el clock es de 8MHz, entonces sería 8UL?

void usart_init();

int main()
{

	unsigned char toogle;

	usart_init();	//Inicialización de la interrupción
	sei();		//Esta función se llama para activar las interrupciones
		
	DDRB = (1<<PB0);
	for (;;)
	{
		
		PORTB |= (1 << PB0);
		_delay_ms(10);
		PORTB &= ~(1 << PB0);
		_delay_ms(10);
		
		/*
		if(toogle == 1){
			toogle = 0;
			PORTB |= (1 << PB0);
		}
		else{
			toogle = 1;
			PORTB &= ~(1<<PB0);			
		}
		*/
	}
}

void usart_init()
{
	UCSRB |= (1<<RXCIE) | (1 << RXEN) | (1 << TXEN);   	//Encender recepción transmición
								
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); 	//Configuro para usar 8 caracteres

	UBRRL = BAUD_PRESCALE; 					// Cargo la parte baja del registro
								
	UBRRH = (BAUD_PRESCALE >> 8); 				// Cargo la parte alta del registro
}

ISR (USART_RXC_vect)
{
	unsigned char value;

	value = UDR;				 		// Tomo el valor recibido, y lo cargo en la variable value
	UDR = value;				   		// Cargo el buffer con lo almacenado en la variable value
}
