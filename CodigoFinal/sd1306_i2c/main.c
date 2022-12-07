/*
 * Copyright (C) 2016 Bas Stottelaar <basstottelaar@gmail.com>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 *
 * @file
 * @brief       Test application for the U8g2 package.
 *
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */
#ifndef INDEX_DRIVER_HW_I2C
#error "INDEX_DRIVER_HW_I2C not defined"
#endif

#ifndef TEST_ADDR
#error "TEST_ADDR not defined"
#endif

#ifndef SETUP_DISPLAY
#error "SETUP_DISPLAY not defined"
#endif

#ifndef TEST_PIN_RESET
#error "TEST_PIN_RESET not defined"
#endif

#include <stdio.h>

#include "periph/gpio.h"
#include "periph/i2c.h"

#include "timex.h"
#include "ztimer.h"

#include "u8g2.h"
#include "u8x8_riotos.h"




#include "periph/gpio.h"
#include "periph/i2c.h"
#include "periph/adc.h"

#include "timex.h"
#include "ztimer.h"

#include "u8g2.h"
#include "u8x8_riotos.h"


#include "perifericos/carasPantalla.c"


//sensores digitales
#define movimiento GPIO4
//Indicadores digitales
#define LED0_PIN GPIO25

#define RES             ADC_RES_10BIT
#define DELAY_MS        100000U



#define gpioMovimiento GPIO13

const int gpioTemp =10;
const int gpioHumedad =11;
const int gpioMovimientoInt=1;

bool movst=false;
bool onoff=true;




int main(void)
{
     int emocion=0;
    initSensorLuz();
  //  escribirPantalla(0,readSensorLuz());
    init_adc(gpioTemp);
    init_adc(gpioHumedad);
    gpio_init(gpioMovimiento, GPIO_IN);
    pantallaInit(gpioTemp);


    while (1) {
      movst=gpio_read(gpioMovimiento);
      onoff=cronometroMovimiento(movst);


    escribirPantalla(emocion,onoff);
      if(onoff){
  

    emocion=determinarEmocion(readSensorLuz(),read_adc(gpioTemp),read_adc(gpioHumedad));

    ztimer_sleep(ZTIMER_USEC, US_PER_SEC);
      }

    }

    return 0;
}


