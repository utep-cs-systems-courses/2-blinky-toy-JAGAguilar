#ifndef switches_included
#define switches_included

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8
#define SWITCHES 15

void switches_init();
void switch_interrupt_handler();

extern short correct;
extern short secretButton;
#endif
