#include <avr/io.h>
#include <avr/interrupt.h>


/*los tres sensores del piso estan conectados a la misma interrupcion externa INT2
y a su vez a PA0=izq PA1=der y PA2=centro
La idea con este codigo es primero inicializar las interrupciones por flanco ascendente (usando algun tipo de debouncer  para evitar efecto rebote)
y poder identificar que interrupción fue activada para luego poder usarla en el codigo del robot.
*/

//funcion "cabeza" para detectar celda llegada

void estado_sensores_piso(){

//configuramos PA0 PA1 y PA2 como entradas sin pullup

DDRA &= ~((DDA0)&(DDA1)&(DDA2));
PORTA &= ~((PORTA0)&(PORTA1)&(PORTA2));

if(PINA0 & PINA1 & PINA2){ return 1;}
else return 0;
}



void inicializar_sensores_piso(void)
{

//por defecto el pin PB2 esta en triestado sin pullup , lo configuramos como entrada sin pullup

//DDRB &= ~(1<<DDB2);
//PORTB &= ~(1<<PORTB2);

//configuramos PA0 PA1 y PA2 como entradas sin pullup

DDRA &= ~((DDA0)&(DDA1)&(DDA2));
PORTA &= ~((PORTA0)&(PORTA1)&(PORTA2));


}

void medir_piso(void){

//configuro registro MCUCSR ={JTD ISC2 – JTRF WDRF BORF EXTRF PORF }

// activamos la interrupcion INT2 por flanco ascendente ISC2=1

MCUCSR |= (1<<ISC2);

/* [1]
Finally, the INT2 Interrupt Flag should be cleared by writing a logi-
cal one to its Interrupt Flag bit (INTF2) in the GIFR Register before the interrupt is re-enabled.
*/

//configuramos General Interrupt Control Register – GICR ={INT1 INT0 INT2 – – – IVSEL IVCE}
//activamos la interrupcion INT2=1

GICR |=(1<<INT2);

}


ISR (INT2_vect){
//Averiguamos cual de los tres fue el sensor que detecto un flanco ascendente
//para ello leemos el PINA={PINA7 PINA6 PINA5 PINA4 PINA3 PINA2 PINA1 PINA0}

if (PINA & (1<<PINA0)){
    // fue por el sensor izquierdo (tomar medidas en caso seguidor lineas)
    SENSOR_PISO_IZQ=1;
    }
else if(PINA & (1<<PINA1)){
        //fue por el sensor derecho (tomar medidas en caso seguidor lineas)
        SENSOR_PISO_DER=1;
        }
else if(PINA & (1<<PINA2)){
        //fue por el sensor del centro (tomar medidas en caso seguidor lineas)
        SENSOR_PISO_CEN=1;
        }

//falta el sistema anti-rebote que quizas podria ser un  _delay_ms() aca mismo

//Finalmente hacemos un clear al registro GIFR de interrupcion como se pide en hoja de datos [1].
GIFR &= ~(1<<INTF2);

}


