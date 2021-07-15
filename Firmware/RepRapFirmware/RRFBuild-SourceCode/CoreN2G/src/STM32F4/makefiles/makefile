PROCESSOR = STM32F4


BUILD_DIR ?= ./build
FREERTOS_DIR ?= ./FreeRTOS
REPRAPFIRMWARE_DIR ?= ./RepRapFirmware
RRFLIBRARIES_DIR ?= ./RRFLibraries
CORESTM_DIR ?= ./CoreN2G

BUILD ?= Debug

NETWORK ?= ESP8266WIFI

TMC22XX ?= true
TMC51XX ?= true

STARTUP_DELAY ?= -DSTARTUP_DELAY=10000

#Comment out to show compilation commands (verbose)
V=@

$(info Building RepRapFirmware for STM32F4 based boards:)

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

$(info  - MAKE_DIR: $(MAKE_DIR))
include $(MAKE_DIR)/Core.mk
include $(MAKE_DIR)/FreeRTOS.mk
include $(MAKE_DIR)/RRFLibraries.mk
include $(MAKE_DIR)/RepRapFirmware.mk

ifeq ($(BUILD),Debug)
	DEBUG_FLAGS = -Os -g -DSTM32_DEBUG $(STARTUP_DELAY)
        $(info - Build: Debug) 
else
	DEBUG_FLAGS = -Os
        $(info - Build: Release)
endif
	

#Linker script to avoid built in Bootloader
LINKER_SCRIPT_BASE = $(CORE_DIR)/src/STM32F4/variants/STM32F446/ldscript



#Path to the linker Script
LINKER_SCRIPT  = $(LINKER_SCRIPT_BASE).ld
$(info  - Linker Script used: $(LINKER_SCRIPT))


#Flags common for Core in c and c++
#FLAGS  = -D__$(PROCESSOR)__ -D_XOPEN_SOURCE -DENABLE_UART3 -DSTM32F4 -DSTM32F446xx -DSTM32F40_41xxx -DSTM32F446_5ZX -DSTM32F4xx
FLAGS  = -D__$(PROCESSOR)__ -D_XOPEN_SOURCE -DSTM32F4 -DSTM32F446xx -DSTM32F40_41xxx -DSTM32F446_5ZX -DSTM32F4xx
# UART configuration
FLAGS  += -DHAVE_HWSERIAL1 -DHAVE_HWSERIAL3

#lpcopen Defines
FLAGS += -DCORE_M4
#RTOS + enable mods to RTOS+TCP for RRF
FLAGS += -DRTOS -DFREERTOS_USED -DUSBCON -DUSBD_USE_CDC -DUSBD_VID=0x0483 -DTIM_IRQ_PRIO=13 -DUSB_PRODUCT=\"STM32F446ZG\" -DVECT_TAB_OFFSET=0x8000 -DHSE_VALUE=12000000
FLAGS += -DDEVICE_USBDEVICE=1 -DTARGET_STM32F4 -DARDUINO_ARCH_STM32 -DHAL_UART_MODULE_ENABLED -DHAL_PCD_MODULE_ENABLED
FLAGS +=  -Wall -c -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mcpu=cortex-m4 -mthumb -ffunction-sections -fdata-sections
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
endif
ifeq ($(TMC51XX), true)
        $(info  - Smart Drivers: TMC51XX)
        FLAGS += -DSUPPORT_TMC51xx
endif

CFLAGS   = $(FLAGS) -std=gnu11 -fgnu89-inline -Dnoexcept=
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

coreSTM: $(BUILD_DIR)/core.a

$(BUILD_DIR)/libSTMCore.a: $(CORE_OBJS)
	$(V)$(AR) rcs $@ $(CORE_OBJS)
	@echo "\nBuilt STMCore\n"
	
$(BUILD_DIR)/libRRFLibraries.a: $(RRFLIBRARIES_OBJS)
	$(V)$(AR) rcs $@ $(RRFLIBRARIES_OBJS)
	@echo "\nBuilt RRF Libraries\n"

