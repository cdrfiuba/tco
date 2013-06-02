/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	motores.h								*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	*
 *			motores.								*
 *												*
 *	Última modificación: 02/06/2013								*
 *												*
 ***********************************************************************************************/

#include "motores.h"

extern unsigned long cuenta_motor_derecha, cuenta_encoder_derecha, cuenta_motor_izquierda, cuenta_encoder_izquierda;

//////////////////////////////////////////////////////////////////////////////////////////////////

void inicializar_puertos_motores(void){

	//Configuro pines como salida
	DDRB |= MOTOR_DER_BRAKE;	
	DDRB |= MOTOR_IZQ_BRAKE;

	DDRD |= MOTOR_DER_DIRECTION;
	DDRD |= MOTOR_IZQ_DIRECTION;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_avanzar(unsigned char velocidad_izquierda, unsigned char velocidad_derecha){

	//Avance sentido 1: PWM H - Direction H - Brake L

	PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	variar_PWM(velocidad_izquierda, velocidad_derecha);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_retroceder(unsigned char velocidad_izquierda, unsigned char velocidad_derecha){

	//Avance sensito 2: PWM H - Direction L - Brake L

	PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	variar_PWM(velocidad_izquierda, velocidad_derecha);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_detener(void){

	//Freno: poner brake en alto
	PORTB |= MOTOR_DER_BRAKE;	//Pongo en alto el pin BRAKE del motor 1
	PORTB |= MOTOR_IZQ_BRAKE;	//Pongo en alto el pin BRAKE del motor 2
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_rotar_derecha(unsigned char grados){

	//hacer cuenta para convertir grados en cantidad de eventos encoder

	//El motor derecho retrocede.
	PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	//El motor izquierdo avanza
	PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	while(cuenta_motor_derecha != grados)
		cuenta_motor_derecha 	= cuenta_encoder_derecha   * 256 + TCNT0;

}		



//////////////////////////////////////////////////////////////////////////////////////////////////

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


}


//////////////////////////////////////////////////////////////////////////////////////////////////
