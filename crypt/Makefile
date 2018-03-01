#----------------------------------------------------------------
# Root Makefile for nvest.ai analytics source code
#----------------------------------------------------------------

.DEFAULT_GOAL := all

ifneq ($(BUILD),"RELEASE")
        export BUILD = "DEBUG"
endif


COMMON_ROOT := $(shell pwd)
COMMON_INC := ${COMMON_ROOT}/inc
COMMON_BUILD := ${COMMON_ROOT}/build
COMMON_DIST := ${COMMON_ROOT}/dist

curr_dir := $(shell pwd)


SUBDIRS = common ohlcv_fmt

EXECS = ohlcv_fmt
ALL_EXECS = $(addprefix $(COMMON_BUILD)/, $(EXECS) )


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
	rm -rf $(COMMON_INC)/*.h  $(COMMON_BUILD)/* $(COMMON_DIST)/*
	
cleanlog:
cleanlogs:
	rm -rf $(COMMON_BUILD)/*.log
	
install:
	rm -f $(COMMON_DIST)/*
	cp -f $(ALL_EXECS)  $(COMMON_BUILD)/*_config.txt $(COMMON_DIST)

	


