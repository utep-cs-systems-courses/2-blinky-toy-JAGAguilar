#include <msp430.h>
#include "libTimer.h"


#define RLED BIT0
#define GLED BIT6
#define LEDS (RLED|GLED)


#define SW1 BIT0
#define SW2 BIT1
#define SW3 BIT2
#define SW4 BIT3
#define SWITCHES (SW1|SW2|SW3|SW4)


void main(void)
{
  configureClocks();
  P1DIR |=LEDS;
  P1OUT &= ~LEDS;
  
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  buzzer_Init();

  or_sr(0x18);

}

void
switch_interrupt_handler()
{
  char p1val = P2IN;

  P2IES |= (p1val & SWITCHES);
  P2IES &= (p1val | ~SWITCHES);


  if(p1val&SW1){
    P1OUT &=~GLED;
    P1OUT &= ~RLED;
  }
  if(p1val&SW2){
    P1OUT |= GLED;
    P1OUT |= RLED;
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
void
buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}
void
buzzer_set_period(short cycles)
{
  CCR0 = cycles;
  CCR1 = cycles >>1;
}
static 
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  
}
