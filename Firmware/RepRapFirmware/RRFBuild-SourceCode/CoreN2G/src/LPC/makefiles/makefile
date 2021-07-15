PROCESSOR = LPC17xx


#Enable when debugging on MBED to swap serial and USB 
#and select direct ld script
#MBED = true



BUILD_DIR ?= ./build
FREERTOS_DIR ?= ./FreeRTOS
REPRAPFIRMWARE_DIR ?= ./RepRapFirmware
RRFLIBRARIES_DIR ?= ./RRFLibraries
CORELPC_DIR ?= ./CoreN2G

BUILD ?= Debug

NETWORK ?= ESP8266WIFI

TMC22XX ?= true

STARTUP_DELAY ?= -DSTARTUP_DELAY=10000

#Comment out to show compilation commands (verbose)
V=@

$(info Building RepRapFirmware for LPC1768/1769 based boards:)

OUTPUT_NAME=firmware

## Cross-compilation commands 
CC      = arm-none-eabi-gcc
CXX     = arm-none-eabi-g++
LD      = arm-none-eabi-gcc
AR      = arm-none-eabi-ar
AS      = arm-none-eabi-as
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE    = arm-none-eabi-size

MKDIR = mkdir -p

#function to get unique values from a list from bobbogo (https://stackoverflow.com/questions/16144115/makefile-remove-duplicate-words-without-sorting)
uniq = $(if $1,$(firstword $1) $(call uniq,$(filter-out $(firstword $1),$1)))


include $(MAKE_DIR)/Core.mk
include $(MAKE_DIR)/FreeRTOS.mk
include $(MAKE_DIR)/RRFLibraries.mk
include $(MAKE_DIR)/RepRapFirmware.mk

ifeq ($(BUILD),Debug)
	#DEBUG_FLAGS = -Og -g -DLPC_DEBUG
	DEBUG_FLAGS = -Os -g -DLPC_DEBUG $(STARTUP_DELAY)
        $(info - Build: Debug) 
else
	DEBUG_FLAGS = -Os
        $(info - Build: Release)
endif
	

#select correct linker script
ifeq ($(MBED), true)
	#No bootloader for MBED
	LINKER_SCRIPT_BASE = $(CORE_DIR)/src/LPC/variants/LPC/linker_scripts/gcc/LPC17xx_direct
else 
	#Linker script to avoid Smoothieware Bootloader
 	LINKER_SCRIPT_BASE = $(CORE_DIR)/src/LPC/variants/LPC/linker_scripts/gcc/LPC17xx_smoothie
endif


#Path to the linker Script
LINKER_SCRIPT  = $(LINKER_SCRIPT_BASE)_combined.ld
$(info  - Linker Script used: $(LINKER_SCRIPT))


#Flags common for Core in c and c++
FLAGS  = -D__$(PROCESSOR)__ -DLPC17xx -D_XOPEN_SOURCE -DENABLE_UART3

ifeq ($(MBED), true)
        $(info  - Building for MBED)
	    FLAGS += -D__MBED__
        ifeq ($(ESP8266WIFI), true)
            FLAGS += -DENABLE_UART3 -DENABLE_UART2 -DENABLE_UART1
        endif
endif

#lpcopen Defines
FLAGS += -DCORE_M3
#RTOS + enable mods to RTOS+TCP for RRF
FLAGS += -DRTOS -DFREERTOS_USED -DRRF_RTOSPLUS_MOD
FLAGS += -DDEVICE_USBDEVICE=1 -DTARGET_LPC1768
FLAGS +=  -Wall -c -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections -march=armv7-m 
FLAGS += -nostdlib -Wdouble-promotion -fsingle-precision-constant -fstack-usage
#FLAGS += -Wfloat-equal
#FLAGS += -Wundef
FLAGS += $(DEBUG_FLAGS)
FLAGS += -MMD -MP 

ifeq ($(NETWORK), ETHERNET)
        $(info  - Networking: Ethernet)
        FLAGS += -DLPC_NETWORKING
else ifeq ($(NETWORK), ESP8266WIFI)
        $(info  - Networking: ESP8266 WIFI) 
        FLAGS += -DESP8266WIFI
else ifeq ($(NETWORK), SBC)
        $(info  - SBC Interface Enabled)
        FLAGS += -DLPC_SBC
else
        $(info  - Networking: None)
endif

ifeq ($(TMC22XX), true)
        $(info  - Smart Drivers: TMC22XX)
        FLAGS += -DSUPPORT_TMC22xx
else
        $(info  - Smart Drivers: None)
endif

CFLAGS   = $(FLAGS) -std=gnu11 -fgnu89-inline 
#Ignore noexcepts in c
CFLAGS   += -Dnoexcept=
CXXFLAGS = $(FLAGS) -std=gnu++17 -fno-threadsafe-statics -fexceptions -fno-rtti -Wno-register
CXXFLAGS_RRFL = $(FLAGS) -std=gnu++17 -fno-threadsafe-statics -fno-exceptions -fno-rtti -Wno-register
CXXFLAGS_CORE = $(FLAGS) -std=gnu++17 -fno-threadsafe-statics -fno-exceptions -fno-rtti -Wno-register


