# project structure
SRC_DIR			 = src
INC_DIR			 = inc
OPENCM3_DIR		 = ../libopencm3

BINARY = WaveWorm

# target device
LIBNAME		     = opencm3_stm32f4
DEFS	    	+= -DSTM32F4
FP_FLAGS	    ?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
ARCH_FLAGS	     = -mthumb -mcpu=cortex-m4 $(FP_FLAGS)

# linker script
LDSCRIPT	     = STM32F429ZI.ld

# include files
DEFS		    += -I$(INC_DIR)

# source files
OBJS	    	+= $(SRC_DIR)/Clock.o
OBJS	    	+= $(SRC_DIR)/SDRAM.o
OBJS	    	+= $(SRC_DIR)/Interrupt.o
OBJS	    	+= $(SRC_DIR)/PerifLCD.o
OBJS	    	+= $(SRC_DIR)/PerifADC.o
OBJS	    	+= $(SRC_DIR)/PerifConsole.o
OBJS	    	+= $(SRC_DIR)/Driver.o
OBJS	    	+= $(SRC_DIR)/GraphicsEngine.o

OBJS	    	+= $(SRC_DIR)/$(BINARY).o


# libraries
DEFS	    	+= -I$(OPENCM3_DIR)/include
LDFLAGS	    	+= -L$(OPENCM3_DIR)/lib
LDLIBS		    += -l$(LIBNAME)
LDLIBS	    	+= --specs=rdimon.specs
LDLIBS		    += -Wl,--start-group -lc -lgcc -lnosys -lrdimon -Wl,--end-group
LDLIBS		    += -lm -lstdc++

# compiler config
PREFIX	    	?= arm-none-eabi
CC		    	:= $(PREFIX)-gcc
CXX		    	:= $(PREFIX)-g++
LD		    	:= $(PREFIX)-gcc
AR		    	:= $(PREFIX)-ar
AS		    	:= $(PREFIX)-as
SIZE	    	:= $(PREFIX)-size
OBJCOPY	    	:= $(PREFIX)-objcopy
OBJDUMP	    	:= $(PREFIX)-objdump
GDB		    	:= $(PREFIX)-gdb
OPT			    := -Os
DEBUG	    	:= -ggdb3
CSTD		    ?= -std=c99
STFLASH	    	 = $(shell which st-flash)

# linker config
TGT_LDFLAGS		+= --static
TGT_LDFLAGS		+= -T$(LDSCRIPT)
TGT_LDFLAGS		+= $(ARCH_FLAGS) $(DEBUG)
TGT_LDFLAGS		+= -Wl,-Map=$(*).map -Wl,--cref
TGT_LDFLAGS		+= -Wl,--gc-sections
TGT_LDFLAGS		+= -Wl,--print-gc-sections

# C flags
TGT_CFLAGS  	+= $(OPT) $(CSTD) $(DEBUG)
TGT_CFLAGS  	+= $(ARCH_FLAGS)
TGT_CFLAGS	    += -Wextra -Wshadow -Wimplicit-function-declaration
TGT_CFLAGS	    += -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes
TGT_CFLAGS	    += -fno-common -ffunction-sections -fdata-sections

# C++ flags
TGT_CXXFLAGS	+= $(OPT) $(CXXSTD) $(DEBUG)
TGT_CXXFLAGS	+= $(ARCH_FLAGS)
TGT_CXXFLAGS	+= -Wextra -Wshadow -Wredundant-decls -Weffc++
TGT_CXXFLAGS	+= -fno-common -ffunction-sections -fdata-sections
TGT_CXXFLAGS	+= -std=c++20

# preprocessor flags
TGT_CPPFLAGS	+= -MD
TGT_CPPFLAGS	+= -Wall -Wundef
TGT_CPPFLAGS	+= $(DEFS)

# openocd variables
OOCD			?= openocd
OOCD_INTERFACE	?= stlink-v2
OOCD_TARGET		?= stm32f4x

# translation targets
.SUFFIXES: .elf .bin .map
.SECONDEXPANSION:
.SECONDARY:

all: clean elf size
size: $(BINARY).size
elf: $(BINARY).elf
bin: $(BINARY).bin
flash: $(BINARY).flash

GENERATED_BINARIES = $(BINARY).elf $(BINARY).bin $(BINARY).map

$(OPENCM3_DIR)/lib/lib$(LIBNAME).a:
ifeq (,$(wildcard $@))
    $(warning $(LIBNAME).a not found, attempting to rebuild in $(OPENCM3_DIR))
    $(MAKE) -C $(OPENCM3_DIR)
endif

%.bin: %.elf
    $(OBJCOPY) -Obinary $(*).elf $(*).bin

%.elf %.map: $(OBJS) $(LDSCRIPT)
    $(LD) $(TGT_LDFLAGS) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(*).elf

%.o: %.c
    $(CC) $(TGT_CFLAGS) $(CFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).c

%.o: %.cxx
    $(CXX) $(TGT_CXXFLAGS) $(CXXFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).cxx

%.o: %.cpp
    $(CXX) $(TGT_CXXFLAGS) $(CXXFLAGS) $(TGT_CPPFLAGS) $(CPPFLAGS) -o $(*).o -c $(*).cpp

%.size: %.elf
    @echo "Output code size:"
    @$(SIZE) -A -d $(*).elf | egrep 'text|data|bss' | awk ' \
    function human_readable_size(x){ \
        if(x < 1000){ return x }else{ x /= 1024 } \
        s="kMGTEPZY"; \
        while(x >= 1000 && length(s) > 1) \
            { x /= 1024; s = substr(s, 2)} \
        return int(x + 0.5) substr(s, 1, 1) \
    } \
    { printf("%10s %8s\n", $$1, human_readable_size($$2)) } \
'

%.flash: %.elf
    @printf "  FLASH   $<\n"
    (echo "halt; program $(realpath $(*).elf) verify reset" | nc -4 localhost 4444 2>/dev/null) || \
        $(OOCD) -f interface/$(OOCD_INTERFACE).cfg \
        -f target/$(OOCD_TARGET).cfg \
        -c "program $(*).elf verify reset exit" \
        $(NULL)

%.stlink-flash: %.bin
    @printf "  FLASH  $<\n"
    $(STFLASH) write $(*).bin 0x8000000

clean:
    $(RM) $(GENERATED_BINARIES) generated.* $(OBJS) $(OBJS:%.o=%.d)

.PHONY: images clean elf bin hex srec list

-include $(OBJS:.o=.d)