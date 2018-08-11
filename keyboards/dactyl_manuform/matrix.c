/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include "ch.h"
#include "hal.h"

#include "config.h"
/*
 * scan matrix
 */
#include "debug.h"
#include "matrix.h"
#include "print.h"
#include "util.h"
#include "wait.h"
#include "split_util.h"
#include "i2c.h"

#ifndef DEBOUNCE
#define DEBOUNCE 5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[ROWS_PER_HAND];

static const ioline_t row_pins[ROWS_PER_HAND] = MATRIX_ROW_PINS;
static const ioline_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;

volatile bool isLeftHand = false;
static int    matrix_offset;

static matrix_row_t read_cols(void);
static void         init_pins(void);
static void         unselect_rows(void);
static void         select_row(uint8_t row);

inline uint8_t matrix_rows(void)
{
  return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void)
{
  return MATRIX_COLS;
}

/* generic STM32F103C8T6 board */
#ifdef BOARD_GENERIC_STM32_F103
inline void LED_ON(void)
{
  palClearPad(GPIOC, GPIOC_LED);
}
inline void LED_OFF(void)
{
  palSetPad(GPIOC, GPIOC_LED);
}
void LED_TGL(void)
{
  palTogglePad(GPIOC, GPIOC_LED);
}
#endif

/* Maple Mini */
#ifdef BOARD_MAPLEMINI_STM32_F103
#define LED_ON() \
  do \
  { \
    palSetPad(GPIOB, 1); \
  } while (0)
#define LED_OFF() \
  do \
  { \
    palClearPad(GPIOB, 1); \
  } while (0)
#define LED_TGL() \
  do \
  { \
    palTogglePad(GPIOB, 1); \
  } while (0)
#endif

void matrix_init(void)
{
  matrix_offset = isLeftHand ? 0 : ROWS_PER_HAND;

  // initialize row and col
  init_pins();
  unselect_rows();

  // initialize matrix state: all keys off
  for (uint8_t i = 0; i < MATRIX_ROWS; i++)
  {
    matrix[i]            = 0;
    matrix_debouncing[i>>1] = 0;
  }

  // debug
  debug_enable = true;
  LED_ON();
  wait_ms(500);
  LED_OFF();
}

uint8_t _matrix_scan(void)
{
  for (uint8_t i = 0; i < ROWS_PER_HAND; i++)
  {
    select_row(i);
    wait_us(30);  // without this wait read unstable value.
    matrix_row_t cols = read_cols();
    debug_hex(cols);
    if (matrix_debouncing[i] != cols)
    {
      matrix_debouncing[i] = cols;
      if (debouncing)
      {
        debug("bounce!: ");
        debug_hex(debouncing);
        debug("\n");
      }
      debouncing = DEBOUNCE;
    }
    unselect_rows();
  }

  if (debouncing)
  {
    if (--debouncing)
    {
      wait_ms(1);
    }
    else
    {
      for (uint8_t i = 0; i < ROWS_PER_HAND; i++)
      {
        matrix[matrix_offset + i] = matrix_debouncing[i];
      }
    }
  }

  return 1;
}

uint8_t matrix_scan(void)
{
  uint8_t ret          = _matrix_scan();
  int     slave_offset = ROWS_PER_HAND - matrix_offset;

  // get matrix from other half here
#ifdef USE_I2C
  uint8_t dest_offset = 0;

  if (i2cMasterTransmitTimeout(&I2C_DEVICE, SLAVE_I2C_ADDRESS, &dest_offset, 1, matrix + slave_offset, ROWS_PER_HAND, 100) != MSG_OK)
  {
    i2c_reset_state();
  }
#endif
  return ret;
}

void matrix_slave_scan(void)
{
  _matrix_scan();

#ifdef USE_I2C
  i2c_set_slave_data(matrix+matrix_offset, ROWS_PER_HAND);
#endif
}

inline bool matrix_is_on(uint8_t row, uint8_t col)
{
  return (matrix[row] & ((matrix_row_t)1 << col));
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
  return matrix[row];
}

void matrix_print(void)
{
  print("\nr/c 0123456789ABCDEF\n");
  for (uint8_t row = 0; row < MATRIX_ROWS; row++)
  {
    phex(row);
    print(": ");
    pbin_reverse16(matrix_get_row(row));
    print("\n");
  }
}

/* Column pin configuration
 */
static void init_pins(void)
{
  palSetPadMode(GPIOC, GPIOC_LED, PAL_MODE_OUTPUT_PUSHPULL);
  for (uint8_t col = 0; col < MATRIX_COLS; col++)
  {
    palSetLineMode(col_pins[col], PAL_MODE_INPUT_PULLUP);
  }
  for (uint8_t row = 0; row < ROWS_PER_HAND; row++)
  {
    palSetLineMode(row_pins[row], PAL_MODE_OUTPUT_OPENDRAIN);
  }
}

/* Returns status of switches(1:on, 0:off) */
static matrix_row_t read_cols(void)
{
  matrix_row_t row = 0;

  for (uint8_t col = 0; col < MATRIX_COLS; col++)
  {
    row = (row << 1) | ((palReadLine(col_pins[col]) == PAL_LOW) & 1);
  }

  return row;
}

/* Row pin configuration
 */
static void unselect_rows(void)
{
  for (uint8_t row = 0; row < ROWS_PER_HAND; row++)
  {
    palSetLine(row_pins[row]);
  }
}

static void select_row(uint8_t row)
{
  // Output low to select
  palClearLine(row_pins[row]);
}
