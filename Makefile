src_dirs         = platform math datatype engine

ptfm_inc_dir     = platform
math_inc_dir     = math
type_inc_dir     = datatype
engn_inc_dir     = engine

bin_dir          = ../bin

opencm3_dir      = libopencm3

binary          := waveworm
objects         := $(foreach dir, $(src_dirs), $(patsubst $(dir)/%.cpp, $(bin_dir)/%.o, $(wildcard $(dir)/*.cpp)))
deps            := $(objects:.o=.d)

vpath %.cpp $(src_dirs)

includes        += -I$(opencm3_dir)/include
includes        += -I$(ptfm_inc_dir)
includes        += -I$(math_inc_dir)
includes        += -I$(type_inc_dir)
includes        += -I$(engn_inc_dir)

ldscript         = platform/STM32F429ZI.ld

libname          = opencm3_stm32f4

gcc_prefix      ?= arm-none-eabi
cxx             := $(gcc_prefix)-g++
ld              := $(gcc_prefix)-g++
size            := $(gcc_prefix)-size
objcopy         := $(gcc_prefix)-objcopy

opt             := -Os -O2
debug           := -ggdb3
cxxstd          ?= -std=c++20
stflash          = $(shell which st-flash)

device          += -DSTM32F4
flptflags       ?= -mfloat-abi=hard -mfpu=fpv4-sp-d16
archflags        = -mthumb -mcpu=cortex-m4 $(flptflags)

cppflags         += -MD
cppflags         += -Wall -Wundef
cppflags         += $(device)
cppflags         += $(includes)

cxxflags        += $(opt) $(debug) $(cxxstd)
cxxflags        += $(archflags)
cxxflags        += -Wextra -Wshadow -Wredundant-decls -Weffc++
cxxflags        += -fno-common -ffunction-sections -fdata-sections
cxxflags        += -fexceptions

ldflags         += --static
ldflags         += -T$(ldscript)
ldflags         += $(archflags) $(debug)
ldflags         += -Wl,-Map=$(bin_dir)/$(binary).map -Wl,--cref
ldflags         += -Wl,--gc-sections
ldflags         += -Wl,--print-gc-sections

ldflags         += -L$(opencm3_dir)/lib

ldlibs          += -l$(libname)
ldlibs          += --specs=rdimon.specs
ldlibs          += -Wl,--start-group -lc -lgcc -lnosys -lrdimon -Wl,--end-group
ldlibs          += -lm -lstdc++

oocd            ?= openocd
oocd_interface  ?= stlink-v2
oocd_target     ?= stm32f4x

all: dir clean elf size
size: $(bin_dir)/$(binary).size
elf: $(bin_dir)/$(binary).elf
bin: $(bin_dir)/$(binary).bin
flash: $(bin_dir)/$(binary).flash

generated_binaries += $(bin_dir)/$(binary).elf
generated_binaries += $(bin_dir)/$(binary).map
generated_binaries += $(bin_dir)/$(binary).bin

$(opencm3_dir)/lib/lib$(libname).a:
ifeq (, $(wildcard $@))
	$(warning $(libname).a not found, attempting to rebuild in $(opencm3_dir))
	$(MAKE) -C $(opencm3_dir)
endif

%.bin: %.elf
	$(objcopy) -Obinary $(*).elf $(*).bin

$(bin_dir)/$(binary).elf: $(objects) $(ldscript)
	$(ld) $(ldflags) $(objects) $(ldlibs) -o $@

$(objects): $(bin_dir)/%.o: %.cpp
	$(cxx) $(cppflags) $(cxxflags) -o $@ -c $^

%.size: %.elf
	@echo "Output code size:"
	@$(size) -A -d $(*).elf | egrep 'text|data|bss' | awk ' \
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
	@printf "FLASH $<\n"
	(echo "halt; program $(realpath $(*).elf) verify reset" | nc -4 localhost 4444 2>/dev/null) || \
		$(oocd) -f interface/$(oocd_interface).cfg \
		-f target/$(oocd_target).cfg \
		-c "program $(*).elf verify reset exit" \
		$(NULL)

dir:
	mkdir -p $(bin_dir)

clean:
	$(RM) $(generated_binaries) $(objects) $(deps)

print:
	@echo $(objects)

.PHONY: all dir clean elf map bin size flash print

-include $(deps)