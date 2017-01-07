#include "Peripherals_Init.h"
#include<xc.h>
void init_adc(void)
{
    TRISAbits.TRISA0=1;   // set RA0 to Input
    ANSELAbits.ANSA0=1;   // set RA0 to Analog
    ADCON1bits.ADCS=0b011;    // FRC clock for ADC
    ADCON1bits.ADPREF=0;    // Vref is connected to Vdd

}

void init_pwm(void)
{
    
}