#-------------------------------------------------------------
# Makefile for InfluxDB HTTP Client
#-------------------------------------------------------------

.DEFAULT_GOAL := this

ifneq ($(BUILD),"RELEASE")
        export BUILD = "DEBUG"
endif

COMMON_SRC := .
COMMON_INC := ../inc
COMMON_LIB := ../lib
COMMON_CFG := ../cfg
COMMON_BUILD := ../build

curr_dir := $(shell pwd)
MODULE := influxdb_client

THIS_BUILD := $(COMMON_BUILD)/$(MODULE)_build
CFG = $(COMMON_CFG)/$(MODULE)_config.txt
TARGET = $(COMMON_BUILD)/dbclient_test
TARGET_LIB = $(COMMON_BUILD)/lib$(MODULE)

BUILDDIRS = common $(MODULE)


CC = g++

INCLUDES = -I$(COMMON_INC) -I/usr/local/include 

LIBS = -L$(COMMON_LIB) -L/usr/local/lib

SUBDIRS = 

EXTDIRS = ../common 

SOURCES = $(shell echo *.cc)
LIB_SOURCES = $(filter-out dbclient_test.cc,$(SOURCES))

HEADERS = $(shell echo *.h)

OBJECTS = $(SOURCES:%.cc=$(THIS_BUILD)/%.o)
LIB_OBJECTS = $(LIB_SOURCES:%.cc=$(THIS_BUILD)/%.o)


ALL_OBJECTS1 = $(addprefix $(COMMON_BUILD)/, $(BUILDDIRS) )
ALL_OBJECTS = $(addsuffix _build/*.o, $(ALL_OBJECTS1) )



CFLAGS = -fPIC -Wall -Wextra -std=c++14 

LDFLAGS = 

ifeq ($(BUILD),"RELEASE")
	CFLAGS += -O2 -DNDEBUG
	LDFLAGS += -s 
else ## DEBUG
	CFLAGS += -O0 -g -DDEBUG
endif



$(LIB_OBJECTS): $(THIS_BUILD)/%.o : %.cc %.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@  
	
.PHONY: target_lib
target_lib: $(TARGET_LIB).so $(TARGET_LIB).a
$(TARGET_LIB).so: $(LIB_OBJECTS)
	$(CC) $(LDFLAGS) -shared -o $@ $(LIB_OBJECTS)  
	cp -f $(TARGET_LIB).so $(COMMON_LIB)
$(TARGET_LIB).a: $(LIB_OBJECTS)
	ar rvs -o $@ $(LIB_OBJECTS)
	cp -f $(TARGET_LIB).a $(COMMON_LIB)


.PHONY: target_exec
target_exec: $(TARGET)
$(TARGET) : dbclient_test.cc
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) -l$(MODULE) -o $@ dbclient_test.cc 
	
		
	
define fullBuild
	@echo "Building $(curr_dir) - full build "
	mkdir -p $(THIS_BUILD)
	@for subdir in $(SUBDIRS); do \
	    echo "Making all in $(curr_dir)/$$subdir"; \
	    $(MAKE) -C $(curr_dir)/$$subdir all;\
	done
	echo $(LIB_OBJECTS)
	$(MAKE) target_lib
	$(MAKE) target_exec
	@# post-build steps
	cp $(CFG) $(COMMON_BUILD)/
endef

define extbuild
	@echo "Building $(curr_dir) - full build "
	@for extdir in $(EXTDIRS); do \
	    echo "Making all in $$extdir"; \
	    $(MAKE) -C $$extdir all;\
	done
	mkdir -p $(THIS_BUILD)
	@for subdir in $(SUBDIRS); do \
	    echo "Making all in $(curr_dir)/$$subdir"; \
	    $(MAKE) -C $(curr_dir)/$$subdir all;\
	done
	echo $(LIB_OBJECTS)
	$(MAKE) target_lib
	$(MAKE) target_exec
	@# post-build steps
	cp $(CFG) $(COMMON_BUILD)/
endef

this: tree
tree:	
	$(call fullBuild)
	
	
all:
	$(call extbuild)

clean:
	rm -rf $(THIS_BUILD) $(TARGET) $(COMMON_BUILD)/*$(MODULE)*.*
	
	
