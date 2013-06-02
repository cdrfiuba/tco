#include <avr/io.h>
#include <util/delay.h>
#include <sensores_pared.h>


int16 sensores_pared(void){
	
	int16 dist_izq=0;
	int16 dist_der=0;
	int16 dist_cent=0;
	
	dist_izq = medir(SENSOR_IZQ_TRIG,SENSOR_IZQ_ECHO,dist_izq);
	dist_cent = medir(SENSOR_CENT_TRIG,SENSOR_CENT_ECHO,dist_cent);
	dist_der = medir(SENSOR_DER_TRIG,SENSOR_DER_ECHO,dist_der);
	
}


int16 medir(int TRIG, int ECHO, int16 distancia)
{
	output_high(trig);
	delay_us(50);
	output_low(trig);  
	//espera flanco de subida por el pin echo
	while(ECHO==0);
	//comienza a contar centimetros hasta que pin echo sea cero
	while(ECHO==1){
		distancia++;
		delay_us(58);
	}
	//demora de seguridad y retorna con el valor de centimetros contados
	delay_ms(50);
	return(distancia);
}



