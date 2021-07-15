
#RTOS location
RTOS_SRC = $(FREERTOS_DIR)/src
RTOS_INCLUDE = $(RTOS_SRC)/include/
RTOS_SRC_PORTABLE = $(RTOS_SRC)/portable/GCC/ARM_CM4F

RTOSPLUS_SRC = $(FREERTOS_DIR)
RTOS_CONFIG_INCLUDE = CoreN2G/src/STM32F4/FreeRTOSConfig



#RTOS Sources (selected dirs only)
RTOS_CORE_SRC    += $(RTOS_SRC) $(RTOS_SRC_PORTABLE)
RTOS_CORE_OBJ_SRC_C  += $(foreach src, $(RTOS_CORE_SRC), $(wildcard $(src)/*.c) )
#RTOS Dynamic Memory Management
#RTOS_CORE_OBJ_SRC_C  += $(RTOS_SRC)/portable/MemMang/heap_5.c

CORE_OBJS += $(patsubst %.c,$(BUILD_DIR)/%.o,$(RTOS_CORE_OBJ_SRC_C))

#RTOS Includes
CORE_INCLUDES   += -I$(RTOS_INCLUDE) -I$(RTOS_SRC_PORTABLE)
CORE_INCLUDES   += -I$(RTOS_CONFIG_INCLUDE)


#RTOS-Plus (selected dirs only)
#RTOS +TCP
#RTOSPLUS_TCP_SRC = $(RTOSPLUS_SRC)/FreeRTOS-Plus-TCP
#RTOSPLUS_TCP_INCLUDE = $(RTOSPLUS_TCP_SRC)/include/

RTOSPLUS_CORE_SRC    += $(RTOSPLUS_TCP_SRC) $(RTOS_SRC_PORTABLE)
RTOSPLUS_CORE_OBJ_SRC_C  += $(foreach src, $(RTOSPLUS_CORE_SRC), $(wildcard $(src)/*.c) )
#** RTOS+TCP Portable**

#(portable) Select Buffer Management (only enable one)
#RTOSPLUS_CORE_OBJ_SRC_C  += $(RTOSPLUS_TCP_SRC)/portable/BufferManagement/BufferAllocation_1.c #Static Ethernet Buffers
#RTOSPLUS_CORE_OBJ_SRC_C  += $(RTOSPLUS_TCP_SRC)/portable/BufferManagement/BufferAllocation_2.c #Dynamic Ethernet Buffers

#(portable) Compiler Includes (GCC)
#RTOSPLUS_TCP_INCLUDE += -I$(RTOSPLUS_TCP_SRC)/portable/Compiler/GCC

#(portable) NetworkInterface
#RTOSPLUS_TCP_INCLUDE += -I$(RTOSPLUS_TCP_SRC)/portable/NetworkInterface/include
#RTOSPLUS_TCP_NI_SRC    += $(RTOSPLUS_TCP_SRC)/portable/NetworkInterface/Common
#RTOSPLUS_TCP_NI_SRC    += $(RTOSPLUS_TCP_SRC)/portable/NetworkInterface/LPC17xx 
#RTOSPLUS_CORE_OBJ_SRC_C  += $(foreach src, $(RTOSPLUS_TCP_NI_SRC), $(wildcard $(src)/*.c) )


ifeq ($(NETWORK), ETHERNET)
	CORE_OBJS += $(patsubst %.c,$(BUILD_DIR)/%.o,$(RTOSPLUS_CORE_OBJ_SRC_C))
	#RTOS+TCP Includes
	CORE_INCLUDES   += -I$(RTOSPLUS_TCP_INCLUDE) -I$(RTOSPLUS_TCP_INCLUDE)	
endif
