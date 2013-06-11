/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *											                                                	*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *											                                                	*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace            			*
 *												                                                *
 *	Archivo:	    main.h								                                        *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo del		        *
 *			        programa principal.							                                *
 *												                                                *
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pwm.h"
#include "motores.h"
#include "sensores_pared.h"
#include "encoders.h"

#define USART_BAUDRATE 	9600
#define BAUD_PRESCALE 	(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define MAX_STRING	25

#define DISTANCIA_CHICA   0x1E
#define DISTANCIA_GRANDE  0x8C

#endif /* _MAIN_H_ */

//Definición de prototipos
void usart_init(void);
void mantener_distancia (uint8_t, uint8_t);
