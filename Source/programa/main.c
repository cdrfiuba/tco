//Funciones para la transmición/recepción de datos a través de RS232

#include "main.h"


int main()
{
	usart_init();	//Inicialización de la interrupción
	sei();		//Esta función se llama para activar las interrupciones

	inicializar_PWM();
	motores_detener();
		
	for (;;)
	{
	
	}

	return 0;
}



void usart_init()
{
	UCSRB |= (1<<RXCIE) | (1 << RXEN) | (1 << TXEN);   	//Encender recepción transmición
								
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); 	//Configuro para usar 8 caracteres

	UBRRL = BAUD_PRESCALE; 					// Cargo la parte baja del registro
								
	UBRRH = (BAUD_PRESCALE >> 8); 				// Cargo la parte alta del registro
}


ISR (USART_RXC_vect)						//Interrupción puerto serie
{
	unsigned char value;

	value = UDR;				 		// Tomo el valor recibido, y lo cargo en la variable value
	UDR = value;				   		// Cargo el buffer con lo almacenado en la variable value
}


