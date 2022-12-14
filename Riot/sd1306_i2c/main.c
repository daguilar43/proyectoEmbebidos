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

/**
 * @brief   RIOT-OS logo, 64x32 pixels at 8 pixels per byte.
 */
static const uint8_t logo[] = {

// 'amiplanta128x64', 128x64px
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xe1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xfc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xe1, 0xfe, 0x7f, 0xc7, 0xff, 0xff, 0xf0, 0x01, 0xff, 0xff, 
0xff, 0xff, 0x00, 0x07, 0xc7, 0xff, 0xc3, 0xfe, 0x3f, 0xe3, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 
0xff, 0xff, 0x1f, 0xff, 0xc0, 0x3f, 0xc7, 0xfe, 0x3f, 0xf1, 0xfe, 0x01, 0xff, 0xfc, 0x7f, 0xff, 
0xff, 0xff, 0x1f, 0xff, 0xfe, 0x07, 0x8f, 0xfe, 0x3f, 0xf1, 0xe0, 0x3f, 0xff, 0xf8, 0xff, 0xff, 
0xff, 0xff, 0x1f, 0xff, 0xff, 0xe0, 0x1f, 0xfe, 0x3f, 0xf8, 0x03, 0xff, 0xff, 0xf8, 0xff, 0xff, 
0xff, 0xff, 0x1f, 0xff, 0xff, 0xfc, 0x1f, 0xfe, 0x3c, 0x38, 0x1f, 0xff, 0xff, 0xf8, 0xff, 0xff, 
0xff, 0xff, 0x8f, 0xe1, 0xfe, 0x3f, 0x0f, 0xfe, 0x38, 0x70, 0xfc, 0x7f, 0xc7, 0xf8, 0xff, 0xff, 
0xff, 0xff, 0x8f, 0xf0, 0x7e, 0x3f, 0xc0, 0x7e, 0x3f, 0xe3, 0xfc, 0x7f, 0x0f, 0xf1, 0xff, 0xff, 
0xff, 0xff, 0x8f, 0xfc, 0x1e, 0x3f, 0xe0, 0x1e, 0x3f, 0x87, 0xfc, 0x7c, 0x3f, 0xf1, 0xff, 0xff, 
0xff, 0xff, 0xc7, 0xff, 0x07, 0xff, 0xf8, 0x0e, 0x3f, 0x0f, 0xff, 0xf0, 0xff, 0xe3, 0xff, 0xff, 
0xff, 0xff, 0xe3, 0xff, 0xc1, 0xff, 0xfc, 0x7e, 0x3e, 0x3f, 0xff, 0xc3, 0xff, 0xe3, 0xff, 0xff, 
0xff, 0xff, 0xe3, 0xff, 0xf0, 0x7f, 0xfe, 0x3e, 0x3c, 0x3f, 0xff, 0x0f, 0xff, 0xc7, 0xff, 0xff, 
0xff, 0xff, 0xf1, 0xff, 0xfc, 0x1f, 0xff, 0x1e, 0x3c, 0x7f, 0xfc, 0x3f, 0xff, 0x8f, 0xff, 0xff, 
0xff, 0xff, 0xf8, 0xff, 0xff, 0x07, 0xff, 0x1e, 0x38, 0xff, 0xf0, 0xff, 0xff, 0x1f, 0xff, 0xff, 
0xff, 0xff, 0xfc, 0x3f, 0xff, 0xc1, 0xff, 0x8e, 0x31, 0xff, 0xc3, 0xff, 0xfe, 0x3f, 0xff, 0xff, 
0xff, 0xff, 0xfe, 0x1f, 0x80, 0xf0, 0x7f, 0x8e, 0x31, 0xff, 0x0f, 0x81, 0xf8, 0x7f, 0xff, 0xff, 
0xff, 0xff, 0xff, 0x87, 0xff, 0xfc, 0x3f, 0xc7, 0xf1, 0xfc, 0x3f, 0xff, 0xe1, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xc7, 0xe3, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf8, 0x3f, 0xff, 0xff, 0xc7, 0xe3, 0xff, 0xff, 0xfc, 0x1f, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xc0, 0xff, 0xff, 0x01, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0x8c, 0x7f, 0xfe, 0x31, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xf1, 0xcf, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xf0, 0x0f, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xfe, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xe1, 0xfe, 0x38, 0x7e, 0x7e, 0x07, 0xf3, 0xff, 0x87, 0xf8, 0xcf, 0xc0, 0x7f, 0x0f, 0xff, 
0xff, 0xe1, 0xfe, 0x38, 0x7e, 0x7e, 0x73, 0xf3, 0xff, 0x87, 0xf8, 0xcf, 0xf3, 0xff, 0x0f, 0xff, 
0xff, 0xe1, 0xfe, 0x18, 0x7e, 0x7e, 0x73, 0xf3, 0xff, 0x27, 0xf8, 0x4f, 0xf3, 0xfe, 0x4f, 0xff, 
0xff, 0xc8, 0xfe, 0x10, 0x7e, 0x7e, 0x73, 0xf3, 0xff, 0x33, 0xf8, 0x4f, 0xf3, 0xfe, 0x67, 0xff, 
0xff, 0xcc, 0xfe, 0x10, 0x7e, 0x7e, 0x07, 0xf3, 0xff, 0x33, 0xf9, 0x0f, 0xf3, 0xfe, 0x67, 0xff, 
0xff, 0xcc, 0xfe, 0x44, 0x7e, 0x7e, 0x3f, 0xf3, 0xff, 0x03, 0xf9, 0x8f, 0xf3, 0xfc, 0x07, 0xff, 
0xff, 0x80, 0x7e, 0x44, 0x7e, 0x7e, 0x3f, 0xf3, 0xfe, 0x71, 0xf9, 0x8f, 0xf3, 0xfc, 0xe3, 0xff, 
0xff, 0x9e, 0x7e, 0x44, 0x7e, 0x7e, 0x3f, 0xf0, 0x3e, 0x79, 0xf9, 0xcf, 0xf1, 0xfc, 0xf3, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

int main(void)
{
    uint32_t screen = 0;
    u8g2_t u8g2;

    /* initialize to I2C */
    puts("Initializing to I2C.");

    SETUP_DISPLAY(&u8g2, U8G2_R0, u8x8_byte_hw_i2c_riotos, u8x8_gpio_and_delay_riotos);

    u8x8_riotos_t user_data =
    {
        .device_index = INDEX_DRIVER_HW_I2C,
        .pin_cs = TEST_PIN_CS,
        .pin_dc = TEST_PIN_DC,
        .pin_reset = TEST_PIN_RESET,
    };

    u8g2_SetUserPtr(&u8g2, &user_data);
    u8g2_SetI2CAddress(&u8g2, TEST_ADDR);

    /* initialize the display */
    puts("Initializing display.");

    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);

    /* start drawing in a loop */
    puts("Drawing on screen.");

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
                    u8g2_DrawBitmap(&u8g2, 0, 0, 16, 53, logo);
                    u8g2_DrawStr(&u8g2, 24, 65, "AMIPLANTA!");
                    break;
            }
        } while (u8g2_NextPage(&u8g2));

        /* show screen in next iteration */
        screen = (screen + 1) % 3;

        /* sleep a little */
        ztimer_sleep(ZTIMER_USEC, US_PER_SEC);
    }

    return 0;
}
