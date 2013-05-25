#include <avr/io.h>
#include <util/delay.h>

void main(void){
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRC = 0xFF;

	for(;;){
		
//		PORTA = 0x0;
//		PORTB = 0x0;
		PORTC = 0x0;
		_delay_ms(200);
//		PORTA = 0xFF;
//		PORTB = 0xFF;	
		PORTC = 0xFF;
		_delay_ms(200);
	}
}

