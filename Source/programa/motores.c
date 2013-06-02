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


//////////////////////////////////////////////////////////////////////////////////////////////////

void inicializar_puertos_motores(void){

	//Configuro pines como salida
	DDRB |= MOTOR_1_BRAKE;	
	DDRB |= MOTOR_2_BRAKE;

	DDRD |= MOTOR_1_DIRECTION;
	DDRD |= MOTOR_2_DIRECTION;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_avanzar(unsigned char velocidad){

	//Avance sentido 1: PWM H - Direction H - Brake L

	PORTD |= MOTOR_1_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_1_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	PORTD |= MOTOR_2_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_2_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	variar_PWM(velocidad, velocidad);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_retroceder(unsigned char velocidad){

	//Avance sensito 2: PWM H - Direction L - Brake L

	PORTD &= ~MOTOR_1_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_1_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	PORTD &= ~MOTOR_2_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_2_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	variar_PWM(velocidad, velocidad);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_detener(void){

	//Freno: poner brake en alto
	PORTB |= MOTOR_1_BRAKE;	//Pongo en alto el pin BRAKE del motor 1
	PORTB |= MOTOR_2_BRAKE;	//Pongo en alto el pin BRAKE del motor 2
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_rotar_derecha(unsigned char grados){


}



//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_rotar_izquierda(unsigned char grados){


}


//////////////////////////////////////////////////////////////////////////////////////////////////
