#include <avr/io.h>
#include <util/delay.h>

#define	SENSOR_IZQ_TRIG (1<<PA4)
#define SENSOR_IZQ_ECHO (1<<PB2)
  
#define	SENSOR_DER_TRIG (1<<PA3)
#define SENSOR_DER_ECHO (1<<PB2)

#define	SENSOR_CENT_TRIG (1<<PA2)
#define SENSOR_CENT_ECHO (1<<PB2)


//Configuracion de pines como salida

DDRA |= SENSOR_IZQ_TRIG;
DDRA |= SENSOR_DER_TRIG;
DDRA |= SENSOR_CENT_TRIG;

//Configuracion de pines como entrada 

DDRB& = ~SENSOR_IZQ_ECHO;
DDRB& = ~SENSOR_DER_ECHO;
DDRB& = ~SENSOR_CENT_ECHO;