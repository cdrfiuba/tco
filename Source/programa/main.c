/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	main.c									*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo del		*
 *			programa principal.							*
 *												*
 *	Última modificación: 02/06/2013								*
 *												*
 ***********************************************************************************************/

#include "main.h"

unsigned char	buff_rx[MAX_STRING];
unsigned int	indice_rx;

unsigned char value;

int main(void)
{
	usart_init();		//Inicialización de la interrupción
	//sei();			//Activación de las interrupciones

	/*
	inicializar_PWM();	//Inicialización del PWM
	motores_detener();	//Detengo los motores

    	avanzar_celda(); //avanza una distancia de una celda hacia adonde este apuntando el robot

	*/

	inicializar_puertos_sensores_pared();

	for (;;)
	{
		UDR = prueba_rapida_sensor_pared(); 

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

/*
void enviar_string(unsigned char *cadena){

	unsigned int i;

	unsigned int longitud = strlen(cadena);

	for(i = 0; i < longitud; i++){

		while(!UCSRA);					//Espero que se libere el buffer de transimición
		UDR = cadena[i];
	}
}
*/

ISR (USART_RXC_vect)						//Interrupción puerto serie
{
	/*
	unsigned char value;

	if(indice_rx < MAX_STRING){

		buff_rx[indice_rx] = UDR;
		indice_rx++;

	}

	else{
		indice_rx = 0;

	}
	*/
	
	//El código comentado sirve para implementar un echo.
	value = UDR;				 		// Tomo el valor recibido, y lo cargo en la variable value
	UDR = value;				   		// Cargo el buffer con lo almacenado en la variable value
}


