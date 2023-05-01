#include <msp430.h>
#include "switches.h"

int notes[] = {1273,1350,1607,2145,2272,1517,1201,948};
short duration[] = {25,25,25,25,25,25,25,125,200};
short counter = 0;
short beat = 0;
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
