#---RepRapFirmware---
RRF_SRC_BASE  = $(REPRAPFIRMWARE_DIR)/src


RRF_SRC_DIRS = FilamentMonitors GCodes GCodes/GCodeBuffer Heating 
RRF_SRC_DIRS += Movement Movement/BedProbing Movement/Kinematics 
RRF_SRC_DIRS += Storage Libraries/sha1 Hardware/SharedSpi Comms Platform PrintMonitor
RRF_SRC_DIRS += Heating/Sensors Fans ObjectModel Endstops Hardware Tools
RRF_SRC_DIRS += Display Display/ST7920 GPIO bossa

#LPC RRF Addons
RRF_SRC_DIRS += targets/LPC targets/common targets/LPC/MCP4461 targets/LPC/FatFS targets/common/FatFS targets/common/Fans
RRF_SRC_DIRS += targets/LPC/Hardware

#networking support?
ifeq ($(NETWORK), ETHERNET)
	RRF_SRC_DIRS += Networking targets/LPC/Networking targets/LPC/Networking/RTOSPlusTCPEthernet
else ifeq ($(NETWORK), ESP8266WIFI) 
	RRF_SRC_DIRS += Networking Networking/ESP8266WiFi targets/LPC/Networking/ESP8266WiFi 
else ifeq ($(NETWORK), SBC)
	RRF_SRC_DIRS += Linux
	RRF_SRC_DIRS += targets/common/NoNetwork
else
	RRF_SRC_DIRS += targets/common/NoNetwork
endif

#TMC22XX support?
ifeq ($(TMC22XX), true)
	RRF_SRC_DIRS += targets/LPC/Movement/StepperDrivers targets/common/Movement/StepperDrivers
endif

#Find the c and cpp source files
RRF_SRC = $(RRF_SRC_BASE) $(addprefix $(RRF_SRC_BASE)/, $(RRF_SRC_DIRS))
RRF_OBJ_SRC_C	   += $(foreach src, $(RRF_SRC), $(wildcard $(src)/*.c) ) 
RRF_OBJ_SRC_CXX   += $(foreach src, $(RRF_SRC), $(wildcard $(src)/*.cpp) )
ifeq ($(TMC22XX), true)
	RRF_OBJ_SRC_CXX += $(RRF_SRC_BASE)/Movement/StepperDrivers/DriverMode.cpp
else ifeq ($(TMC51XX), true)
	RRF_OBJ_SRC_CXX += $(RRF_SRC_BASE)/Movement/StepperDrivers/DriverMode.cpp
endif

RRF_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(RRF_OBJ_SRC_C)) $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(RRF_OBJ_SRC_CXX))


RRF_INCLUDES = $(addprefix -I, $(RRF_SRC))
RRF_INCLUDES += -I$(RRF_SRC_BASE)/Libraries/
RRF_INCLUDES += -I$(RRF_SRC_BASE)/targets/

#If building ESP8266 WIFI we only need to add the include from DuetWifiSocketServer as it has a file needed to compile RRF 
ifeq ($(NETWORK), ESP8266WIFI)
	RRF_INCLUDES += -IDuetWiFiSocketServer/src/include
endif

#end RRF

#Libc and libcpp in RRF
RRFLIBC_SRC_DIRS = libcpp libc
RRFLIBC_SRC = $(addprefix $(RRF_SRC_BASE)/, $(RRFLIBC_SRC_DIRS))
RRFLIBC_OBJ_SRC_C	  += $(foreach src, $(RRFLIBC_SRC), $(wildcard $(src)/*.c) ) 
RRFLIBC_OBJ_SRC_CXX   += $(foreach src, $(RRFLIBC_SRC), $(wildcard $(src)/*.cpp) )
RRFLIBC_OBJ_SRC_CC    += $(foreach src, $(RRFLIBC_SRC), $(wildcard $(src)/*.cc) )

RRFLIBC_INCLUDES = $(addprefix -I, $(RRF_SRC))

RRFLIBC_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(RRFLIBC_OBJ_SRC_C)) $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(RRFLIBC_OBJ_SRC_CXX))
RRFLIBC_OBJS += $(patsubst %.cc,$(BUILD_DIR)/%.o,$(RRFLIBC_OBJ_SRC_CC))


#


