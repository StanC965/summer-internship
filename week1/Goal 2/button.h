#include "sos.h"
#include "iom324pb.h"

static volatile int btn=0;
#pragma vector=PCINT2_vect
__interrupt void buton_apasat(void);
void PressToSos();
void SosStop();