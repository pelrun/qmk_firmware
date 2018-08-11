/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef KEYBOARDS_DACTYL_MANUFORM_CONFIG_H_
#define KEYBOARDS_DACTYL_MANUFORM_CONFIG_H_

//#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x3060
#define DEVICE_VER 0x0001
#define MANUFACTURER pelrun
#define PRODUCT Dactyl - Manuform Mini
#define DESCRIPTION     A split keyboard for the cheap makers

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 5
#define ROWS_PER_HAND (MATRIX_ROWS / 2)

// wiring of each half
#define MATRIX_ROW_PINS { PAL_LINE(GPIOB, 13), PAL_LINE(GPIOB, 14), PAL_LINE(GPIOB, 15), PAL_LINE(GPIOA, 8), PAL_LINE(GPIOA, 9) }
#define MATRIX_COL_PINS { PAL_LINE(GPIOB, 9), PAL_LINE(GPIOB, 8), PAL_LINE(GPIOB, 7), PAL_LINE(GPIOB, 6), PAL_LINE(GPIOB, 5) }

#define USE_I2C
#define I2C_DEVICE I2CD2
#define SLAVE_I2C_ADDRESS 0x32

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* mouse config */
#define MOUSEKEY_INTERVAL 20
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 60
#define MOUSEKEY_MAX_SPEED 7
#define MOUSEKEY_WHEEL_DELAY 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 1

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
 */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

/* Enables This makes it easier for fast typists to use dual-function keys */
#define PERMISSIVE_HOLD

/* ws2812 RGB LED */
// #define RGB_DI_PIN D3
// #define RGBLIGHT_TIMER
// #define RGBLED_NUM 12  // Number of LEDs
// #define ws2812_PORTREG PORTD
// #define ws2812_DDRREG DDRD

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif /* KEYBOARDS_CHIBIOS_TEST_DACTYL_MANUFORM_CONFIG_H_ */
