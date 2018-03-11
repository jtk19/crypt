#----------------------------------------------------------------
# Root Makefile for nvest.ai analytics source code
#----------------------------------------------------------------

.DEFAULT_GOAL := all

ifneq ($(BUILD),"RELEASE")
        export BUILD = "DEBUG"
endif


COMMON_ROOT := $(shell pwd)
COMMON_INC := ${COMMON_ROOT}/inc
COMMON_LIB := ${COMMON_ROOT}/lib
COMMON_BUILD := ${COMMON_ROOT}/build
COMMON_DIST := ${COMMON_ROOT}/dist

curr_dir := $(shell pwd)


SUBDIRS = common influxdb_client ohlcv_fmt

EXECS = ohlcv_fmt

LIBS = influxdb_client	## exclude test programs

ALL_EXECS = $(addprefix $(COMMON_BUILD)/, $(EXECS) )

LIBS1 = $(addprefix $(COMMON_BUILD)/lib, $(LIBS) )
ALL_LIBS = $(addsuffix .so, $(LIBS1) ) 
ALL_LIBS += $(addsuffix .a, $(LIBS1) )


define fullBuild
	mkdir -p ${COMMON_INC} ${COMMON_LIB} ${COMMON_BUILD}  
	@for subdir in $(SUBDIRS); do \
	    echo "Making all in $(curr_dir)/$$subdir"; \
	    $(MAKE) -C $(curr_dir)/$$subdir tree;\
	done
endef


all:  
	$(call fullBuild)
	

clean:
	rm -rf $(COMMON_INC)/*.h  ${COMMON_LIB}/* $(COMMON_BUILD)/* $(COMMON_DIST)/*
	
cleanlog:
cleanlogs:
	rm -rf $(COMMON_BUILD)/*.log
	
	
install:
	rm -f $(COMMON_DIST)/*
	cp -f $(ALL_EXECS)  $(COMMON_DIST)
	cp -f $(ALL_LIBS)  $(COMMON_DIST)
	cp -f $(COMMON_BUILD)/*_config.txt $(COMMON_DIST)
	
	


