
#include <avr/io.h>
#include <util/delay.h>

void inicializar_puertos(void);
void inicializar_PWM(void);
void variar_velocidad(unsigned char, unsigned char);
void motores_avanzar(void);

int main(void)
{

	inicializar_puertos();

	inicializar_PWM();

	variar_velocidad(0, 0);

	motores_avanzar();	

    	DDRD |= (1<<2);

       	// Ciclo
    	while(1)
    	{
        	_delay_ms(10);
		PORTD |= (1<<2);
        	_delay_ms(10);
		PORTD &= ~(1<<2);
		
    	}
    
	return 0;
}

void inicializar_puertos(void){

	//Configuro pines como salida
	DDRB |= (1<<PB3);	//pin BRAKE del motor 1
	DDRB |= (1<<PB4);	//pin BRAKE del motor 1

	DDRD |= (1<<PD6); 	//pin DIRECTION del motor 1
	DDRD |= (1<<PD7); 	//pin DIRECTION del motor 1

	//configuro pines como entrada
	DDRB &= ~(1<<PB0);	//pin ENCODER motor 1
	DDRD &= ~(1<<PD2);	//pin ENCODER motor 1

}


void inicializar_PWM(void){

	TCCR1A = ((1 << COM1A1)|(1 << COM1A0)|(1 << COM1B1)|(1 << COM1B0)|(0 << WGM11)|(1 << WGM10)); 	//COM1A1=1, COM1A0=1, COM1B1=1, COM1B0=1, WGM11=0, WGM10=1
	//Configuración del PWM como fast PWM de 8 bits

    	TCCR1B = ((0 << WGM13)|(1 << WGM12)); 								//Timer Apagado WGM13=0, WGM12=1, CS12=0, CS11=0, CS10=0 
    
	// Configuración de dirección de puertos I/O
	// DDRA=0x00; // Puerto A como entrada
    	//DDRC=0xFF; // Puerto C como salida
    	//DDRD=0xFF;// Pin 3 y 4 del puerto B como salida
	DDRD |= (1<<4)|(1<<5); 
	//    PORTA=0xFF; // Habilitación de pull-ups del puerto A
	//    PORTC=0x00; // Inicialización de salida del puerto C
	//OCR1AH = 0;//velocidad_motor_izq;
    	//OCR1BH = 0;//velocidad_motor_der;


    	// Configuración del Timer 1:
    	TCCR1B |= ((0<<CS12)|(0<<CS11)|(1<<CS10)); //Enciendo el Timer sin prescaler (001)

}

void variar_velocidad(unsigned char velocidad_motor_izq, unsigned char velocidad_motor_der){

	OCR1AL = velocidad_motor_izq;
    	OCR1BL = velocidad_motor_der;
    	//TCNT1 = 0;

}

void motores_avanzar(void){

	PORTD |= (1<<PD7); 	//Pongo en alto el pin DIRECTION del motor 1
	PORTB &= ~(1<<PB3);	//Pongo en bajo el pin BRAKE del motor 1

	PORTD |= (1<<PD6); 	//Pongo en alto el pin DIRECTION del motor 2
	PORTB &= ~(1<<PB4);	//Pongo en bajo el pin BRAKE del motor 2
	
}

