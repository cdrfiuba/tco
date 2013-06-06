

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


unsigned long cuenta_encoder_derecha, cuenta_encoder_izquierda;

void inicializar_encoders(void)
{

//Configurando timer0: Registro – TCCR0 = {FOC0 WGM00 COM01 COM00 WGM01 CS02 CS01 CS00}
//El registro de cuentas se lleva en el registro TCNT0

//Selecciono fuente para clock T0 en flanco ascendente. (conectado a motor_encoder_1_A)
//CS02=1 CS01=1 CS00=1

TCCR0 |= ((1<<CS02) | (1<<CS01) | (1<<CS00));

//Configurando Modo de operacion Normal con TOP en 0xFF (cuenta hasta 256 y resetea)
//WGM01 (CTC0)=0  WGM00 (PWM0)=0
//Deshabilito comparador externo (OC0 desconectado)
//COM01=0 COM00=0

TCCR0 &= ~((1<<WGM01) & (1<<WGM00) & (1<<COM01) & (1<<COM00));

//Configuramos Registro Mascara de Interrupciones
//TIMSK={OCIE2 TOIE2 TICIE1 OCIE1A OCIE1B TOIE1 OCIE0 TOIE0}
//habilitamos la interrupcion por desbordamiento de registro
//TOIE0=1

TIMSK |= (1<<TOIE0);

//Configuramos el Registro Flags de interrupciones
//TIFR={CF2 TOV2 ICF1 OCF1A OCF1B TOV1 OCF0 TOV0}
//Activamos el Flag por overflow TOV0=1

TIFR |= (1<<TOV0);

//----------------------------------------------------------------

//Configuramos timer2 para el encoder B (idem Configuracion timer0)
//(conectado a motor_encoder_2_A)
//TCCR2 = {FOC2 WGM20 COM21 COM20 WGM21 CS22 CS21 CS20 }

TCCR2 |= ((1<<CS22) | (1<<CS21) | (1<<CS20));

TCCR2 &= ~((1<<WGM20) & (1<<WGM21) & (1<<COM21) & (1<<COM20));

//el registro de cuentas es TCNT2
//configuro TIMSK Timer/Counter2 Overflow Interrupt Enable

TIMSK |= (1<<TOIE2);

//Configuro flag por overflow del timer2
//TOV2: Timer/Counter2 Overflow Flag

TIFR |= (1<<TOV2);

}

//¿Las Interrupciones Deberian ir en el Main?
//Las variables que uso a continuacion deberian ser globales y estar definidas en main
//unsigned char cuenta_encoder_1;
//unsigned char cuenta_encoder_2;

ISR (TIMER0_OVF_vect)   //interrupcion por overflow del timer 0
{
cuenta_encoder_derecha++;
}


ISR (TIMER2_OVF_vect)   //interrupcion por overflow del timer 2
{
cuenta_encoder_izquierda++;
}




