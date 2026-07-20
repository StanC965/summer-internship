#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

// Public Interface Layer
void button_init(void);
uint8_t button_sw0_is_pressed(void);

#endif /* BUTTON_H */