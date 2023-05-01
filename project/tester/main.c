#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"
#include "switches.h"
#include "wdtHandler.c"
#include "p2_interrupt_handler.c"

void main(){
  configureClocks();
  buzzer_init();
  led_init();
  switches_init();

  or_sr(0x18);

}
