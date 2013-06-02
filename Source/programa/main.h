#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pwm.h"

#define USART_BAUDRATE 	9600
#define BAUD_PRESCALE 	(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)		//Primer duda existencial, el clock es de 8MHz, entonces sería 8UL?

