#include <msp430.h>
#include "libTimer.h"
#include "switches.h"
#include "p2_interrupt_handler.h"

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

