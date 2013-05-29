#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    TCCR1A = ((1 << COM1A1)|(1 << COM1A0)|(1 << COM1B1)|(1 << COM1B0)|(0 << WGM11)|(1 << WGM10)); //COM1A1=1, COM1A0=1, COM1B1=1, COM1B0=1, WGM11=0, WGM10=1
    TCCR1B = ((0 << WGM13)|(1 << WGM12)); //Timer Apagado WGM13=0, WGM12=1, CS12=0, CS11=0, CS10=0 
    
    
    // Configuración de dirección de puertos I/O
//    DDRA=0x00; // Puerto A como entrada
    DDRC=0xFF; // Puerto C como salida
    DDRB=0xFF;// Pin 3 y 4 del puerto B como salida

//    PORTA=0xFF; // Habilitación de pull-ups del puerto A
//    PORTC=0x00; // Inicialización de salida del puerto C

//Hasta aca es un starup

    // Inicialización del PWM
    OCR1A = 127;
    OCR1B = 127;
    TCNT1 = 0;

    // Configuración del Timer 1:
    TCCR1B|= ((0<<CS12)|(0<<CS11)|(1<<CS10)); //Enciendo el Timer sin prescaler (001)

//Hasta aca control_velocidad

    // Ciclo
    while(1)
    {
        _delay_ms(10);
    }
    return 0;
}
