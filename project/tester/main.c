#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"
#include "wdtHandler.h"
#include "p2_interrupt_handler.h"
#include "leds.h"

void main(){
int notes[] = {1273,1350,1607,2145,2272,1517,1201,948};
short duration[] = {25,25,25,25,25,25,25,125,200};
short counter = 0;
short beat = 0;
  configureClocks();
  buzzer_init();
  leds_init();
  switches_init();

  or_sr(0x18);

}
