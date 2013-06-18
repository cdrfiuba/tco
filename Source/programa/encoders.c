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

    //Configuro el encoder de la rueda derecha.

    //Si bien no es necesario, configuro el pin T0 como entrada.
    DDRB &= ~(1<<PB0);

    //Configuración del Timer/Counter Control register
    //TCCR0 = FOC0 - WGM00 - COM01 - COM00 - WGM01 - CS02 - CS01 - CS00

    TCCR0 &= ~((1<<WGM01) & (1<<WGM00) & (1<<COM01) & (1<<COM00));
    TCCR0 |= ((1<<CS02) | (1<<CS01) | (1<<CS00));


    //Bit 7    – FOC0:    Force Output Compare
    //Bit 3, 6 – WGM01:0: Waveform Generation Mode    - Se configura en modo normal WGM01 = 0 y WGM00 = 0
    //Bit 5:4  – COM01:0: Compare Match Output Mode   - Normal port operation, OC0 disconnected. COM01 = 0 y COM00 = 0
    //Bit 2:0  – CS02:0:  Clock Select                - External clock source on T0 pin. Clock on rising edge. CS02 = CS01 = CS00 = 1
    //
    //Supuestamente, de esta forma, se configura el timer 0 para ser incrementado por un flanco ascendente, en el pin T0.


    //Configuración del Timer/Counter Interrupt Mask Register – TIMSK
    TIMSK |= (1<<TOIE0);

    //Bit 0 – TOIE0: Timer/Counter0 Overflow Interrupt Enable             - Se configura en uno, para activar la interrupción por overflow del contador T0
    //Bit 1 – OCIE0: Timer/Counter0 Output Compare Match Interrupt Enable - Se configura en cero, no interesa interrupción por comparación.

    TIFR |= (1<<TOV0);

    //Pongo en cero el contador.
    TCNT0 = 0;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //Configuro el encoder de la rueda izquierda.

//    //Si bien no es necesario, configuro el pin T2 como entrada.
//    DDRC &= ~(1<<PC6);
//
//    //Configuración del Timer/Counter Control register
//    //FOC2 WGM20 COM21 COM20 WGM21 CS22 CS21 CS20
//
//    TCCR2 |=  ((1<<CS22) | (1<<CS21) | (1<<CS20));
//
//    //Asynchronous Operation of the Timer/Counter
//    //AS2 TCN2UB OCR2UB TCR2UB
//    ASSR |= (1<<AS2);
//
//    //Timer/Counter Interrupt Mask Register
//    TIMSK |= (1<<TOIE2);
//
//    //Timer/Counter Interrupt Flag Register
//    TIFR |= (1<<TOV2);
//
//    //Pongo en cero el contador.
//    TCNT2 = 0;


    //Configuro el encoder usando el pin como entrada
    DDRC    &= ~(1<<PC6);//Configuro como entrada
    PORTC   &= ~(1<<PC6);//Desactivo el pull up




}




