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
 *	Última modificación: 15/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "main.h"

uint8_t             sensor_active, estado_sensor_piso_cen, estado_sensor_piso_der, estado_sensor_piso_izq;
volatile uint32_t   interrupciones_timer_1, distancia, cuenta_encoder_derecha, cuenta_encoder_izquierda;
volatile uint8_t    status_flag, value;


int main(void)
{
	usart_init();		                //Inicialización de UART para enviar/recibir datos por serie.
	sei();			                    //Activación de las interrupciones.


    inicializar_puertos_sensores_pared();
    inicializar_encoders();             //Al inicializar los encoders lo que se hace es configurar el TIMER 0 y el TIMER 2
    inicializar_puertos_motores();
    inicializar_PWM();                  //Al inicializar el PWM lo que se hace es configurar el TIMER 1
    motores_detener();
    inicializar_sensores_piso();

	for (;;)
	{
/*

        while(1){

        //Creo una interrupcion por software
//        _delay_ms(100);
//        PORTB |= (1<<PORTB2);
//        _delay_ms(100);
//        PORTB &= ~(1<<PORTB2);


        if(estado_sensor_piso_cen == 1 && (PINA & (1<<PINA2))){
            motores_avanzar(170,170);
            _delay_ms(100);
            }
        else {
            motores_detener();
            estado_sensor_piso_cen=0;
            _delay_ms(100);
            }

//        _delay_ms(1000);
//
//        estado_sensor_piso_cen=0;
//        motores_detener();
//        estado_sensor_piso_cen=0;
//
//        _delay_ms(500);


        }*/
//
//        //Enviar distancia por puerto serie, funciona OK. Prueba 12/06/13
//
//        _delay_ms(1000);
//
//        distancia = prueba_rapida_sensor_pared(SENSOR_PARED_CEN);
//
//        _delay_ms(100);
//
//        while(!UCSRA);
//        UDR = (uint8_t)((distancia >> 24) & 0x000000FF);
//
//         _delay_ms(100);
//
//        while(!UCSRA);
//        UDR = (uint8_t)((distancia >> 16) & 0x000000FF);
//
//         _delay_ms(100);
//
//        while(!UCSRA);
//        UDR = (uint8_t)((distancia >> 8) & 0x000000FF);
//
//         _delay_ms(100);
//
//        while(!UCSRA);
//        UDR = (uint8_t)((distancia) & 0x000000FF);
//
//
//
//        //Prueba encoders
//
//
       _delay_ms(1000);
//
        while(!UCSRA);
        UDR = TCNT0;
//
//        _delay_ms(100);
//
//        while(!UCSRA);
//        UDR = (uint8_t)((cuenta_encoder_izquierda >> 16) & 0x000000FF);
//
//        _delay_ms(100);
//
//        while(!UCSRA);
//        UDR = (uint8_t)((cuenta_encoder_izquierda >> 8) & 0x000000FF);
//
//        _delay_ms(100);
//
//        while(!UCSRA);
//        UDR = (uint8_t)((cuenta_encoder_izquierda) & 0x000000FF);
//
//
//        motores_avanzar(170,170);
//
//        _delay_ms(200);
//
//        motores_detener();
//
//        distancia = prueba_rapida_sensor_pared(SENSOR_PARED_DER);
//
//        if(distancia > DISTANCIA_GRANDE){
//
//        //Si entro aca es que no tengo pared a la derecha, entonces, giro a la derecha
//
//             motores_detener();
//            _delay_ms(200);
//            //motores_avanzar(170,170);
//            //_delay_ms(200);
//            motores_rotar_der_90_grados();
//            _delay_ms(50);
//            motores_detener();
//            _delay_ms(200);
//            motores_avanzar(170,170);
//            _delay_ms(500);
//             motores_detener();
//
//        }
//
//        else{
//
//            //Si entro aca, es que tengo pared a la derecha
//
//            distancia = prueba_rapida_sensor_pared(SENSOR_PARED_CEN);
//
//            if(distancia < DISTANCIA_CHICA){
//
//                //Si entro aca, tengo pared a la derecha, y tengo pared al frente
//
//                motores_detener();
//                _delay_ms(100);
//                motores_retroceder(170,170);
//                _delay_ms(150);
//                motores_detener();
//                // motores_avanzar(170,170);
//                //_delay_ms(200);
//                motores_rotar_izq_90_grados();
//                _delay_ms(50);
//                motores_detener();
//                _delay_ms(200);
//
//                distancia = prueba_rapida_sensor_pared(SENSOR_PARED_CEN);
//
//                if(distancia < DISTANCIA_CHICA){
//
//                    //Si entro aca, es que tengo pared a la derecha, al frente y a la izquierda.
//
//                    motores_detener();
//                    _delay_ms(100);
//                    // motores_avanzar(170,170);
//                    //_delay_ms(200);
//                    motores_rotar_izq_90_grados();
//                    _delay_ms(50);
//                    motores_detener();
//                    _delay_ms(200);
//
//                }
//
//                motores_avanzar(170,170);
//                _delay_ms(500);
//                motores_detener();
//
//            }
//
//            else{
//
//            }
//        }
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



//interrupcion sensores de piso

ISR (INT2_vect){

//Averiguamos cual de los tres fue el sensor que detecto un flanco ascendente
//para ello leemos el PINA={PINA7 PINA6 PINA5 PINA4 PINA3 PINA2 PINA1 PINA0}


estado_sensor_piso_cen = 1;

//
//if (PINA & (1<<PINA0)){
//    // fue por el sensor izquierdo (tomar medidas en caso seguidor lineas)
//    estado_sensor_piso_izq=1;
//    estado_sensor_piso_cen=0;
//    estado_sensor_piso_der=0;
//    }
//else if(PINA & (1<<PINA1)){
//        //fue por el sensor derecho (tomar medidas en caso seguidor lineas)
//    estado_sensor_piso_izq=0;
//    estado_sensor_piso_cen=0;
//    estado_sensor_piso_der=1;
//        }
//else if(PINA & (1<<PINA2)){
//        //fue por el sensor del centro (tomar medidas en caso seguidor lineas)
//    estado_sensor_piso_izq=0;
//    estado_sensor_piso_cen=1;
//    estado_sensor_piso_der=0;
//        }

//falta el sistema anti-rebote que quizas podria ser un  _delay_ms() aca mismo

//Finalmente hacemos un clear al registro GIFR de interrupcion como se pide en hoja de datos [1].

GIFR &= ~(1<<INTF2);

}



