/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	main.h									*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo del		*
 *			programa principal.							*
 *												*
 *	Última modificación: 02/06/2013								*
 *												*
 ***********************************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include "pwm.h"
#include "motores.h"

#ifndef MAIN_H_
#define MAIN_H_

#define USART_BAUDRATE 	9600
#define BAUD_PRESCALE 	(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define MAX_STRING	25

#endif /* MAIN_H_ */


//Definición de prototipos
void usart_init();
void enviar_string(unsigned char *);