#$(BUILD_DIR)/$(OUTPUT_NAME).elf: $(BUILD_DIR)/src/CoreMain.o $(BUILD_DIR)/libSTMCore.a $(BUILD_DIR)/libRRFLibraries.a $(RRFLIBC_OBJS)
#	$(V)$(LD) -L$(BUILD_DIR)/ -L$(CORE_DIR)/variants/BIGTREE_SKR_PRO_1v1/ -L$(CORE_DIR)/CMSIS/CMSIS/DSP/Lib/GCC --specs=nano.specs -Os -Wl,--warn-section-align -Wl,--fatal-warnings -fmerge-all-constants -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mcpu=cortex-m4 -mthumb -T$(LINKER_SCRIPT) -Wl,-Map,$(BUILD_DIR)/$(OUTPUT_NAME).map -o $(BUILD_DIR)/$(OUTPUT_NAME).elf -Wl,--cref -Wl,--check-sections -Wl,--gc-sections,--relax -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols -Wl,--defsym=LD_MAX_SIZE=1048576 -Wl,--defsym=LD_MAX_DATA_SIZE=196608 -Wl,--defsym=LD_FLASH_OFFSET=0x0 -Wl,--start-group $(BUILD_DIR)/src/CoreMain.o -lSTMCore -lRRFLibraries -larm_cortexM4l_math -lc -lm -lgcc -lstdc++ -Wl,--end-group

$(BUILD_DIR)/$(OUTPUT_NAME).elf: $(BUILD_DIR)/libSTMCore.a $(BUILD_DIR)/libRRFLibraries.a $(RRFLIBC_OBJS) $(RRF_OBJS)
	@echo "\nCreating $(OUTPUT_NAME).bin"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(LD) -L$(BUILD_DIR)/ -L$(CORE_DIR)/src/STM32F4/variants/STM32F446/ -L$(CORE_DIR)/src/STM32F4/system/CMSIS/CMSIS/DSP/Lib/GCC --specs=nosys.specs -Xlinker -z -Xlinker muldefs -Os -Wl,--fatal-warnings -fmerge-all-constants -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mcpu=cortex-m4 -mthumb -T$(LINKER_SCRIPT) -Wl,-Map,$(BUILD_DIR)/$(OUTPUT_NAME).map -o $(BUILD_DIR)/$(OUTPUT_NAME).elf -Wl,--cref -Wl,--check-sections -Wl,--gc-sections,--relax -Wl,--entry=Reset_Handler -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-unresolved-symbols -Wl,--defsym=LD_MAX_SIZE=1048576 -Wl,--defsym=LD_MAX_DATA_SIZE=196608 -Wl,--defsym=LD_FLASH_OFFSET=0x0 -Wl,--start-group $(RRFLIBC_OBJS) -lSTMCore $(RRF_OBJS) -lRRFLibraries -larm_cortexM4l_math -lc -lm -lgcc -lstdc++ -Wl,--end-group
	$(V)$(OBJCOPY) --strip-unneeded -O binary $(BUILD_DIR)/$(OUTPUT_NAME).elf $(BUILD_DIR)/$(OUTPUT_NAME).bin
	$(V)$(SIZE) $(BUILD_DIR)/$(OUTPUT_NAME).elf
	-@$(MAKE_DIR)/staticMemStats.sh $(BUILD_DIR)/$(OUTPUT_NAME)
	
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

$(BUILD_DIR)/$(CORESTM_DIR)/%.o : $(CORESTM_DIR)/%.cpp
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

$(BUILD_DIR)/$(CORESTM_DIR)/%.o: $(CORESTM_DIR)/%.S
	@echo "[$<]"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(CXX) -x assembler-with-cpp $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MM -MF $(patsubst %.o,%.d,$@) $<
	$(V)$(CXX) -x assembler-with-cpp $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -o $@ $<

$(BUILD_DIR)/%.o: %.S
	@echo "[$<]"
	$(V)$(MKDIR) $(dir $@)
	$(V)$(CXX) -x assembler-with-cpp $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -MM -MF $(patsubst %.o,%.d,$@) $<
	$(V)$(CXX) -x assembler-with-cpp $(CXXFLAGS) $(DEFINES) $(INCLUDES) -MMD -MP -o $@ $<

cleanrrf:
	-rm -f $(RRF_OBJS)  $(BUILD_DIR)/libRRFLibraries.a
	
cleancore:
	-rm -f $(CORE_OBJS) $(BUILD_DIR)/libLPCCore.a

cleanrrflibraries:
	-rm -f $(RRFLIBRARIES_OBJS) $(BUILD_DIR)/libRRFLibraries.a

clean: distclean

distclean:
	-rm -rf $(BUILD_DIR)/ 

upload:
	ST-LINK_CLI.exe -c SWD -P "$(BUILD_DIR)/firmware.bin" 0x8008000 -ClrBP -NoPrompt -Rst -Run

.PHONY: all firmware clean distclean $(BUILD_DIR)/$(OUTPUT_NAME).elf
