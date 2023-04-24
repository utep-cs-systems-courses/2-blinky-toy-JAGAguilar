#include <msp430.h>
#include "libTimer.h"


#define RLED BIT0
#define GLED BIT6
#define LEDS (RLED|GLED)


#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SW5 BIT3
#define SWITCHES 15 

void buzzer_set_period(short cycles)
{
  CCR0 = cycles;
  CCR1 = cycles>>1;
}

void buzzer_init(){
  timerAUpmode();
  P2SEL2 &= ~(BIT6 | BIT7);
  P2SEL &= ~BIT7;
  P2SEL |= BIT6;
  P2DIR = BIT6;
}

void main(void)
{
  //enableWDTInterrupts();
  configureClocks();
  P1DIR |=LEDS;
  P1OUT &= ~LEDS;

  P1DIR &= ~SW5;
  P1OUT |= SW5;
  P1REN |= SW5;
  P1IE |= SW5;
  
  P2REN |= SWITCHES;
  P2IE |= SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  buzzer_init();

  or_sr(0x18);

}
static int secretButton =0;
void
switch_interrupt_handler()
{
  char p2val = P2IN;
  char p1val = P1IN;
  P1IES |= (p1val & SW5);
  P1IES &= (p1val | ~SW5);
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);

  
  if (!(p2val & SW1)){
    P1OUT |= RLED;
    P1OUT |= GLED;
  }if(!(p2val & SW4)){
    P1OUT &= ~RLED;
    buzzer_set_period(1738);
  }
  if(!(p1val & SW5)){
    //secretButton =1;
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
__interrupt_vec(PORT1_VECTOR) Port_1(){
  if(P1IFG & SW5){
    P1IFG &= ~SW5;
    switch_interrupt_handler();
  }
}
static int notes[] = {1273,1350,1607,2145,2272,1517,1201,948};
static short duration[] = {200};
static short counter = 0;
static short state =0;
static short beat = 0;
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  if(!(P1IN & SW5)){
    switch(state){
    case(0):
      buzzer_set_period(notes[beat]);
      beat++;
      goto defaultState;
    case(1):
      buzzer_set_period(notes[beat]);
      beat++;
      break;
    defaultState:
      counter++;
      if(counter > duration[beat]){
	counter =0;
	state +=1;
      }
    }
  }
}

