#include <msp430.h>
#include "libTimer.h"

#define RLED BIT0;
#define GLED BIT6;
#define LEDS (GLED|RLED);

#define SW1 BIT0;
#define SW2 BIT1;
#define SW3 BIT2;
#define SW4 BIT3;
#define SWITCHES (SW1|SW2|SW3|SW4);

void main(void)
{
  configureClocks();
  P1DIR |=LEDS;
  P1OUT &= ~LEDS;
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= SWITCHES;

  or_sr(0x10);


  
}
void
switch_interrupt_handlers()
{
  char p2val = P2IN;

  P2IES |= (p2val & switches);
  P2IES &= (p2val | ~SWITCHES);

  if(p2val&SW1){
    P1OUT |= GLED;
    P1OUT |=~RLED;
  }
  if(p2val&SW2){
    P1OUT |= RLED;
    P1OUT |= ~GLED;
  }
  if(p2val&SW3){
    P1OUT|= GLED;
    P1OUT|= ~RLED;
  }
  if(p2val&SW4){
    P1OUT|= GLED;
    P1OUT|= ~RLED;
  }

}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