#all Includes (RRF + Core)
INCLUDES = $(CORE_INCLUDES) $(RRFLIBRARIES_INCLUDES) $(RRF_INCLUDES) $(RRFLIBC_INCLUDES)


DEPS = $(CORE_OBJS:.o=.d)
DEPS += $(RRF_OBJS:.o=.d)
DEPS += $(RRFLIBC_OBJS:.o=.d)
DEPS += $(RRFLIBRARIES_OBJS:.o=.d)

default: all

all: firmware

-include $(DEPS)

firmware:  $(BUILD_DIR)/$(OUTPUT_NAME).elf

coreLPC: $(BUILD_DIR)/core.a

$(BUILD_DIR)/libLPCCore.a: $(CORE_OBJS)
	$(V)$(AR) rcs $@ $(CORE_OBJS)
	@echo "\nBuilt LPCCore\n"
	
$(BUILD_DIR)/libRRFLibraries.a: $(RRFLIBRARIES_OBJS)
	$(V)$(AR) rcs $@ $(RRFLIBRARIES_OBJS)
	@echo "\nBuilt RRF Libraries\n"
	
$(BUILD_DIR)/$(OUTPUT_NAME).elf: $(BUILD_DIR)/libLPCCore.a $(BUILD_DIR)/libRRFLibraries.a $(RRFLIBC_OBJS) $(RRF_OBJS)
	@echo "\nCreating $(OUTPUT_NAME).bin"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(LD) -L$(BUILD_DIR)/ -L$(CORE_DIR)/src/LPC/variants/LPC/linker_scripts/gcc/ --specs=nosys.specs -Os -Wl,--warn-section-align -Wl,--fatal-warnings -march=armv7-m -mcpu=cortex-m3 -T$(LINKER_SCRIPT) -Wl,-Map,$(BUILD_DIR)/$(OUTPUT_NAME).map -o $(BUILD_DIR)/$(OUTPUT_NAME).elf  -mthumb -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--start-group $(BUILD_DIR)/$(CORE_DIR)/src/LPC/new.o $(RRFLIBC_OBJS) -lLPCCore $(RRF_OBJS) -lsupc++ -lRRFLibraries  -Wl,--end-group -lm 
	$(V)$(OBJCOPY) --strip-unneeded -O binary $(BUILD_DIR)/$(OUTPUT_NAME).elf $(BUILD_DIR)/$(OUTPUT_NAME).bin
	$(V)$(SIZE) $(BUILD_DIR)/$(OUTPUT_NAME).elf
	-@$(MAKE_DIR)/staticMemStats.sh $(BUILD_DIR)/$(OUTPUT_NAME).elf
	
$(BUILD_DIR)/%.o: %.c
	@echo "[$<]"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(CC)  $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MM -MF $(patsubst %.o,%.d,$@) $<
	$(V)$(CC)  $(CFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -o $@ $<

$(BUILD_DIR)/$(RRFLIBRARIES_DIR)/%.o : $(RRFLIBRARIES_DIR)/%.cpp
	@echo "RRFL [$<]"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(CXX) $(CXXFLAGS_RRFL) $(DEFINES) $(INCLUDES) -MMD -MP -MM -MF $(patsubst %.o,%.d,$@) $<
	$(V)$(CXX) $(CXXFLAGS_RRFL) $(DEFINES) $(INCLUDES) -MMD -MP -o $@ $<

$(BUILD_DIR)/$(CORELPC_DIR)/%.o : $(CORELPC_DIR)/%.cpp
	@echo "CORE [$<]"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(CXX) $(CXXFLAGS_CORE) $(DEFINES) $(INCLUDES) -MMD -MP -MM -MF $(patsubst %.o,%.d,$@) $<
	$(V)$(CXX) $(CXXFLAGS_CORE) $(DEFINES) $(INCLUDES) -MMD -MP -o $@ $<

$(BUILD_DIR)/%.o: %.cpp
	@echo "[$<]"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MM -MF $(patsubst %.o,%.d,$@) $<
	$(V)$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -o $@ $<

$(BUILD_DIR)/%.o: %.cc
	@echo "[$<]"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MM -MF $(patsubst %.o,%.d,$@) $<
	$(V)$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -o $@ $<


cleanrrf:
	-rm -f $(RRF_OBJS)  $(BUILD_DIR)/libRRFLibraries.a
	
cleancore:
	-rm -f $(CORE_OBJS) $(BUILD_DIR)/libLPCCore.a

cleanrrflibraries:
	-rm -f $(RRFLIBRARIES_OBJS) $(BUILD_DIR)/libRRFLibraries.a

clean: distclean

distclean:
	-rm -rf $(BUILD_DIR)/ 

.PHONY: all firmware clean distclean $(BUILD_DIR)/$(OUTPUT_NAME).elf
