# gcc_helpers
Tools to help with gcc

#### Example usage in Linux kernel using Makefile

MY_CFLAGS = $(DBGFLAGS) -Wall -Wextra -Wconversion -Wshadow -Wstrict-prototypes
CFLAGS_sbull.o += $(MY_CFLAGS)

#### Add your debugging flag (or not) to ccflags.
ifeq ($(DEBUG),y)
	DEBFLAGS = -O -g -DSBULL_DEBUG # "-O" is needed to expand inlines
else
	DEBFLAGS = -O2
endif

MY_CFLAGS = $(DBGFLAGS) -Wall -Wextra -Wconversion -Wshadow -Wstrict-prototypes -Wno-declaration-after-statement
CFLAGS_sbull.o += $(MY_CFLAGS)

obj-m	:= sbull.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
