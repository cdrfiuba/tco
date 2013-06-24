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
 *	Última modificación: 15/06/2013								                                *
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
DDRC |= (1<<1);


//GIMSK  |= (1<<INT2);

//configuro el pin de interrupcion como salida para poder activarlo por soft
//DDRB |= (1<<DDB2);

//configuro el pin de interrupcion como entrada (no se si es necesario)
DDRB &= ~(1<<2);
PORTB &= ~(1<<2);

//configuramos PA0 PA1 y PA2 como entradas sin pullup

//DDRA &= ~((1<<DDA0)|(1<<DDA1)|(1<<DDA2));
//PORTA &= ~((1<<PORTA0)|(1<<PORTA1)|(1<<PORTA2));

//configuro registro MCUCSR ={JTD ISC2 – JTRF WDRF BORF EXTRF PORF }

// activamos la interrupcion INT2 por flanco ascendente ISC2=1

MCUCSR |= (1<<ISC2);

/* [1]
Finally, the INT2 Interrupt Flag should be cleared by writing a logi-
cal one to its Interrupt Flag bit (INTF2) in the GIFR Register before the interrupt is re-enabled.
*/

//configuramos General Interrupt Control Register – GICR ={INT1 INT0 INT2 – – – IVSEL IVCE}
//activamos la interrupcion INT2=1

GICR |= (1<<INT2);

}
