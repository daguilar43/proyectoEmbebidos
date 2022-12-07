#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "periph_conf.h"
#include "periph/gpio.h"
#include "periph/i2c.h"
#include "shell.h"

#include <xtimer.h>

#ifndef I2C_ACK
#define I2C_ACK         (0)
#endif

uint8_t data;




int initSensorLuz(void){
i2c_acquire(0);
if(i2c_write_reg(0, 0x39,0x80,3,0)==0){
puts("0x39 0x80 3 0 existoso");
}
if(i2c_write_reg(0, 0x39,0x8F,2,0)==0){
puts("0x39 0x8F 2 0 exitoso");
}
if(i2c_read_reg(0, 0x39,0x94,&data,0)==0 ){

    puts("Read Operation Succesful");
}
printf("Valor incial %02x",data);
i2c_release(0);

return 1;
}

int readSensorLuz(void){
i2c_acquire(0);
if(i2c_read_reg(0, 0x39,0x94,&data,0)==0 ){

    puts("Read Operation Succesful");
}
printf("%02x",data);
i2c_release(0);
return data;
}