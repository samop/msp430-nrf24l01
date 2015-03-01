#
#  $Id: Makefile 364 2009-01-12 22:03:17Z jcw $
#  $Revision: 364 $
#  $Author: jcw $
#  $Date: 2009-01-12 17:03:17 -0500 (Mon, 12 Jan 2009) $
#  $HeadURL: http://tinymicros.com/svn_public/arm/lpc2148_demo/trunk/Makefile $
#

#.SILENT: 
.DELETE_ON_ERROR:

#
export CC=arm-elf-gcc
export AR=arm-elf-ar
export OBJCOPY=arm-elf-objcopy
export OBJDUMP=arm-elf-objdump
export CRT0=boot.s
export WARNINGS=-Wall -Wextra -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align -Wsign-compare -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wunused
export CFLAGS=$(WARNINGS) -DPROTOTYPE -D RUN_MODE=RUN_FROM_ROM -D GCC_ARM7 $(INCLUDES) $(BASEINCLUDE) -mcpu=arm7tdmi -T$(LDSCRIPT) -g -Os -fomit-frame-pointer
export LDSCRIPT=lpc2148-rom.ld
export LINKER_FLAGS=-Xlinker -olpc2148.elf -Xlinker -M -Xlinker -Map=lpc2148.map -n
export ROOT=$(shell pwd)
export BASEINCLUDE=-I$(ROOT) -I$(ROOT)/libs -I$(ROOT)/include -I$(ROOT)/TASK -I$(ROOT)/RTOS/Source/include -I$(ROOT)/libusb
export COMMON=$(ROOT)/common
export STARTEDATTOP=true
export RTOS_SOURCE_DIR=./RTOS/Source

#
#  Project sub-directories
#
SUBDIRS=#FreeRTOS #adc cpu dac eints fatfs fiq gps i2c iap kbd lcd leds mmc monitor newlib pwm rtc sensors spi swi timer uart uip usb usbmass usbser

SRC_FILES = TASK/ledblink.c TASK/usbser.c TASK/usb2wireless.c\
main.c \
libs/spi.c\
libs/BK2421_TxRx.c\
libs/bk2421_initialize.c \
$(RTOS_SOURCE_DIR)/tasks.c \
$(RTOS_SOURCE_DIR)/croutine.c \
$(RTOS_SOURCE_DIR)/queue.c \
$(RTOS_SOURCE_DIR)/list.c \
$(RTOS_SOURCE_DIR)/portable/MemMang/heap_2.c \
$(RTOS_SOURCE_DIR)/portable/GCC/ARM7_LPC2000/port.c \
$(RTOS_SOURCE_DIR)/portable/GCC/ARM7_LPC2000/portISR.c \
libusb/usbISR.c libusb/usbinit.c libusb/usbcontrol.c libusb/usbstdreq.c


ARM_OBJ = $(SRC_FILES:.c=.o)

.PHONY: all
all : subdirs lpc2148.hex

.PHONY: subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

lpc2148.hex : .depend Makefile lpc2148.elf
	$(OBJCOPY) lpc2148.elf -O ihex lpc2148.hex
	@echo "Length is " `grep __"end_of_text__ = ." *.map | cut -b 17-35` "bytes"

lpc2148.elf : .depend Makefile $(ARM_OBJ) $(CRT0) $(LDSCRIPT)
	$(CC) $(CFLAGS) $(ARM_OBJ) -nostartfiles $(CRT0) $(LINKER_FLAGS)
	$(OBJDUMP) -d -S lpc2148.elf >lpc2148.lst

$(ARM_OBJ) : %.o : %.c Makefile .depend
	$(CC) -c $(CFLAGS) $< -o $@

#
#  The .depend files contains the list of header files that the
#  various source files depend on.  By doing this, we'll only
#  rebuild the .o's that are affected by header files changing.
#
.depend:
	$(CC) $(CFLAGS) -M $(SRC_FILES) -o .depend

#
#  Utility targets
#
.PHONY: tags
tags :
	@rm -f tags ctags
	find . -name \*.c -exec ctags -a {} \;
	find . -name \*.h -exec ctags -a {} \;

.PHONY: clean
clean :
	find . -name \*.o -exec rm -f {} \;
	find . -name .depend -exec rm -f {} \;
	rm -f *.map *.lst *.elf *.hex .depend $(COMMON)/common.a sizes.csv tags

.PHONY: svncheck
svncheck :
	find . -name \*.c -exec grep -L HeadURL {} \;
	find . -name \*.h -exec grep -L HeadURL {} \;
	find . -name \*.s -exec grep -L HeadURL {} \;
	find . -name Makefile -exec grep -L HeadURL {} \;

.PHONY: release
release :
	./release.sh

#
#
#
ifeq (.depend,$(wildcard .depend))
include .depend
endif
