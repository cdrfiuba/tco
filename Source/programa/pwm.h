#include <avr/io.h>
#include <util/delay.h>

void inicializar_puertos_motores(void);
void inicializar_PWM(void);
void variar_velocidad(unsigned char, unsigned char);
void motores_avanzar(void);
void motor_detener(void);

