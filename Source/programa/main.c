/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *											                                                	*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *											                                                	*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace            			*
 *												                                                *
 *	Archivo:	    main.c								                                        *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo del		        *
 *			        programa principal.							                                *
 *												                                                *
 *	Última modificación: 06/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "main.h"

volatile uint8_t 	status_flag;
uint8_t             value, distancia;

int main(void)
{
	inicializar_timer();	//Configuro la interrupción por timer
	usart_init();		    //Inicialización de la interrupción
	sei();			        //Activación de las interrupciones

    inicializar_puertos_sensores_pared();
    inicializar_puertos_motores();
    inicializar_PWM();
    motores_detener();

	for (;;)
	{
        _delay_ms(100);
        //mantener_distancia (SENSOR_PARED_CEN, 0x4E);

        distancia = prueba_rapida_sensor_pared(SENSOR_PARED_CEN);

        if(distancia < 0x4E)

            motores_retroceder(127,127);

        else if (distancia > 0x6E)

            motores_avanzar(127,127);

        else

            motores_detener();
    }

	return 0;
}


//Inicialización puerto serie
void usart_init()
{
	UCSRB |= (1<<RXCIE) | (1 << RXEN) | (1 << TXEN);   	    //Encender recepción transmición

	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); 	//Configuro para usar 8 caracteres

	UBRRL = BAUD_PRESCALE; 					                // Cargo la parte baja del registro

	UBRRH = (BAUD_PRESCALE >> 8); 				            // Cargo la parte alta del registro
}

//Interrupción puerto serie
ISR (USART_RXC_vect){

    //Echo: Esta función recibe un dato por el puerto serie y lo reenvia. Sirve para probar que la conexión esta OK

	value = UDR;    // Tomo el valor recibido, y lo cargo en la variable value
	UDR = value;	// Cargo el buffer con lo almacenado en la variable value
}


//Interruoción overflow timer 0
ISR (TIMER0_OVF_vect){

	status_flag = 1;

}


void mantener_distancia (uint8_t direccion, uint8_t distancia){

    uint8_t distancia_medida = prueba_rapida_sensor_pared(direccion);

    while(distancia_medida != distancia){

        if(distancia_medida < distancia)

            motores_retroceder(127,127);

        else
            motores_avanzar(127,127);
    }

}

/*
void seguir_pared(uint8_t direccion , uint8_t distancia, uint8_t velocidad_izq, uint8_t velocidad_der){

    motores_avanzar(velocidad_izq,velocidad_der);

    uint8_t distancia_medida = prueba_rapida_sensor_pared(direccion);




}
*/




