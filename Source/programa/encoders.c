/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *											                                                	*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *											                                                	*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace            			*
 *												                                                *
 *	Archivo:	    encoders.c  							                                    *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los          *
 *			        encoders.                                                                   *
 *												                                                *
 *	Última modificación: 13/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "encoders.h"

void inicializar_encoders(void){

    //Configuro el encoder usando el pin como entrada
    DDRD    &= ~(1<<PD3);   //Configuro como entrada
    PORTD   &= ~(1<<PD3);   //Desactivo el pull up

    //Configuro el encoder usando el pin como entrada
    DDRD    &= ~(1<<PD2);   //Configuro como entrada
    PORTD   &= ~(1<<PD2);   //Desactivo el pull up

    GICR |= (1<<INT0);      //Activo INT0
    GICR |= (1<<INT1);      //Activo INT1
    GICR &= ~(1<<INT2);     //Desactivo INT2

    MCUCR |= ((1<<ISC01) | (1<<ISC00));     //Configuro la INT0 por flanco ascendente
    MCUCR |= ((1<<ISC11) | (1<<ISC10));     //Configuro la INT1 por flanco ascendente

}




