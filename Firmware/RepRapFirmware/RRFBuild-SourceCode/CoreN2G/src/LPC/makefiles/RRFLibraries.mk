#---RRF Libraries----
RRF_LIBRARY_SRC_BASE = $(RRFLIBRARIES_DIR)/src
RRF_LIBRARY_SRC_DIRS = General Math RTOSIface

#  Find the c and cpp source files
RRF_LIBRARY_SRC = $(RRF_LIBRARY_SRC_BASE) $(addprefix $(RRF_LIBRARY_SRC_BASE)/, $(RRF_LIBRARY_SRC_DIRS))
RRFLIBRARIES_OBJ_SRC_C      += $(foreach src, $(RRF_LIBRARY_SRC), $(wildcard $(src)/*.c) ) 
RRFLIBRARIES_OBJ_SRC_CXX   += $(foreach src, $(RRF_LIBRARY_SRC), $(wildcard $(src)/*.cpp) )
#RRF_INCLUDES += $(addprefix -I, $(RRF_LIBRARY_SRC))
RRFLIBRARIES_INCLUDES = -I$(RRFLIBRARIES_DIR)/src

RRFLIBRARIES_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(RRFLIBRARIES_OBJ_SRC_C)) $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(RRFLIBRARIES_OBJ_SRC_CXX))
#end RRF Libraries

