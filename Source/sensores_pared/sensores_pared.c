/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	sensores_pared.c							*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	*
 *			sensores HC-SR04, para la medición de distancia a las paredes.		*
 *												*
 *	Última modificación: 03/06/2013								*
 *												*
 ***********************************************************************************************/

#include "sensores_pared.h"

void inicializar_puertos_sensores_pared(void)
{
	//Configuro los puertos de TRIGGER como salida.
	DDRA |= SENSOR_PARED_DER_TRIG;
	DDRA |= SENSOR_PARED_CEN_TRIG;
	DDRA |= SENSOR_PARED_IZQ_TRIG;

	//Configuro los puertos de ECHO como entradas.
	DDRB &= ~SENSOR_PARED_DER_ECHO;
	DDRB &= ~SENSOR_PARED_CEN_ECHO;
	DDRB &= ~SENSOR_PARED_IZQ_ECHO;	
}


//////////////////////////////////////////////////////////////////////////////////////////////////


unsigned int inicializar_maquina_medicion_distancia_pared(void)
{

	estado_maquina_medicion_distancia_pared = INICIALIZAR_MEDICION_DISTANCIA_PARED;
	tick_maquina_medicion_distancia_pared	= TICK_INICIALIZAR_MEDICION_DISTANCIA_PARED;

}


//////////////////////////////////////////////////////////////////////////////////////////////////


/* El siguiente código es una maquina de estados para manejar los sensores de medición de distancia.
 * Para poder usarla se tiene que usar un variable contador del tipo unsigned long global "tick_maquina_medicion_distancia_pared"
 * Esta variable debe ser decrementada en la interrupción de timer cada 1 ms.
 * Tambien se debe declarar una variable global del tipo unsigned char "estado_maquina_medicion_distancia_pared" para llevar el 
 * orden de la maquina.
 *
 */

unsigned int medir_distancia_pared(unsigned char sensor)
{

	if(tick_maquina_medicion_distancia_pared == 0)
	{
		switch(estado_maquina_medicion_distancia_pared){

			//En caso de que caiga en un estado no valido, reinicio la máquina
			case MAX_ESTADOS_MEDICION_DISTANCIA_PARED:

				inicializar_maquina_medicion_distancia_pared();

			break;


			case INICIAR_MEDICION_DISTANCIA_PARED:

				//Pongo el pin en 1 y paso al siguiente estado. Como al siguiente estado voy a entrar en
				// TICK_MEDICION_DISTANCIA_PARED = 10 ms como minimo, es el tiempo suficiente para generar el tren de pulsos
					

				if(sensor == SENSOR_PARED_DERECHA){
				
					PORTA |= SENSOR_PARED_DER_TRIG;

					//Poner contador en cero	

					estado_maquina_medicion_distancia_pared = MEDICION_DISTANCIA_PARED;
					tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED;	

				}
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA |= SENSOR_PARED_CEN_TRIG;	

					//Poner contador en cero
					
					estado_maquina_medicion_distancia_pared = MEDICION_DISTANCIA_PARED;
					tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED;

				} 
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA |= SENSOR_PARED_IZQ_TRIG;	

					//Poner contador en cero

					estado_maquina_medicion_distancia_pared = MEDICION_DISTANCIA_PARED;
					tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED;

				}

				//Si llego a este punto, es que el sensor ingresado no es válido, reinicio la maquina de estados
				else
					inicializar_maquina_medicion_distancia_pared();
			break;


			case MEDICION_DISTANCIA_PARED:

				//Espero a tener la cantidad de pulsos del reloj (ms).

				if(sensor == SENSOR_PARED_DERECHA){
				
					PORTA &= ~SENSOR_PARED_DER_TRIG;	//Pongo en cero el trigger

					if((PORTA & SENSOR_PARED_IZQ_ECHO) == SENSOR_PARED_IZQ_ECHO)

				}
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA &= ~SENSOR_PARED_CEN_TRIG;	//Pongo en cero el trigger

				} 
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA &= ~SENSOR_PARED_IZQ_TRIG;	//Pongo en cero el trigger	

				}

				//Si llego a este punto, es que el sensor ingresado no es válido, reinicio la maquina de estados
				else
					inicializar_maquina_medicion_distancia_pared();

			break;


			//En caso de que caiga en un estado no valido, reinicio la máquina
			case DEFAULT:
				inicializar_maquina_medicion_distancia_pared();
			break;

		}
	}
}


//////////////////////////////////////////////////////////////////////////////////////////////////

