/************************************************************************************************
 *											                                                	*
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *												                                                *
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *												                                                *
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			            *
 *										                                                		*
 *	Archivo:	    pwm.h									                                    *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo del PWM.	    *
 *												                                                *
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#ifndef _PWM_H_
#define _PWM_H_

#include <avr/io.h>
#include <util/delay.h>

#endif


//Definición de prototipos
void inicializar_PWM    (void);
void variar_PWM         (uint8_t valor_izq, uint8_t valor_der);
