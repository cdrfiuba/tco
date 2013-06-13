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
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "main.h"

volatile uint32_t   interrupciones_timer_1, distancia, cuenta_encoder_derecha, cuenta_encoder_izquierda;
volatile uint8_t    status_flag, value;
uint8_t             sensor_active;

int main(void)
{
	usart_init();		    //Inicializ••••••••••ación de la interrupción
	sei();			        //Activación de las interrupciones

    inicializar_puertos_sensores_pared();
    inicializar_encoders();
    inicializar_puertos_motores();
    inicializar_PWM();
    motores_detener();

	for (;;)
	{

        /*
        //Enviar distancia por puerto serie, funciona OK. Prueba 12/06/13

        _delay_ms(1000);

        distancia = prueba_rapida_sensor_pared(SENSOR_PARED_CEN);

        _delay_ms(100);

        while(!UCSRA);
        UDR = (uint8_t)((distancia >> 24) & 0x000000FF);

         _delay_ms(100);

        while(!UCSRA);
        UDR = (uint8_t)((distancia >> 16) & 0x000000FF);

         _delay_ms(100);

        while(!UCSRA);
        UDR = (uint8_t)((distancia >> 8) & 0x000000FF);

         _delay_ms(100);

        while(!UCSRA);
        UDR = (uint8_t)((distancia) & 0x000000FF);
        */


        //Prueba encoders
        _delay_ms(1000);

        while(!UCSRA);
        UDR = (uint8_t)((cuenta_encoder_izquierda >> 24) & 0x000000FF);

        _delay_ms(100);

        while(!UCSRA);
        UDR = (uint8_t)((cuenta_encoder_izquierda >> 16) & 0x000000FF);

        _delay_ms(100);

        while(!UCSRA);
        UDR = (uint8_t)((cuenta_encoder_izquierda >> 8) & 0x000000FF);

        _delay_ms(100);

        while(!UCSRA);
        UDR = (uint8_t)((cuenta_encoder_izquierda) & 0x000000FF);



        /*

        motores_avanzar(170,170);

        _delay_ms(200);

        motores_detener();

        distancia = prueba_rapida_sensor_pared(SENSOR••••••••••_PARED_DER);

        if(distancia > DISTANCIA_GRANDE){

        //Si entro aca es que no tengo pared a la derecha, entonces, giro a la derecha

             motores_detener();
            _delay_ms(200);
            //motores_avanzar(170,170);
            //_delay_ms(200);
            motores_rotar_der_90_grados();
            _delay_ms(50);
            motores_detener();
            _delay_ms(200);
            motores_avanzar(170,170);
            _delay_ms(500);
             motores_detener();

        }

        else{

            //Si entro aca, es que tengo pared a la derecha

            distancia = prueba_rapida_sensor_pared(SENSOR_PARED_CEN);

            if(distancia < DISTANCIA_CHICA){

                //Si entro aca, tengo pared a la derecha, y tengo pared al frente

                motores_detener();
                _delay_ms(100);
                motores_retroceder(170,170);
                _delay_ms(150);
                motores_detener();
                // motores_avanzar(170,170);
                //_delay_ms(200);
                motores_rotar_izq_90_grados();
                _delay_ms(50);
                motores_detener();
                _delay_ms(200);

                distancia = prueba_rapida_sensor_pared(SENSOR_PARED_CEN);

                if(distancia < DISTANCIA_CHICA){

                    //Si entro aca, es que tengo pared a la derecha, al frente y a la izquierda.

                    motores_detener();
                    _delay_ms(100);
                    // motores_avanzar(170,170);
                    //_delay_ms(200);
                    motores_rotar_izq_90_grados();
                    _delay_ms(50);
                    motores_detener();
                    _delay_ms(200);

                }

                motores_avanzar(170,170);
                _delay_ms(500);
                motores_detener();

            }

            else{

            }
        }*/
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


//Interrupción Timer 0
ISR (TIMER0_OVF_vect)
{
    cuenta_encoder_derecha++;
}


//Interrupción Timer 1
ISR (TIMER1_OVF_vect){

    if (sensor_active)
        interrupciones_timer_1++;

	if(interrupciones_timer_1 > MAX_INTERRUPCIONES_SENSOR_DISTANCIA)
        status_flag = 1;
}


//Interrupción Timer 2
ISR (TIMER2_OVF_vect)
{
    cuenta_encoder_izquierda++;
}
