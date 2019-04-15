#include <string.h>
#include <stddef.h>

#include "serial_link/system/serial_link.h"
#include "serial_link/protocol/transport.h"

#include "config.h"
#include "matrix.h"
#include "quantum.h"

#include "transport.h"

typedef struct {
  matrix_row_t rows[MATRIX_ROWS];
} matrix_object_t;

SLAVE_TO_MASTER_OBJECT(keyboard_matrix, matrix_object_t);
// MASTER_TO_ALL_SLAVES_OBJECT(name, type);

static remote_object_t* remote_objects[] = {
    REMOTE_OBJECT(keyboard_matrix),
};

static void init_remote_objects(void) { add_remote_objects(remote_objects, sizeof(remote_objects) / sizeof(remote_object_t*)); }

void transport_master_init(void) { init_remote_objects(); }
void transport_slave_init(void) { init_remote_objects(); }

bool transport_master(matrix_row_t matrix[]) {
  matrix_object_t* m = begin_write_keyboard_matrix();
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    m->rows[i] = matrix[i];
  }
  end_write_keyboard_matrix();
  return true;
}

void transport_slave(matrix_row_t matrix[]) {
  matrix_object_t* m = read_keyboard_matrix(0);
  if (m) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
      matrix[i] = m->rows[i];
    }
  }
}
