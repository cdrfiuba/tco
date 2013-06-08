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
 *	Última modificación: 06/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "motores.h"

extern uint32_t     cuenta_encoder_derecha, cuenta_encoder_izquierda, cuenta_motor_celda; //harcodear cuenta_motor_X para obtener numero que de con medida de avance necesaria
uint32_t            cuenta_motor_derecha, cuenta_motor_izquierda;

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



    //hacer cuenta para convertir grados en cantidad de eventos encoder
    PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
    PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1

    PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
    PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

    //Agregar cuando detener la rotación

    _delay_ms(190);


}


void motores_rotar_izq_90_grados(void){

    PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
    PORTB &= ~MOTOR_DER_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 1


    PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
    PORTB &= ~MOTOR_IZQ_BRAKE;	    //Pongo en bajo el pin BRAKE del motor 2

    _delay_ms(170);
}


void girar_poquito_izquierda(void){

    motores_avanzar(200,180);
}


void girar_poquito_derecha(void){

    motores_avanzar(180,200);

}




//////////////////////////////////////////////////////////////////////////////////////////////////

/*

void motores_rotar_izquierda(unsigned char grados){

	//hacer cuenta para convertir grados en cantidad de eventos encoder

	//El motor derecho avanza.
	PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	//El motor izquierdo retrocede
	PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	while(cuenta_motor_izquierda != grados)
		cuenta_motor_izquierda 	= cuenta_encoder_izquierda   * 256 + TCNT0;


}*/


//////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////
