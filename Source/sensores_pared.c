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
 *	Última modificación: 24/06/2013								                                *
 *												                                                *
 ***********************************************************************************************/

#include "sensores_pared.h"

extern volatile uint8_t     status_flag, sensor_active;
extern volatile uint32_t    interrupciones_timer_1;

void inicializar_puertos_sensores_pared(void){

	//Configuro los puertos de TRIGGER como salida.
	DDRA |= SENSOR_PARED_DER;
	DDRA |= SENSOR_PARED_CEN;
	DDRA |= SENSOR_PARED_IZQ;

	//Configuro el puerto de ECHO como entrada.
	DDRB &= ~SENSOR_PARED_ECHO;

	//Configuro los puertos encendido como salida.
	DDRA |= (1<<PA0);

}


uint32_t medicion_distancia_pared(uint8_t sensor){

    uint32_t    cuentas = 0, cuentas_inicial, cuentas_final;

    //Desactivo INT 2 al medir, para evitar problemas.
    GICR &= ~(1<<INT2);

    while(cuentas == 0){

        //pongo en 1 el trigger
        PORTA |= sensor;

        //Espero 10 us
        _delay_us(10);

        //pongo en 0 el trigger
        PORTA &= ~sensor;

        //Espero a que el echo sea 1
        while((PINB & SENSOR_PARED_ECHO) != SENSOR_PARED_ECHO);

        interrupciones_timer_1 = 0;
        cuentas_inicial = TCNT1;
        status_flag = 0;
        sensor_active = 1;

        //Espero a que el echo sea 0
        while( ((PINB & SENSOR_PARED_ECHO) == SENSOR_PARED_ECHO) && (status_flag == 0) );
        sensor_active = 0;

        cuentas_final = TCNT1;

        cuentas = (256 - cuentas_inicial) + 256 * interrupciones_timer_1 + cuentas_final;

    }

    //Vuelvo a activar la interrupcion INT2
    GICR |= (1<<INT2);


    if (status_flag == 1)
        return 0xFFFFFFFF;


    else
        return cuentas;
}
