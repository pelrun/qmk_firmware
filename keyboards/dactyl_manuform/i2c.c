#include <stdlib.h>
#include <stdbool.h>
#include "ch.h"
#include "hal.h"
#include "config.h"
#include "i2c.h"
#include "hal_i2c_lld.h"

#ifdef USE_I2C

static uint8_t          rxBuf[16];
static volatile uint8_t slave_buffer_pos;
static volatile uint8_t slave_buffer[SLAVE_BUFFER_SIZE];

static const I2CConfig masterI2Cconfig = {OPMODE_I2C, SCL_CLOCK, STD_DUTY_CYCLE};

// Setup twi to run at 100kHz
void i2c_master_init(I2CDriver * i2cp)
{
  i2cStart(i2cp, &masterI2Cconfig);
  palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); /* SCL */
  palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); /* SDA */
}

void i2c_reset_state(void) {
}

void i2c_set_slave_data(const uint8_t *buf, const size_t length)
{
  memcpy(slave_buffer, buf, length);
}

void onI2CSlaveReceive(I2CDriver * i2cp, const uint8_t * rxdata, size_t rxbytes)
{
  (void)i2cp;
  (void)rxdata;
  (void)rxbytes;

  slave_buffer_pos = rxdata[0];
}

void onI2CSlaveRequest(I2CDriver * i2cp)
{
  i2cSlaveStartTransmission(i2cp, slave_buffer + slave_buffer_pos, ROWS_PER_HAND);

  i2cSlaveOnReceive(i2cp, onI2CSlaveReceive, rxBuf, 16);
}

void i2c_slave_init(I2CDriver * i2cp, const uint8_t address)
{
  i2cStart(i2cp, &masterI2Cconfig);
  palSetPadMode(GPIOB, 6, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); /* SCL */
  palSetPadMode(GPIOB, 7, PAL_MODE_STM32_ALTERNATE_OPENDRAIN); /* SDA */

  i2cSlaveOnRequest(i2cp, onI2CSlaveRequest);
  i2cSlaveOnReceive(i2cp, onI2CSlaveReceive, rxBuf, 16);
  i2cSlaveMatchAddress(i2cp, address);
}

#endif
