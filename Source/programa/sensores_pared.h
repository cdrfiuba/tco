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

#ifndef _SENSORES_PARED_H_
#define _SENSORES_PARED_H_

#include <avr/io.h>
#include <util/delay.h>


void 		inicializar_puertos_sensores_pared(void);
unsigned char 	prueba_rapida_sensor_pared(void);

#define	SENSOR_PARED_IZQ_TRIG	(1<<3)
#define SENSOR_PARED_IZQ_ECHO	(1<<2)  //revisar
  
#define	SENSOR_PARED_DER_TRIG	(1<<4)
#define SENSOR_PARED_DER_ECHO	(1<<2)  //revisar

#define	SENSOR_PARED_CEN_TRIG	(1<<5)
#define SENSOR_PARED_CEN_ECHO	(1<<2)  //revisar

#endif

