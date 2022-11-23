/*
 * Copyright (C) 2014-2015 Freie Universität Berlin
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
 * @brief       Test application for peripheral ADC drivers
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>
#include "timex.h"
#include "ztimer.h"
#include "periph/adc.h"
#include "periph/i2c.h"
#include "u8g2.h"
#include "u8x8_riotos.h"

 
#define SSD1306_I2C_ADDR    (61)
    
// Codigo tomado de controlador para arduino 

//i2c_t oled_dev;
//

//u8g2_t u8g2;

//u8x8_riotos_t user_data =
//{
  //  .device_index = 0,
    //.pin_sda = GPIO_PIN(PA, 22),
    //.pin_scl = GPIO_PIN(PA, 23)
//};
 
 //u8g2_SetUserPtr(&u8g2, &user_data);
 //u8g2_Setup_ssd1306_128x64_noname_1(&u8g2, U8G2_R0, u8x8_byte_riotos_hw_i2c, u8x8_gpio_and_delay_riotos);



#define RES             ADC_RES_10BIT
#define DELAY_MS        1000U



// Funcion de Inicializacion tomada de https://github.com/HendrikVE/RIOT/commit/82b88cb98eaeb9043f8a1635f10317d687ce3f43?diff=unified#diff-0ee4738ff24684d860334c86f75f79790b80f766b37714a86881b32c2dfb2ff2
void esp_i2c_init(i2c_t dev) {

  //  assert(dev);
  //  assert(params);

  //  dev->params = *params;

    i2c_init(0);

    //uint8_t _functionSet = 0;

    // configure bit mode
    //if (params->bit_mode == BITMODE_8_BIT) {
    //    _functionSet |= (1 << BIT_FUNCTION_SET_BITMODE);
   // }

    // configure line count
    //if (params->row_count >= 2) {
    //    _functionSet |= (1 << BIT_FUNCTION_SET_LINECOUNT);
   // }

    // configure character size
    //if (params->font_size == FONT_SIZE_5x10) {
     //   _functionSet |= (1 << BIT_FUNCTION_SET_FONTSIZE);
   // }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50 ms
   // xtimer_usleep(50 * US_PER_MS);

    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
   // _command(dev, CMD_FUNCTION_SET | _functionSet);
   // xtimer_usleep(5 * US_PER_MS);

    // second try
    //_command(dev, CMD_FUNCTION_SET | _functionSet);
    //xtimer_usleep(500);

    // third go
  //  _command(dev, CMD_FUNCTION_SET | _functionSet);

    // above three calls to _command will return -ENXIO, but subsequent calls
    // should give no error

  //**  hd44780_i2c_turn_on(dev);
   // hd44780_i2c_clear(dev);
    //hd44780_i2c_set_text_insertion_mode(dev, LEFT_TO_RIGHT);

   // return ESP_OK;
}



/* static const uint8_t logo[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xE0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xF8, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x3C,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x1E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x70, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x0E,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x0E, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF0, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x1E,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x3C, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xF0, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0xF8,
    0x30, 0x3C, 0x3F, 0xC0, 0x00, 0x0C, 0x77, 0xF0, 0x38, 0x7E, 0x3F, 0xC0,
    0x00, 0x7E, 0x73, 0xC0, 0x38, 0xE7, 0x06, 0x00, 0x00, 0xFC, 0x71, 0x00,
    0x38, 0xE3, 0x06, 0x00, 0x01, 0xF0, 0x70, 0x00, 0x38, 0xE3, 0x06, 0x00,
    0x01, 0xC0, 0x70, 0x00, 0x38, 0xE3, 0x06, 0x00, 0x03, 0x80, 0x70, 0xC0,
    0x38, 0xE3, 0x06, 0x00, 0x03, 0x80, 0x71, 0xE0, 0x38, 0xE3, 0x06, 0x00,
    0x03, 0x80, 0x70, 0xE0, 0x38, 0xE3, 0x06, 0x00, 0x03, 0x80, 0x70, 0xF0,
    0x38, 0xE3, 0x06, 0x00, 0x03, 0x80, 0x70, 0x70, 0x38, 0xE3, 0x06, 0x00,
    0x03, 0x80, 0xF0, 0x78, 0x38, 0xE3, 0x06, 0x00, 0x03, 0xC1, 0xE0, 0x3C,
    0x38, 0xE7, 0x06, 0x00, 0x01, 0xE3, 0xE0, 0x3C, 0x38, 0x7E, 0x06, 0x00,
    0x01, 0xFF, 0xC0, 0x1C, 0x30, 0x3C, 0x06, 0x00, 0x00, 0x7F, 0x80, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
}; */







