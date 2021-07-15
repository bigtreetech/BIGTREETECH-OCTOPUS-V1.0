CORE_DIR = $(CORELPC_DIR)

CORE_SRC_DIRS = src src/LPC src/LPC/system/ExploreM3_lib src/LPC/SharedSPI src/LPC/SoftwarePWM
CORE_SRC_DIRS += src/LPC/ConfigurableUART src/LPC/variants/LPC src/LPC/ExploreM3 src/LPC/lpcopen/src
CORE_SRC_DIRS += src/LPC/mbed/platform src/LPC/mbed/usb src/LPC/mbed/usb/hal src/LPC/mbed/usb/TARGET_NXP 
CORE_SRC_DIRS += src/LPC/mbed/usb/USBDevice src/LPC/mbed/usb/USBPhy src/LPC/mbed/usb/USBSerial
CORE_SRC_DIRS += src/LPC/mbed/usb/utilities src/LPC/mbed src/LPC/ExploreM3/ExploreM3_lib
CORE_SRC_DIRS += src/LPC/Wire

CORE_SRC = $(addprefix $(CORE_DIR)/, $(CORE_SRC_DIRS))


#Find all c and c++ files for Core
CORE_OBJ_SRC_C    += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.c) )
CORE_OBJ_SRC_CXX    += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.cpp) )

#all object files for core
CORE_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_C)) $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_CXX))

#Find all headers
CORE_HEADERS = $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.h) )
#generate the paths that have headers files to include
CORE_HEADERS += $(CORE_DIR)/src/LPC/lpcopen/inc/ $(CORE_DIR)/src/LPC/mbed/

CORE_HEADERS_DIRS = $(call uniq,$(dir $(CORE_HEADERS)))
CORE_INCLUDES = $(addprefix -I, $(CORE_HEADERS_DIRS))
