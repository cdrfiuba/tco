#include <avr/io.h>
#include <avr/interrupt.h>

//prototipos de funcion.

#define SENSOR_PISO_IZQ
#define SENSOR_PISO_DER
#define SENSOR_PISO_CEN

void    inicializar_sensores_piso   (void);
void    medir_piso  (void);
void    estado_sensores_piso    (void);
