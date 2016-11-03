# Put your stlink folder here so make burn will work.
STLINK=~/stlink.git

# Put your source files here (or *.c, etc)
SRCS=main.c system_stm32f10x.c conf.c config.c ds18b20.c func.c media.c newlib_stubs.c stm32f1xx_it.c xbee.c
SRCS+=$(wildcard stm32/*.c)

# Binaries will be generated with this name (.elf, .bin, .hex, etc)
PROJ_NAME=teste


# Normally you shouldn't need to change anything below this line!
#######################################################################################

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS  = -g -O2  -Tstm32_flash.ld 
CFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m3 -mthumb-interwork
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
#CFLAGS += -I.
CFLAGS += -DUSE_STDPERIPH_DRIVER

# Include files from STM libraries

CFLAGS += -I../include/
CFLAGS += -I../include/stm32/

# add startup file to build
SRCS += startup_stm32f10x_md_vl.S 
OBJS = $(SRCS:.c=.o)


.PHONY: proj

all: proj

proj: $(PROJ_NAME).elf
	

$(PROJ_NAME).elf: $(SRCS)
	@echo $(SRCS)

	$(CC) $(CFLAGS) $^ -o $@ 
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin

clean:
	rm -f *.o $(PROJ_NAME).elf $(PROJ_NAME).hex $(PROJ_NAME).bin

# Flash the STM32F4
burn: proj
	$(STLINK)/st-flash write $(PROJ_NAME).bin 0x8000000
