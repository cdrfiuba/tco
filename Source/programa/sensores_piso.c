#include <avr/io.h>
#include <avr/interrupt.h>
#include "sensores_piso.h"


/*los tres sensores del piso estan conectados a la misma interrupcion externa INT2
y a su vez a PA0=izq PA1=der y PA2=centro
La idea con este codigo es primero inicializar las interrupciones por flanco ascendente (usando algun tipo de debouncer  para evitar efecto rebote)
y poder identificar que interrupción fue activada para luego poder usarla en el codigo del robot.
*/


void inicializar_sensores_piso(void)
{

//enciendo los Leds de los CNY70

DDRC |= (1<<1);
PORTC |= (1<<1);

//GIMSK  |= (1<<INT2);

//configuro el pin de interrupcion como salida para poder activarlo por soft
//DDRB |= (1<<DDB2);

//configuro el pin de interrupcion como entrada (no se si es necesario)
DDRB &= ~(1<<2);
PORTB &= ~(1<<2);

//configuramos PA0 PA1 y PA2 como entradas sin pullup

DDRA &= ~((DDA0)&(DDA1)&(DDA2));
PORTA &= ~((PORTA0)&(PORTA1)&(PORTA2));

//configuro registro MCUCSR ={JTD ISC2 – JTRF WDRF BORF EXTRF PORF }

// activamos la interrupcion INT2 por flanco ascendente ISC2=1

MCUCSR |= (1<<ISC2);

/* [1]
Finally, the INT2 Interrupt Flag should be cleared by writing a logi-
cal one to its Interrupt Flag bit (INTF2) in the GIFR Register before the interrupt is re-enabled.
*/

//configuramos General Interrupt Control Register – GICR ={INT1 INT0 INT2 – – – IVSEL IVCE}
//activamos la interrupcion INT2=1

GICR |= (1<<INT2);




}


