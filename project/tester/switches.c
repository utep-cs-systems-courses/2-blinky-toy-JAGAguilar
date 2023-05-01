#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"


void
switches_init(){
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
}

void
switch_interrupt_handler()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  if(correct ==0){
    buzSet(900);
    P1OUT &= ~RLED;
    P1OUT &= ~GLED;
    if(!(p2val & SW1)){
      correct =1;
    }
    if(!(p2val & SW3)){
      P1OUT |= RLED;
      buzSet(1738);
    }
    if(!(p2val & SW2)){
      P1OUT |= RLED;
      buzSet(8008);
    }
    if(!(p2val & SW4)){
      secretButton =1;
      enableWDTInterrupts();
    }
  }
  else{
    P1OUT |= GLED;
    P1OUT &= ~RLED;
    buzSet(0);
  }
  
}
