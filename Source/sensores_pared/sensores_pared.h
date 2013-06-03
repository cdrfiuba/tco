/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	sensores_pared.h							*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	*
 *			sensores HC-SR04, para la medición de distancia a las paredes.		*
 *												*
 *	Última modificación: 03/06/2013								*
 *												*
 ***********************************************************************************************/


#include <avr/io.h>
#include <util/delay.h>

#define	SENSOR_PARED_IZQ_TRIG	(1<<PA4)
#define SENSOR_PARED_IZQ_ECHO	(1<<PB2)
  
#define	SENSOR_PARED_DER_TRIG	(1<<PA3)
#define SENSOR_PARED_DER_ECHO	(1<<PB2)

#define	SENSOR_PARED_CENT_TRIG	(1<<PA2)
#define SENSOR_PARED_CENT_ECHO	(1<<PB2)

