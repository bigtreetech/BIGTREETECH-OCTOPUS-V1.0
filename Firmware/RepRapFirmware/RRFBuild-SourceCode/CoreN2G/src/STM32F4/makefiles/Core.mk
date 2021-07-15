CORE_DIR = $(CORESTM_DIR)


#Core
CORE_SRC_DIRS  = src src/STM32F4 src/STM32F4/usb src/STM32F4/usb/cdc
CORE_SRC_DIRS += src/STM32F4/system src/STM32F4/system/STM32F4xx src/STM32F4/system/Middlewares/ST/STM32_USB_Device_Library/Core/Inc src/STM32F4/system/Middlewares/ST/STM32_USB_Device_Library/Core/Src 
CORE_SRC_DIRS += src/STM32F4/system/Drivers/CMSIS/Device/ST/STM32F4xx/Include src/STM32F4/system/Drivers/CMSIS/Device/ST/STM32F4xx/Source
CORE_SRC_DIRS += src/STM32F4/system/Drivers/STM32F4xx_HAL_Driver/Inc src/STM32F4/system/Drivers/STM32F4xx_HAL_Driver/Src
CORE_SRC_DIRS += src/STM32F4/system/CMSIS/CMSIS/Core/Include src/STM32F4/system/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc
CORE_SRC_DIRS += src/STM32F4/variants/STM32F446 src/STM32F4/ConfigurableUART src/STM32F4/SharedSPI src/STM32F4/PWM src/STM32F4/SDIO src/STM32F4/CRC32

CORE_SRC = $(CORE_DIR) $(addprefix $(CORE_DIR)/, $(CORE_SRC_DIRS))
CORE_INCLUDES = $(addprefix -I, $(CORE_SRC))

#Find all c and c++ files for Core
CORE_OBJ_SRC_C    += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.c))
CORE_OBJ_SRC_CXX   += $(foreach src, $(CORE_SRC), $(wildcard $(src)/*.cpp))
CORE_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_C)) $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CORE_OBJ_SRC_CXX))
CORE_OBJS += $(BUILD_DIR)/CoreN2G/src/STM32F4/startup_stm32yyxx.o
