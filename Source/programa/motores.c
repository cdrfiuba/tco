/************************************************************************************************
 *												*
 *	Proyecto TCO - Robot resolverdor de laberintos						*
 *												*
 *	Laboratorio de microcomputadores 66.09 - Club de robótica 2013				*
 *												*
 *	Integrantes: 	Ignacio Carballeda, Sebastian Cerone y Gisela Farace			*
 *												*
 *	Archivo:	motores.h								*
 *	Descripción: 	El presente documento tiene las definiciones para el manejo de los 	*
 *			motores.								*
 *												*
 *	Última modificación: 02/06/2013								*
 *												*
 ***********************************************************************************************/

#include "motores.h"

extern unsigned long cuenta_motor_derecha, cuenta_encoder_derecha, cuenta_motor_izquierda, cuenta_encoder_izquierda;
extern unsigned long cuenta_motor_celda; //harcodear cuenta_motor_X para obtener numero que de con medida de avance necesaria

//////////////////////////////////////////////////////////////////////////////////////////////////

void inicializar_puertos_motores(void){

	//Configuro pines como salida
	DDRB |= MOTOR_DER_BRAKE;
	DDRB |= MOTOR_IZQ_BRAKE;

	DDRD |= MOTOR_DER_DIRECTION;
	DDRD |= MOTOR_IZQ_DIRECTION;
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_avanzar(unsigned char velocidad_izquierda, unsigned char velocidad_derecha){

	//Avance sentido 1: PWM H - Direction H - Brake L

	PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	variar_PWM(velocidad_izquierda, velocidad_derecha);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_retroceder(unsigned char velocidad_izquierda, unsigned char velocidad_derecha){

	//Avance sensito 2: PWM H - Direction L - Brake L

	PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	variar_PWM(velocidad_izquierda, velocidad_derecha);
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_detener(void){

	//Freno: poner brake en alto
	PORTB |= MOTOR_DER_BRAKE;	//Pongo en alto el pin BRAKE del motor 1
	PORTB |= MOTOR_IZQ_BRAKE;	//Pongo en alto el pin BRAKE del motor 2
}


//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_rotar_derecha(unsigned char grados){

	//hacer cuenta para convertir grados en cantidad de eventos encoder

	//El motor derecho retrocede.
	PORTD &= ~MOTOR_DER_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	//El motor izquierdo avanza
	PORTD |= MOTOR_IZQ_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	while(cuenta_motor_derecha != grados)
		cuenta_motor_derecha 	= cuenta_encoder_derecha   * 256 + TCNT0;

}



//////////////////////////////////////////////////////////////////////////////////////////////////

void motores_rotar_izquierda(unsigned char grados){

	//hacer cuenta para convertir grados en cantidad de eventos encoder

	//El motor derecho avanza.
	PORTD |= MOTOR_DER_DIRECTION; 	//Pongo en alto el pin DIRECTION del motor 1
	PORTB &= ~MOTOR_DER_BRAKE;	//Pongo en bajo el pin BRAKE del motor 1

	//El motor izquierdo retrocede
	PORTD &= ~MOTOR_IZQ_DIRECTION; 	//Pongo en bajo el pin DIRECTION del motor 2
	PORTB &= ~MOTOR_IZQ_BRAKE;	//Pongo en bajo el pin BRAKE del motor 2

	while(cuenta_motor_izquierda != grados)
		cuenta_motor_izquierda 	= cuenta_encoder_izquierda   * 256 + TCNT0;


}


//////////////////////////////////////////////////////////////////////////////////////////////////

 void avanzar_celda()
 {
    /*Idea del codigo: Avanzar, cuando se detecta que el robot esta en 1/10 parte del recorrido se
    procede a una comparacion de manera de saber cual fue la rueda que alcanzo antes el objetivo.
    Si la ruda izquierda llego antes, entonces se aumenta la velocidad de la derecha (segun la diferencia
    y teniendo en cuenta un factor de proporcion) y si la rueda derecha llego antes se aumenta la velocidad de la izquierda.
    una vez pasado este 1/10 de trayecto la variable fraccion aumenta a 2/10 de trayecto y
    el robot continua avanzando hasta ese 2/10 , una vez alcanzado se procede a otra comparacion y correcion
    de velocidad, este proceso se repite 10 veces hasta alcanzar la distancia requerida.
    */
    int precision=10; //mientras mas alto sea este valor mas veces se va a comparar y a corregir el pwm en un trayecto
    unsigned long fraccion=cuenta_motor_celda/precision;  //estas definiciones van arriba...despues moverlas
    int velocidad_izq=127,velocidad_der=127; //empiezo con una velocidad intermedia
    int diferencia;
    int proporcion; //variable a harcodear
    //reseteo cuentas, para arrancar desde cero.
    cuenta_motor_derecha=0;
    cuenta_encoder_derecha=0;
    TCNT0=0x00;

    while(fraccion<cuenta_motor_celda) //mientras no se haya alcanzado el objetivo
    {
    //giro ruedas con cierto pwm
    motores_avanzar(velocidad_izq,velocidad_der); //las velocidades son directamente los puntos de comparacion para PWM

    if((cuenta_motor_izquierda || cuenta_motor_derecha)>=(fraccion)) //cuando alguno de los dos motores llegue a cuenta/fraccion de lo que se debe mover para recorrer una celda
        {
        if(cuenta_motor_izquierda > cuenta_motor_derecha) //si la rueda de la izquierda llego antes que la derecha
            {
            diferencia=cuenta_motor_izquierda-cuenta_motor_derecha;
            velocidad_izq=velocidad_izq+(diferencia*proporcion);
            }
        else if(cuenta_motor_izquierda < cuenta_motor_derecha)
            {
            diferencia=cuenta_motor_derecha-cuenta_motor_izquierda;
            velocidad_der=velocidad_der+(diferencia*proporcion)
            }

        }
        fraccion=fraccion+fraccion; //esto se va a repetir 10 veces
    }


}

//////////////////////////////////////////////////////////////////////////////////////////////////
