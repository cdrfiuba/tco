/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *												                                                *
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *												                                                *
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			            *
 *												                                                *
 *	Archivo:	    motores.h								                                    *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	        *
 *			        motores.								                                    *
 *												                                                *
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/
#ifndef MOTORES_H_
#define MOTORES_H_
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include "main.h"
#include "pwm.h"
#include "sensores_pared.h"

#define MOTOR_DER_BRAKE		(1<<PB3)
#define MOTOR_IZQ_BRAKE		(1<<PB4)
#define MOTOR_DER_DIRECTION	(1<<PD7)
#define MOTOR_IZQ_DIRECTION	(1<<PD6)

#define TRUE    1
#define FALSE   0

#endif /* MOTORES_H_ */


//Definición de prototipos
void inicializar_puertos_motores	(void);
void motores_avanzar			    (uint8_t, uint8_t, uint32_t);
void motores_retroceder			    (uint8_t, uint8_t);
void motores_detener			    (void);
void motores_rotar_der_90_grados    ();
void motores_rotar_izq_90_grados    (void);
void motores_corregir_rumbo         (void);

extern void inicializar_PWM         (void);
extern void variar_PWM              (uint8_t, uint8_t);
