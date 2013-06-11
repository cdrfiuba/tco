/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *												                                                *
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *												                                                *
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			            *
 *												                                                *
 *	Archivo:	    encoder.h				    	                                            *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	        *
 *			        encoders                                                        	        *
 *												                                                *
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#ifndef _ENCODERS_H_
#define _ENCODERS_H_


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void inicializar_encoders(void);

#endif
