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
 *	Última modificación: 24/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "main.h"

//Delacaración de variables globales

volatile uint8_t    value, flag_piso_blanco;

//Variables encoders
volatile uint32_t   cuenta_encoder_izquierda, cuenta_encoder_derecha;

//Variables sensores pared
volatile uint8_t    sensor_active, status_flag;
volatile uint32_t   interrupciones_timer_1, distancia;


int main(void)
{
	usart_init();			//Inicialización de UART para enviar/recibir datos por serie.
	sei();			        //Activación de las interrupciones.


	inicializar_puertos_sensores_pared();
	//inicializar_sensores_piso();
	inicializar_encoders();       	//Al inicializar los encoders lo que se hace es configurar el TIMER 0 y el TIMER 2
	inicializar_puertos_motores();
	inicializar_PWM();             	//Al inicializar el PWM lo que se hace es configurar el TIMER 1

	cuenta_encoder_derecha = 0;
	cuenta_encoder_izquierda = 0;
	_delay_ms(500);

	for (;;){

        //Se corrige el rumbo, midiendo la distancia a la pared derecha.
        motores_corregir_rumbo();

        //Se avanza una distancia muy pequeña.
        motores_avanzar(200,200, 10);
/*
        //Se mide a la derecha para saber si hay pared o no.
        distancia = medicion_distancia_pared(SENSOR_PARED_DER);

        //Si se entra acá es que no hay pared a la derecha, entonces, se giro a la derecha
        if(distancia > DISTANCIA_GRANDE){

            motores_avanzar(200,200, 200);

            motores_rotar_der_90_grados();

            motores_avanzar(200,200, 450);

        }

        //Si se entra acá, es que hay una pared a la derecha
        else{

            distancia = medicion_distancia_pared(SENSOR_PARED_CEN);

            //Si se entra acá, es que hay pared a la derecha, y al frente
            if(distancia < DISTANCIA_CHICA){

                motores_rotar_izq_90_grados();

                _delay_ms(10);

                distancia = medicion_distancia_pared(SENSOR_PARED_CEN);

                _delay_ms(10);

                //Si se entra acá, es que hay pared a la derecha, al frente y a la izquierda.
                //Entonces rota 180 grados.
                //La distancia tiene que se mayor a distancia chica, porque a veces no queda centrado en la casilla
                if(distancia < 0x00001800){

                    motores_rotar_izq_90_grados();

                }

                motores_avanzar(200,200, 450);
            }
        }
*/
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


//Interrupción Timer 1
ISR (TIMER1_OVF_vect){

    if (sensor_active)
        interrupciones_timer_1++;

	if(interrupciones_timer_1 > MAX_INTERRUPCIONES_SENSOR_DISTANCIA)
        status_flag = 1;
}

//Interrupción INT 0
ISR (INT0_vect)
{
    cuenta_encoder_derecha++;

}

//Interrupción INT 1
ISR (INT1_vect)
{
    cuenta_encoder_izquierda++;

}


//interrupcion sensores de piso

ISR (INT2_vect){

    if((PINA & (1 << PA2)) == (1 << PA2))

       flag_piso_blanco = TRUE;

    //Finalmente hacemos un clear al registro GIFR de interrupcion como se pide en hoja de datos [1].
    GIFR &= ~(1<<INTF2);

}


//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_derecha >> 24) & 0x000000FF);
//
//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_derecha >> 16) & 0x000000FF);
//
//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_derecha >> 8) & 0x000000FF);
//
//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_derecha) & 0x000000FF);
//
//_delay_ms(500);
//
//
//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_izquierda >> 24) & 0x000000FF);
//
//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_izquierda >> 16) & 0x000000FF);
//
//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_izquierda >> 8) & 0x000000FF);
//
//_delay_ms(100);
//
//while(!UCSRA);
//UDR = (uint8_t)((cuenta_encoder_izquierda) & 0x000000FF);
//
//_delay_ms(2500);
