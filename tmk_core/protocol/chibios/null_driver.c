
#include "host_driver.h"

static uint8_t keyboard_leds(void) {
    return 0;
}

static void send_keyboard(report_keyboard_t *report) {
    (void)report;
}

static void send_mouse(report_mouse_t *report) {
    (void)report;
}

static void send_system(uint16_t data) {
    (void)data;
}

static void send_consumer(uint16_t data) {
    (void)data;
}

host_driver_t null_driver = {
  keyboard_leds,
  send_keyboard,
  send_mouse,
  send_system,
  send_consumer
};
