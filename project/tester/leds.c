#include <msp430.h>
#include "leds.h"

void
leds_init(){
  P1DIR |= LEDS;
  P1OUT &= ~LEDS;
}
