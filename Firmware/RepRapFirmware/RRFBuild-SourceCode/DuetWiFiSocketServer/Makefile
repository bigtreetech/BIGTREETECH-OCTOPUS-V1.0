all: DuetWiFiServer.bin

# Choose one to define build SDK
#NONO_SDK ?=V2
NONO_SDK ?=V3

# Enable debug?
DEBUG ?=-DDEBUG

# Build for Duet or LPC
HOSTSYS ?=-DLPCRRF -DEXTENDED_LISTEN

OBJ = \
        $(patsubst %.cpp,$(BUILD)/%.o,$(wildcard src/*.cpp)) \
        $(patsubst %.c,$(BUILD)/%.o,$(wildcard src/*.c)) \

SDKBASE ?= ../Arduino
SDK ?= $(SDKBASE)/tools/sdk
SDKTOOLS ?= $(SDKBASE)/tools
TOOLS ?= $(SDKTOOLS)/xtensa-lx106-elf/bin/xtensa-lx106-elf-
BUILD ?= Build
LIB ?= $(SDK)/lib

ifeq ($(NONO_SDK),V2)
    $(info  - Building for NONO SDK V2.X $(HOSTSYS) $(DEBUG))
    NONOSDK ?= $(LIB)/NONOSDK22x_190703
    CORELIB ?= CoreESP8266
else
    $(info  - Building for NONO SDK V3.X $(HOSTSYS) $(DEBUG))
    NONOSDK ?= $(LIB)/NONOSDK302_200122
    CORELIB ?= CoreESP8266V3
endif

CPP_BUILD_FLAGS += -Wall -c -Os -g -Wpointer-arith -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -mtext-section-literals -falign-functions=4 -MMD -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti

BUILD_FLAGS += -Wall -c -Os -g -Wpointer-arith -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -mtext-section-literals -falign-functions=4 -MMD -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti

BUILD_DEFINES += -D__ets__ -DICACHE_FLASH -U__STRICT_ANSI__ -DF_CPU=80000000L -DARDUINO=10606 -DARDUINO_ESP8266_ESP12 -DARDUINO_ARCH_ESP8266 -DESP8266 -DLWIP_OPEN_SRC -DTCP_MSS=1 -DLWIP_FEATURES=1 -DLWIP_IPV6=0 -DLWIP_MDNS_RESPONDER=1 $(HOSTSYS) $(DEBUG)

BUILD_INCLUDES= -I$(SDKBASE)/cores/esp8266 -I$(SDKBASE)/variants/nodemcu/ -I$(SDKBASE)/libraries/EEPROM -I$(SDKBASE)/libraries/DNSServer/src -I$(SDKBASE)/libraries/ESP8266WiFi/src -I$(SDK)/include -I$(SDK)/lwip2/include

V ?= 0
ifeq ($(V), 0)
VERBCPP = @echo "C++  $@";
VERBC = @echo "C  $@";
VERBAR = @echo "AR $@";
VERBAS = @echo "AS $@";
VERBLD = @echo "LD $@";
else
VERBCPP =
VERBC =
VERBAR =
VERBAS = 
VERBLD =
endif

CPP                     = $(VERBCPP) $(TOOLS)g++
CPP_BUILD_FLAGS                 += -std=c++11 -DTRUE=true -DFALSE=false
CC                      = $(VERBC) $(TOOLS)gcc
BUILD_FLAGS             += -std=gnu99

AR                      = $(VERBAR) $(TOOLS)ar
AS                      = $(VERBAS) $(TOOLS)as
OC                      = $(TOOLS)objcopy
OD                      = $(TOOLS)objdump
LD			= $(VERBLD) $(TOOLS)g++

$(BUILD)/%.h:
	@mkdir -p $(dir $@)
	@touch $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(BUILD_FLAGS) $(BUILD_DEFINES) $(BUILD_INCLUDES) $< -o $@

$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPP_BUILD_FLAGS) $(BUILD_DEFINES) $(BUILD_INCLUDES) $< -o $@

$(BUILD)/%.o: %.S
	@mkdir -p $(dir $@)
	$(AS) --text-section-literals $< -o $@


DuetWiFiSocketServer.elf: $(OBJ) src/ld/local.eagle.app.v6.common.ld
	$(LD) -DXXX=1 -nostdlib -L$(NONOSDK) -L$(SDK)/libc/xtensa-lx106-elf/lib -L$(LIB) -Lsrc/ld -L$(SDK)/ld -T eagle.flash.4m2m.ld -Wl,--no-check-sections -u call_user_start -u _printf_float -u _scanf_float -Wl,-static -Wl,--gc-sections -Wl,-wrap,system_restart_local -Wl,-wrap,spi_flash_read -Wl,-Map,$(BUILD)/DuetWiFiSocketServer.map -o $(BUILD)/DuetWiFiSocketServer.elf -Wl,--start-group $(LIB)/heap.o $(OBJ) -l$(CORELIB) -llwip2-1460-feat -lhal -lphy -lpp -lnet80211 -lwpa -lcrypto -lmain -lwps -laxtls -lespnow -lsmartconfig -lairkiss -lwpa2 -lstdc++ -lm -lc -lgcc -Wl,--end-group 


DuetWiFiServer.bin: DuetWiFiSocketServer.elf
	python $(SDKTOOLS)/elf2bin.py -e $(SDKBASE)/bootloaders/eboot/eboot.elf -a $(BUILD)/DuetWiFiSocketServer.elf -o $(BUILD)/DuetWiFiServer.bin -m dio -f 40 -s 4M -p $(SDKTOOLS)/xtensa-lx106-elf/bin/

clean:
	rm -rf $(BUILD)
