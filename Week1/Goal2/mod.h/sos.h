#ifndef SOS_H
#define SOS_H

#include <stdint.h>

// Public Architecture Interfaces
void sos_init(void);
uint8_t sos_run_sequence(void);

#endif /* SOS_H */