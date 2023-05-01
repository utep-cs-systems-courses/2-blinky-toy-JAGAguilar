# makfile configuration
COMMON_OBJECTS  = 
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../h -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: game.elf 

#additional rules for files
game.elf: ${COMMON_OBJECTS} main.o switches.o switch_handler.o wdtHandler.o buzzer.o leds.o p2_interrupt_handler.o ../lib/libTimer.a
	${CC} ${CFLAGS} -o $@ $^

load: game.elf
	msp430loader.sh  $^

main.o: switches.h switch_handler.c wdtHandler.c buzzer.h leds.h p2_interrupt_handler.c

buzzer.o: buzzer.c buzzer.h

switches.o: switches.c switches.h buzzer.h

leds.o: leds.c leds.h

clean: $^
	rm -f *.o *.elf



