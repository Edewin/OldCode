
#include "System_Init.h"
#include<xc.h>

// Clock source and freq select

void init_sys(void)
{
    OSCCONbits.SCS=1;     // Internal System Clock
    OSCCONbits.IRCF=0b1110;  // 32 MHz

}

