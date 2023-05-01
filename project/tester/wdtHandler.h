#ifndef wdt_included
#define wdt_included

extern int notes[];
extern short duration[];
extern short counter;
extern short beat;

void __interrupt_vec(WDT_VECTOR) WDT();

#endif
