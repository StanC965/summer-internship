#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

void button_init(void);
uint8_t button_sw0_is_pressed(void);

#endif /* BUTTON_H */