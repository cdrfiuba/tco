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



extern unsigned char flag_interrupcion;

inline void apagar_timer(void) 	{TCCR0 &= ~((1<<CS02)|(1<<CS01)|(1<<CS00));}
inline void	encender_timer(void)	{TCCR0 |= ((0<<CS02)|(1<<CS01)|(1<<CS00));}
inline void	inicializar_timer(void)	{TIMSK |= (1<<TOIE0);}


void inicializar_puertos_sensores_pared(void){

	//Led indicador de medición en curso
	DDRC |= (1<<PC0);

	//configuro TIMER para funcionamiento normal, contando hacia arriba, con prescaler de 256
	TCCR0 &= ~((1<<WGM01)|(1<<WGM00));	// Modo 0

	//Configuro los puertos de TRIGGER como salida.
	DDRA |= SENSOR_PARED_DER_TRIG;
	DDRA |= SENSOR_PARED_CEN_TRIG;
	DDRA |= SENSOR_PARED_IZQ_TRIG;

	//Configuro los puertos de ECHO como entradas.
	DDRB &= ~SENSOR_PARED_DER_ECHO;
	DDRB &= ~SENSOR_PARED_IZQ_ECHO;
	PORTB |= SENSOR_PARED_DER_ECHO;
	PORTB |= SENSOR_PARED_IZQ_ECHO;

}


unsigned char prueba_rapida_sensor_pared(void){

	//Enciendo led indicador de medición en curso
	PORTC |= (1<<PC0);

	//pongo en 1 el trigger
	PORTA |= SENSOR_PARED_DER_TRIG;

	//Espero 15 us	
	_delay_us(15);

	//pongo en 0 el trigger
	PORTA &= ~SENSOR_PARED_DER_TRIG;
	
	//Espero a que el echo sea 1
	while((PINB & SENSOR_PARED_DER_ECHO) != SENSOR_PARED_DER_ECHO);

	TCNT0 = 0;
	encender_timer();
	
	//Espero a que el echo sea 0
	while( (PINB & SENSOR_PARED_DER_ECHO) == SENSOR_PARED_DER_ECHO){
		
		if( (TIFR & (1<<TOV0)) == (1<<TOV0) ){
		
			apagar_timer();

			//Apago led indicador de medición en curso
			PORTC &= ~(1<<PC0);
			
			return 0xFF;
		}
	}

	apagar_timer();

	//Apago led indicador de medición en curso
	PORTC &= ~(1<<PC0);

	return TCNT0;
}
		




//////////////////////////////////////////////////////////////////////////////////////////////////
/*

unsigned int inicializar_maquina_medicion_distancia_pared(void){

	sensor = SENSOR_PARED_DERECHA;

	estado_maquina_medicion_distancia_pared = INICIALIZAR_MEDICION_DISTANCIA_PARED;
	tick_maquina_medicion_distancia_pared	= TICK_INICIALIZAR_MEDICION_DISTANCIA_PARED;

}


//////////////////////////////////////////////////////////////////////////////////////////////////


// El siguiente código es una maquina de estados para manejar los sensores de medición de distancia.
// Para poder usarla se tiene que usar un variable contador del tipo unsigned long global "tick_maquina_medicion_distancia_pared"
// Esta variable debe ser decrementada en la interrupción de timer cada 1 ms.
// Tambien se debe declarar una variable global del tipo unsigned char "estado_maquina_medicion_distancia_pared" para llevar el 
// orden de la maquina.
inline 

unsigned int medir_distancia_pared(void){

	if(tick_maquina_medicion_distancia_pared == 0){

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

					estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
					tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;	

				}
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA |= SENSOR_PARED_CEN_TRIG;	

					estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
					tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;	

				} 
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA |= SENSOR_PARED_IZQ_TRIG;	

					estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
					tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;	

				}

				//Si llego a este punto, es que el sensor ingresado no es válido, reinicio la maquina de estados
				else
					inicializar_maquina_medicion_distancia_pared();
			break;


			case ESPERAR_UNO:

				//Espero a tener un '1' en el pin ECHO

				if(sensor == SENSOR_PARED_DERECHA){
				
					PORTA &= ~SENSOR_PARED_DER_TRIG;	//Pongo en cero el trigger

					if((PORTA & SENSOR_PARED_DER_ECHO) == SENSOR_PARED_DER_ECHO){

						//poner contador en cero
						
						estado_maquina_medicion_distancia_pared = ESPERAR_CERO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_CERO;

					}
					else{
						estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;

					}
				}
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA &= ~SENSOR_PARED_CEN_TRIG;	//Pongo en cero el trigger

					if((PORTA & SENSOR_PARED_CEN_ECHO) == SENSOR_PARED_CEN_ECHO){

						//poner contador en cero
						
						estado_maquina_medicion_distancia_pared = ESPERAR_CERO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_CERO;

					}
					else{
						estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;

					}

				} 
				
				else if(sensor == SENSOR_PARED_IZQUIERDA){

					PORTA &= ~SENSOR_PARED_IZQ_TRIG;	//Pongo en cero el trigger

					if((PORTA & SENSOR_PARED_IZQ_ECHO) == SENSOR_PARED_IZQ_ECHO){

						//pongo contador en cero
						
						estado_maquina_medicion_distancia_pared = ESPERAR_CERO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_CERO;

					}
					else{
						estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;

					}

				}

				//Si llego a este punto, es que el sensor ingresado no es válido, reinicio la maquina de estados
				else
					inicializar_maquina_medicion_distancia_pared();

			break;


			case ESPERAR_CERO:

				//Espero a tener un '0' en el pin ECHO

				if(sensor == SENSOR_PARED_DERECHA){
				
					if((PORTA & SENSOR_PARED_DER_ECHO) == ~SENSOR_PARED_DER_ECHO){

						
						estado_maquina_medicion_distancia_pared = ESPERAR_CERO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_CERO;

					}
					else{
						estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;

					}
				}
				
				else if(sensor == SENSOR_PARED_CENTRO){

					PORTA &= ~SENSOR_PARED_CEN_TRIG;	//Pongo en cero el trigger

					if((PORTA & SENSOR_PARED_CEN_ECHO) == SENSOR_PARED_CEN_ECHO){

						//poner contador en cero
						
						estado_maquina_medicion_distancia_pared = ESPERAR_CERO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_CERO;

					}
					else{
						estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;

					}

				} 
				
				else if(sensor == SENSOR_PARED_IZQUIERDA){

					PORTA &= ~SENSOR_PARED_IZQ_TRIG;	//Pongo en cero el trigger

					if((PORTA & SENSOR_PARED_IZQ_ECHO) == SENSOR_PARED_IZQ_ECHO){

						//pongo contador en cero
						
						estado_maquina_medicion_distancia_pared = ESPERAR_CERO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_CERO;

					}
					else{
						estado_maquina_medicion_distancia_pared = ESPERAR_UNO;
						tick_maquina_medicion_distancia_pared	= TICK_MEDICION_DISTANCIA_PARED_ESPERAR_UNO;

					}

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
*/

//////////////////////////////////////////////////////////////////////////////////////////////////

