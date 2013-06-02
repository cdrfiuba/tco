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

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pwm.h"


#ifndef MOTORES_H_
#define MOTORES_H_

#define MOTOR_DER_BRAKE		(1<<PB3)
#define MOTOR_IZQ_BRAKE		(1<<PB4)
#define MOTOR_DER_DIRECTION	(1<<PD7)
#define MOTOR_IZQ_DIRECTION	(1<<PD6)

#endif /* MOTORES_H_ */


//Definición de prototipos
void inicializar_puertos_motores	(void);
void motores_avanzar			(unsigned char, unsigned char);
void motores_retroceder			(unsigned char, unsigned char);
void motores_detener			(void);
void motores_rotar_derecha		(unsigned char);
void motores_rotar_izquierda		(unsigned char);
