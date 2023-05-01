#ifndef leds_included
#define leds_included

#define GLED BIT0
#define RLED BIT6
#define LEDS (RLED|GLED)

void leds_init();

#endif