int main(void)
{

ztimer_sleep(ZTIMER_MSEC, DELAY_MS);


 i2c_init(0);



///Inicializacion i2C
//esp_i2c_init(oled_dev);

//i2c_acquire(0);
///

  // int sample = 0;

    //puts("\nRIOT ADC peripheral driver test\n");
    //puts("This test will sample all available ADC lines once every 100ms with\n"
      //   "a 10-bit resolution and print the sampled results to STDIO\n\n");

    /* initialize all available ADC lines */
    /* for (unsigned i = 0; i < ADC_NUMOF; i++) { */
    /*     if (adc_init(ADC_LINE(i)) < 0) { */
    /*         printf("Initialization of ADC_LINE(%u) failed\n", i); */
    /*         return 1; */
    /*     } else { */
    /*         printf("Successfully initialized ADC_LINE(%u)\n", i); */
    /*     } */
    /* } */

    /* initialize all available ADC lines */
    //if(adc_init(ADC_LINE(7)) < 0){
      //  return 1;
    //}

   // adc_init(ADC_LINE(7));



 // i2c_init(0);
uint16_t add_Oled=61 ;//"01111000"
uint8_t  contrByte=0x80  ;// Para comandos
uint8_t  contrBytedata=0x40  ;// Para escribir datos
//uint8_t  dataByte=175;
uint8_t linea1=230;
uint8_t rutinaInicio[]={contrByte, 0xA8,  0x3F,  0xD3, 0x00,  0x40, 0xA0,  0xC0,  0xDA, 
 02, 0x81, 0xA4, 0xA6,  0xD5, 0x80, 0x8D, 0x14,  0xAF,0xA5, contrBytedata, linea1};
//uint8_t todoON=0xA5;
// first, acquire the shared bus again
   
/* i2c_acquire(0);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP);
i2c_write_byte(0, add_Oled, 0xA8, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0x3F, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xD3, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0x00, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0x40, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xA0, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xC0, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xDA, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 02, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0x81, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xA4, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xA6, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xD5, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0x80, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0x8D, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0x14, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrByte, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, 0xAF, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, contrBytedata, I2C_NOSTOP,I2C_NOSTART);
i2c_write_byte(0, add_Oled, linea1 , I2C_NOSTART); */
i2c_acquire(0);
i2c_write_bytes(0,add_Oled,rutinaInicio ,sizeof(rutinaInicio) ,0);
//i2c_write_byte(0, add_Oled,todoON, 0);
i2c_release(0);

  //  while (1) {
        /* for (unsigned i = 0; i < ADC_NUMOF; i++) { */
        /*     sample = adc_sample(ADC_LINE(i), RES); */
        /*     if (sample < 0) { */
        /*         printf("ADC_LINE(%u): selected resolution not applicable\n", i); */
        /*     } else { */
        /*         printf("ADC_L INE(%u): %i\n", i, sample); */
        /*     } */
        /* } */

       // sample = adc_sample(ADC_LINE(8), RES);
     //   if (sample < 0) {
         //   printf("ADC_LINE(%u): selected resolution not applicable\n", 1);
        //} else {
  //          printf("ADC_LINE(%u): %i\n", 8, sample);
        //}



//i2c_acquire(0);
// write the 16-bit register address to the device and prevent STOP condition
//i2c_write_byte(0, add_Oled, contrBytedata, I2C_NOSTOP);
//1i2c_write_byte(0, add_Oled, linea1 , 0);
// and write the data after a REPEATED START
//i2c_write_bytes(dev, add_Oled, linea1, 2, 0);
// and finally free the bus again
//i2c_release(0); 

    //    ztimer_sleep(ZTIMER_MSEC, DELAY_MS);
    //}



/* i2c_init(0;


 uint32_t screen = 0;
    u8g2_t u8g2;


     //   u8g2_SetupBuffer_Utf8(&u8g2, U8G2_R0);

       //     u8g2_SetupBuffer_SDL_128x64_4(&u8g2, U8G2_R0);

    

u8x8_riotos_t user_data = {
    .device_index = 0,
    .pin_cs = GPIO_UNDEF,
    .pin_dc = GPIO_UNDEF,
    .pin_reset = GPIO_UNDEF,
};

u8g2_SetUserPtr(&u8g2, &user_data);
u8g2_SetI2CAddress(&u8g2, SSD1306_I2C_ADDR);

u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0,
                                       u8x8_byte_hw_i2c_riotos,
                                       u8x8_gpio_and_delay_riotos);



u8g2_InitDisplay(&u8g2);
u8g2_SetPowerSave(&u8g2, 0);





  while (1) {
        u8g2_FirstPage(&u8g2);

        do {
            u8g2_SetDrawColor(&u8g2, 1);
            u8g2_SetFont(&u8g2, u8g2_font_helvB12_tf);

            switch (screen) {
                case 0:
                    u8g2_DrawStr(&u8g2, 12, 22, "THIS");
                    break;
                case 1:
                    u8g2_DrawStr(&u8g2, 24, 22, "IS");
                    break;
                case 2:
                    u8g2_DrawBitmap(&u8g2, 0, 0, 8, 32, logo);
                    break;
            }
        } while (u8g2_NextPage(&u8g2));



        / show screen in next iteration /
        screen = (screen + 1) % 3;


 //   }
 */

         /* sleep a little */
        ztimer_sleep(ZTIMER_USEC, US_PER_SEC);
    return 0;
}






