/************************************************************************************************
 *												                                                *
 *	Proyecto TCO - Robot resolverdor de laberintos						                        *
 *												                                                *
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				                *
 *												                                                *
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			            *
 *												                                                *
 *	Archivo:	    sensores_pared.c							                                *
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	        *
 *			        sensores HC-SR04, para la medición de distancia a las paredes.		        *
 *												                                                *
 *	Última modificación: 10/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "sensores_pared.h"

extern volatile uint8_t status_flag;

inline void 	        apagar_timer(void) 	    {TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));}
//Con este andaba, lo cambio para ver de tener mas alcance
//inline void	            encender_timer(void)	{TCCR0 |= ((0<<CS02)|(1<<CS01)|(1<<CS00));}
inline void	            encender_timer(void)	{TCCR0 |= ((1<<CS02)|(0<<CS01)|(0<<CS00));}

void inicializar_timer(void){

	apagar_timer();

	//configuro TIMER para funcionamiento normal, contando hacia arriba, con prescaler de 256
	TCCR0 &= ~((1<<WGM01)|(1<<WGM00));	// Modo 0
 	TIMSK |= (1<<TOIE0);
}

void inicializar_puertos_sensores_pared(void){

	//Configuro los puertos de TRIGGER como salida.
	DDRA |= SENSOR_PARED_DER;
	DDRA |= SENSOR_PARED_CEN;
	DDRA |= SENSOR_PARED_IZQ;

	//Configuro el puerto de ECHO como entrada.
	DDRB &= ~SENSOR_PARED_ECHO;
	PORTB |= SENSOR_PARED_ECHO;

	//Configuro los puertos encendido como salida.
	DDRA |= (1<<PA0);

}


uint8_t prueba_rapida_sensor_pared(uint8_t sensor){

    //pongo en 1 el trigger
    PORTA |= sensor;

    //Espero 10 us
    _delay_us(15);

    //pongo en 0 el trigger
    PORTA &= ~sensor;

    //Espero a que el echo sea 1
    while((PINB & SENSOR_PARED_ECHO) != SENSOR_PARED_ECHO);

    TCNT0 = 0;
    encender_timer();

    status_flag = 0;

    //Espero a que el echo sea 0
    while( ((PINB & SENSOR_PARED_ECHO) == SENSOR_PARED_ECHO) && (status_flag == 0) );

    apagar_timer();

    //Apago led indicador de medición en curso
    PORTC &= ~(1<<PC0);

    if (status_flag == 1)
        return 0xFF;

    else if(TCNT0 < 0x02)
        return 0x02;

    else
        return TCNT0;


}
