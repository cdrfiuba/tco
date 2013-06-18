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
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "motores.h"

extern volatile uint32_t     cuenta_encoder_derecha, cuenta_encoder_izquierda;

//////////////////////////////////////////////////////////////////////////////////////////////////

void inicializar_puertos_motores(void){

	//Configuro pines como salida
	DDRB |= MOTOR_DER_BRAKE;
	DDRB |= MOTOR_IZQ_BRAKE;

	DDRD |= MOTOR_DER_DIRECTION;
	DDRD |= MOTOR_IZQ_DIRECTION;
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

void motores_avanzar(uint8_t velocidad_izquierda, uint8_t velocidad_derecha){

	//Avance sensito 2: PWM H - Direction L - Brake L

	PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

	PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2


	variar_PWM(velocidad_izquierda, velocidad_derecha);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_detener(void){

	//Freno: poner brake en alto
	PORTB |= MOTOR_DER_BRAKE;	//Pongo en alto el pin BRAKE del motor 1
	PORTB |= MOTOR_IZQ_BRAKE;	//Pongo en alto el pin BRAKE del motor 2
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_rotar_der_90_grados(void){

    uint8_t  flag_fin_rotacion = FALSE;
    uint32_t cuenta_inicial_encoder_derecho     =   cuenta_encoder_derecha;
    uint32_t cuenta_inicial_encoder_izquierdo   =   cuenta_encoder_izquierda;

    variar_PWM(200, 200);

    PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
    PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

    PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
    PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

    while(flag_fin_rotacion == FALSE){

        if(cuenta_encoder_derecha >= (cuenta_inicial_encoder_derecho + 300)){

            if(cuenta_encoder_izquierda >= (cuenta_inicial_encoder_izquierdo + 300)){

                PORTB |= MOTOR_DER_BRAKE;	//Pongo en alto el pin BRAKE del motor 1
                PORTB |= MOTOR_IZQ_BRAKE;	//Pongo en alto el pin BRAKE del motor 2

                flag_fin_rotacion = TRUE;

            }
        }
    }
}


void motores_rotar_izq_90_grados(void){

    uint8_t  flag_fin_rotacion = FALSE;
    uint32_t cuenta_inicial_encoder_derecho     =   cuenta_encoder_derecha;
    uint32_t cuenta_inicial_encoder_izquierdo   =   cuenta_encoder_izquierda;

    variar_PWM(200, 200);

    PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
    PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

    PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
    PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

    while(flag_fin_rotacion == FALSE){

        if(cuenta_encoder_derecha >= (cuenta_inicial_encoder_derecho + 315)){

            if(cuenta_encoder_izquierda >= (cuenta_inicial_encoder_izquierdo + 315)){

                //Antes tenia 300

                PORTB |= MOTOR_DER_BRAKE;	//Pongo en alto el pin BRAKE del motor 1
                PORTB |= MOTOR_IZQ_BRAKE;	//Pongo en alto el pin BRAKE del motor 2

                flag_fin_rotacion = TRUE;

            }
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////
