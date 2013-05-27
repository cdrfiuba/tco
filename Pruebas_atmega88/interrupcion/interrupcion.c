#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "board.h"

int main(void){
	DDRC = 0xFF; //defino como salidas
	DDRD = 0b10010000; //salidas pD4 y pD7
	PORTD = 0xFF;
	int delay=1000;
	EICRA=0x01;
	EIMSK=0x01;	
 	// Se habilita la INT0
 	sei(); // Enable Interrupts

	while(1){
                PORTC = 0xF7;   //enciendo led en PC3
                _delay_ms(delay);
                PORTC = 0b11111011; //apago led, enciendo el otro en PC2
		_delay_ms(delay);
		PORTC = 0xFF;
		PORTD = 0x7F;
		_delay_ms(delay);
		PORTD = 0xEF;
		_delay_ms(delay);
		PORTD = 0xFF;
                }
	}

ISR(INT0_vect){
PORTC = 0xF7;   //enciendo led en PC3
_delay_ms(40);
PORTC = 0b11111011; //apago led, enciendo el otro en PC2
_delay_ms(40);
PORTC= 0xFF;
}
