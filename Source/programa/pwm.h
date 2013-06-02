/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	pwm.h									*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo del PWM.	*
 *												*
 *	Última modificación: 02/06/2013								*
 *												*
 ***********************************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

void inicializar_PWM	(void);
void variar_velocidad	(unsigned char, unsigned char);


