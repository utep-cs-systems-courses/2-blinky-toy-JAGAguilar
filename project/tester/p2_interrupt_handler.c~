#include <msp430.h>
#include "libTimer.h"

static short secretButton =0;
static short correct = 0;
static int notes[] = {1273,1350,1607,2145,2272,1517,1201,948};
static short duration[] = {25,25,25,25,25,25,25,125,200};
static short counter = 0;
static short beat = 0;

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}
void
__interrupt_vec(WDT_VECTOR) WDT()
{
  if(secretButton == 1){
    if(beat>8){
      buzSet(0);
      counter=0;
      secretButton =0;
    }
    else{
      if(counter==duration[beat]){
	beat+=1;
	counter =0;
      }else{
	counter+=1;
	buzSet(notes[beat]);
      }
    }
  }
}
