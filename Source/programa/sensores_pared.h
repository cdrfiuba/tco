/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *												                                                *
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *												                                                *
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			            *
 *												                                                *
 *	Archivo:	    sensores_pared.h				    	                                    *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	        *
 *			        sensores HC-SR04, para la medición de distancia a las paredes.		        *
 *												                                                *
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#ifndef _SENSORES_PARED_H_
#define _SENSORES_PARED_H_

#include <avr/io.h>
#include <util/delay.h>

#define	SENSOR_PARED_IZQ	(1 << PA3)
#define	SENSOR_PARED_DER	(1 << PA4)
#define	SENSOR_PARED_CEN	(1 << PA5)
#define SENSOR_PARED_ECHO	    (1 << PB2)

#define CANTIDAD    10


#endif

//Definición de prototipos
inline void  apagar_timer(void);
inline void	encender_timer(void);
void        inicializar_timer(void);
void        inicializar_puertos_sensores_pared(void);
uint8_t     prueba_rapida_sensor_pared(uint8_t);




