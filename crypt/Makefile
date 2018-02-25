#----------------------------------------------------------------
# Root Makefile for SAIC ADAS & Autonomous Driving Source Code
#----------------------------------------------------------------

.DEFAULT_GOAL := all

ifneq ($(BUILD),"RELEASE")
        export BUILD = "DEBUG"
endif


COMMON_ROOT := $(shell pwd)
COMMON_INC := ${COMMON_ROOT}/inc
COMMON_BUILD := ${COMMON_ROOT}/build

curr_dir := $(shell pwd)


SUBDIRS = common ohlcv_fmt


define fullBuild
	mkdir -p ${COMMON_INC} ${COMMON_BUILD}  
	@for subdir in $(SUBDIRS); do \
	    echo "Making all in $(curr_dir)/$$subdir"; \
	    $(MAKE) -C $(curr_dir)/$$subdir tree;\
	done
endef


all:  
	$(call fullBuild)
	

		
clean:
	rm -rf $(COMMON_INC)/*.h  $(COMMON_BUILD)/*
	
cleanlog:
cleanlogs:
	rm -rf $(COMMON_BUILD)/*.log
	

	


