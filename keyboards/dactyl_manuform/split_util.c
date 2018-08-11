#include "ch.h"
#include "hal.h"

#include "split_util.h"
#include "matrix.h"
#include "keyboard.h"
#include "config.h"
#include "timer.h"

#ifdef USE_I2C
#include "i2c.h"
#else
#include "serial.h"
#endif

volatile bool isLeftHand = true;

static void setup_handedness(void)
{
  palSetPadMode(GPIOC, 14, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOC, 15, PAL_MODE_INPUT_PULLDOWN);
  palSetPad(GPIOC, 14);
  isLeftHand = palReadPad(GPIOC, 15);
  palClearPad(GPIOC, 14);
}

static void keyboard_master_setup(void)
{
#ifdef USE_I2C
  i2c_master_init(&I2C_DEVICE);
#endif
}

static void keyboard_slave_setup(void)
{
  timer_init();
#ifdef USE_I2C
  i2c_slave_init(&I2C_DEVICE, SLAVE_I2C_ADDRESS);
#endif
}

bool has_usb(void)
{
  return usbGetDriverStateI(&USBD1) == USB_ACTIVE;
}

void keyboard_slave_loop(void)
{
  matrix_init();

  while (1)
  {
    matrix_slave_scan();
  }
}

// this code runs before the usb and keyboard is initialized
void matrix_setup(void)
{
  setup_handedness();

  if (has_usb())
  {
    keyboard_master_setup();
  }
  else
  {
    keyboard_slave_setup();
    keyboard_slave_loop();
  }
}
