/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *												                                                *
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *												                                                *
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			            *
 *												                                                *
 *	Archivo:	    motores.c           					                                    *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	        *
 *			        motores.								                                    *
 *												                                                *
 *	Última modificación: 24/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "motores.h"

extern volatile uint32_t     cuenta_encoder_derecha, cuenta_encoder_izquierda;

//////////////////////////////////////////////////////////////////////////////////////////////////

void inicializar_puertos_motores(void){

	//Configuro pines como salida
	DDRD |= MOTOR_DER_DIRECTION;
	DDRB |= MOTOR_DER_BRAKE;

	DDRB |= MOTOR_IZQ_BRAKE;
    	DDRD |= MOTOR_IZQ_DIRECTION;

    	//Detengo los motores una vez que inicializo los puertos.
    	motores_detener();
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_detener(void){

	TCCR1B = 0;
	TCCR1B = ((0 << WGM13)|(1 << WGM12));

	//Freno: poner brake en alto
	PORTB |= MOTOR_DER_BRAKE;	//Pongo en alto el pin BRAKE del motor 1
	PORTB |= MOTOR_IZQ_BRAKE;	//Pongo en alto el pin BRAKE del motor 2

	//
	PORTD &= ~(MOTOR_DER_PWM);
	PORTD &= ~(MOTOR_IZQ_PWM);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_retroceder(uint8_t velocidad_izquierda, uint8_t velocidad_derecha){

	//Avance sentido 1: PWM H - Direction H - Brake L

	PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

	PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

    variar_PWM(velocidad_izquierda, velocidad_derecha);

}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_avanzar(uint8_t velocidad_izquierda, uint8_t velocidad_derecha, uint32_t cantidad_cuentas){

	uint8_t  flag_fin_avance = FALSE;
    	uint32_t cuenta_encoder_derecha_anterior;

	// Enciendo el timer por si lo apagué al frenar los motores.
	TCCR1B |= ((0<<CS12)|(0<<CS11)|(1<<CS10));

	// Pongo a cero los valores del encoder
	cuenta_encoder_derecha = 0;
	cuenta_encoder_izquierda = 0;
	cuenta_encoder_derecha_anterior = 0;

    	variar_PWM(velocidad_izquierda, velocidad_derecha);

	//Un motor avanza, el otro retrocede, entonces el robot avanza.
    	PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1
	PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2


    	while(flag_fin_avance == FALSE){

		//
		if((cuenta_encoder_derecha_anterior + 5) >= cuenta_encoder_derecha){

		    cuenta_encoder_derecha_anterior = cuenta_encoder_derecha;

		    if(cuenta_encoder_derecha < cuenta_encoder_izquierda){

			//255 es la velocidad máxima
			if(velocidad_derecha < 250)
			    variar_PWM(velocidad_izquierda, velocidad_derecha += 10);
			}

		    if(cuenta_encoder_derecha > cuenta_encoder_izquierda){

			//130 es el valor mínimo de PWM para mover al robot
			if(velocidad_derecha > 130)
			    variar_PWM(velocidad_izquierda, velocidad_derecha -= 10);
		    }
		}

		if(cantidad_cuentas < cuenta_encoder_derecha){    

			motores_detener();

			flag_fin_avance = TRUE;
		}
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_rotar_der_90_grados(void){

	uint8_t  flag_fin_rotacion = FALSE;
	uint32_t cuenta_inicial_encoder_derecha     =   cuenta_encoder_derecha;
	uint32_t cuenta_inicial_encoder_izquierda   =   cuenta_encoder_izquierda;

	// Enciendo el timer por si lo apagué al frenar los motores.
	TCCR1B |= ((0<<CS12)|(0<<CS11)|(1<<CS10));

	variar_PWM(220, 220);

	// Configuro al puente H para que los motores giren para el mismo lado, y entonces el robot gire a la derecha.
	PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1
	PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

    while(flag_fin_rotacion == FALSE){

        if(cuenta_encoder_derecha >= (cuenta_inicial_encoder_derecha + 340)){

			variar_PWM(255, 220);

            if(cuenta_encoder_izquierda >= (cuenta_inicial_encoder_izquierda + 340)){

				break;

            }
        }

		if(cuenta_encoder_izquierda >= (cuenta_inicial_encoder_izquierda + 340)){

			variar_PWM(220, 255);

            if(cuenta_encoder_derecha >= (cuenta_inicial_encoder_derecha + 340)){

				break;

            }
        }
    }

	motores_detener();

    flag_fin_rotacion = TRUE;
}


void motores_rotar_izq_90_grados(void){

    uint8_t  flag_fin_rotacion = FALSE;
    uint32_t cuenta_inicial_encoder_derecha     =   cuenta_encoder_derecha;
    uint32_t cuenta_inicial_encoder_izquierda   =   cuenta_encoder_izquierda;

	// Enciendo el timer por si lo apagué al frenar los motores.
	TCCR1B |= ((0<<CS12)|(0<<CS11)|(1<<CS10));

    variar_PWM(210, 210);

    PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
    PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

    PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
    PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

   while(flag_fin_rotacion == FALSE){

        if(cuenta_encoder_derecha >= (cuenta_inicial_encoder_derecha + 335)){

			variar_PWM(255, 220);

            if(cuenta_encoder_izquierda >= (cuenta_inicial_encoder_izquierda + 335)){

				break;

            }
        }

		if(cuenta_encoder_izquierda >= (cuenta_inicial_encoder_izquierda + 335)){

			variar_PWM(220, 255);

            if(cuenta_encoder_derecha >= (cuenta_inicial_encoder_derecha + 335)){

				break;

            }
        }
    }

	motores_detener();

    flag_fin_rotacion = TRUE;
}



void motores_corregir_rumbo (void){

    uint32_t distancia;
    uint8_t  flag_fin_rotacion = FALSE;

	// Enciendo el timer por si lo apagué al frenar los motores.
	TCCR1B |= ((0<<CS12)|(0<<CS11)|(1<<CS10));

    cuenta_encoder_derecha = 0;
    cuenta_encoder_izquierda = 0;

    _delay_ms(10);

    distancia = medicion_distancia_pared(SENSOR_PARED_DER);

    _delay_ms(10);

    if(distancia < 0x00000700){

        variar_PWM(200, 200);

        PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
        PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

        PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
        PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

        while(flag_fin_rotacion == FALSE){

            if(cuenta_encoder_derecha >= 10){

				variar_PWM(255, 220);

		        if(cuenta_encoder_izquierda >= 10){

					break;
		        }
		    }

			if(cuenta_encoder_izquierda >= 10){

				variar_PWM(220, 255);

		        if(cuenta_encoder_derecha >= 10){

					break;

		        }
		    }
    	}
	}

    if(distancia > 0x00000750){

        variar_PWM(200, 200);

        PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
        PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

        PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
        PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

        while(flag_fin_rotacion == FALSE){

		    if(cuenta_encoder_derecha >= 10){

				variar_PWM(255, 220);

		        if(cuenta_encoder_izquierda >= 10){

					break;

		        }
		    }

			if(cuenta_encoder_izquierda >= 10){

				variar_PWM(220, 255);

		        if(cuenta_encoder_derecha >= 10){

					break;

		        }
		    }
		}
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////
