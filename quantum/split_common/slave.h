#ifndef _SLAVE_H
#define _SLAVE_H

void slave_init(void);
void master_init(void);

int slave_update(void);

void update_master_matrix(uint8_t row, matrix_row_t value);
void update_slave_matrix(uint8_t row, matrix_row_t value);

#endif