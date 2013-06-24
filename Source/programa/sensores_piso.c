/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *											                                                	*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *											                                                	*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace            			*
 *												                                                *
 *	Archivo:	    sensores_piso.c 					                                        *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los	        *
 *			        sensores del piso       					                                *
 *												                                                *
 *	Última modificación: 24/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "sensores_piso.h"


/*los tres sensores del piso estan conectados a la misma interrupcion externa INT2
y a su vez a PA0=izq PA1=der y PA2=centro
La idea con este codigo es primero inicializar las interrupciones por flanco ascendente (usando algun tipo de debouncer  para evitar efecto rebote)
y poder identificar que interrupción fue activada para luego poder usarla en el codigo del robot.
*/

inline void encender_sensores_piso(void){

    PORTC |= (1<<1);

}


inline void apagar_sensores_piso(void){

    PORTC &= ~(1<<1);

}


void inicializar_sensores_piso(void)
{

    //Configuro el pin de los CNY70 como salida.
    DDRC    |= (1<<1);

    //configuro el pin de interrupcion como entrada (no se si es necesario)
    DDRB    &= ~(1<<2);
    PORTB   &= ~(1<<2);

    // activamos la interrupcion INT2 por flanco ascendente ISC2=1
    MCUCSR |= (1<<ISC2);

    //configuramos General Interrupt Control Register – GICR ={INT1 INT0 INT2 – – – IVSEL IVCE}
    //activamos la interrupcion INT2=1
    GICR |= (1<<INT2);

}
