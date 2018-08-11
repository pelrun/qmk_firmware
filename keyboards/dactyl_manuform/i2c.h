#ifndef I2C_H
#define I2C_H

#include <stdint.h>

#define SLAVE_BUFFER_SIZE 0x10

// i2c SCL clock frequency
#define SCL_CLOCK  400000L

void i2c_master_init(I2CDriver * i2cp);
void i2c_reset_state(void);
void i2c_slave_init(I2CDriver * i2cp, const uint8_t address);
void i2c_set_slave_data(const uint8_t * buf, const size_t length);

#endif
