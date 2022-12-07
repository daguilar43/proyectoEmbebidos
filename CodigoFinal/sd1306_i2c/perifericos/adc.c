#include <stdio.h>

#include "ztimer.h"
#include "periph/adc.h"

#define RES             ADC_RES_10BIT

int sample=0;
int segundos=0;
int resetCron=0;
bool activo=false;
int t_max=30;

int init_adc(int numSensor) ///Numero del sensor en el archivo periph.conf de la board utilizada
{
        if(adc_init(ADC_LINE(numSensor)) < 0){
        return 0;              /// Retorna 0 si la inicializacion falla    
    }
    else {
    return 1;
    }
}

int read_adc(int numSensor){ ///Numero del sensor en el archivo periph.conf de la board utilizada

            sample = adc_sample(ADC_LINE(numSensor), RES);
        if (sample < 0) {
    //        printf("ADC_LINE(%u): selected resolution not applicable\n", 1);
        } else {
    //        printf("ADC_LINE(%u): %i\n", 1, sample);
        }

        return sample;

}

bool cronometroMovimiento(bool movst){

    segundos=ztimer_now(ZTIMER_USEC)/1000000;

        if(movst==1){
            resetCron=ztimer_now(ZTIMER_USEC)/1000000;
            activo=true;
        }
        if(segundos-resetCron>=t_max){
            activo=false;
        }
            return activo;
}



