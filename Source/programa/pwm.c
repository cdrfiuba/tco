/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	pwm.c									*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo del PWM.	*
 *												*
 *	Última modificación: 02/06/2013								*
 *												*
 ***********************************************************************************************/

#include "pwm.h"

void inicializar_PWM(void){

	TCCR1A = ((1 << COM1A1)|(1 << COM1A0)|(1 << COM1B1)|(1 << COM1B0)|(0 << WGM11)|(1 << WGM10)); 	
	//COM1A1=1, COM1A0=1, COM1B1=1, COM1B0=1, WGM11=0, WGM10=1
	//Configuración del PWM como fast PWM de 8 bits

	TCCR1B = ((0 << WGM13)|(1 << WGM12)); 								
	//Timer Apagado WGM13=0, WGM12=1, CS12=0, CS11=0, CS10=0

	// Configuración de dirección de puertos I/O
	// DDRA=0x00; // Puerto A como entrada
    	//DDRC=0xFF; // Puerto C como salida
    	//DDRD=0xFF;// Pin 3 y 4 del puerto B como salida
	DDRD |= (1<<4)|(1<<5);
	//PORTA=0xFF; // Habilitación de pull-ups del puerto A
	//PORTC=0x00; // Inicialización de salida del puerto C
	//OCR1AH = 0;//velocidad_motor_izq;
    	//OCR1BH = 0;//velocidad_motor_der;


    	// Configuración del Timer 1:
    	TCCR1B |= ((0<<CS12)|(0<<CS11)|(1<<CS10)); //Enciendo el Timer sin prescaler (001)

}

void variar_PWM(unsigned char valor_izq, unsigned char valor_der){

	OCR1AL = valor_izq;
    	OCR1BL = valor_der;
   	//TCNT1 = 0;

}
