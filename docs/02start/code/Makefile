# 
# Copyright (c) 2016 Zubeen Tolani <ZeekHuge - zeekhuge@gmail.com>
# Copyright (c) 2017 Texas Instruments - Jason Kridner <jdk@ti.com>
# 

# TARGET must be defined as the file to be compiled without the .c.
# PRUN must be defined as the PRU number (0 or 1) to compile for.

# PRU_CGT environment variable points to the TI PRU compiler directory.
# PRU_SUPPORT points to pru-software-support-package.
# GEN_DIR points to where to put the generated files.

$(warning TARGET=$(TARGET), PRUN=$(PRUN), MODEL=$(MODEL))

PRU_CGT:=/usr/share/ti/cgt-pru
PRU_SUPPORT:=/usr/lib/ti/pru-software-support-package
GEN_DIR:=/tmp/pru$(PRUN)-gen

LINKER_COMMAND_FILE=AM335x_PRU.cmd
LIBS=--library=$(PRU_SUPPORT)/lib/rpmsg_lib.lib
INCLUDE=--include_path=$(PRU_SUPPORT)/include --include_path=$(PRU_SUPPORT)/include/am335x --include_path=../../common

STACK_SIZE=0x100
HEAP_SIZE=0x100

CFLAGS=-v3 -O2 --printf_support=minimal --display_error_number --endian=little --hardware_mac=on --obj_directory=$(GEN_DIR) --pp_directory=$(GEN_DIR) --asm_directory=$(GEN_DIR) -ppd -ppa --asm_listing --c_src_interlist -DAI=$(AI) # --absolute_listing

LFLAGS=--reread_libs --warn_sections --stack_size=$(STACK_SIZE) --heap_size=$(HEAP_SIZE) -m $(GEN_DIR)/$(TARGET).map

# Check which model
PRU_DIR="Invalid PRUN"
ifeq ($(MODEL), AI)
	AI=1
	CHIP=am57xx
	ifeq ($(PRUN),1_0)
		PRU_DIR=/sys/class/remoteproc/remoteproc0
	endif
	ifeq ($(PRUN),1_1)
		PRU_DIR=/sys/class/remoteproc/remoteproc1
	endif
	ifeq ($(PRUN),2_0)
		PRU_DIR=/sys/class/remoteproc/remoteproc2
	endif
	ifeq ($(PRUN),2_1)
		PRU_DIR=/sys/class/remoteproc/remoteproc3
	endif
else
	AI=0
	CHIP=am335x
	ifeq ($(PRUN),0)
		PRU_DIR=/sys/class/remoteproc/remoteproc1
	endif
	ifeq ($(PRUN),1)
		PRU_DIR=/sys/class/remoteproc/remoteproc2
	endif
endif

$(warning CHIP=$(CHIP), PRU_DIR=$(PRU_DIR))

all: stop install start
	@echo "MODEL   = $(MODEL)"
	@echo "CHIP    = $(CHIP)"
	@echo "PRUN    = $(PRUN)"
	@echo "PRU_DIR = $(PRU_DIR)"

stop:
	@echo "-    Stopping PRU $(PRUN)"
	@echo stop | tee $(PRU_DIR)/state || echo Cannot stop $(PRUN)

start:
	@echo "-    Starting PRU $(PRUN)"
	@echo start | tee $(PRU_DIR)/state
	@echo write_init_pins.sh
	@/var/lib/cloud9/common/write_init_pins.sh /lib/firmware/$(CHIP)-pru$(PRUN)-fw

install: $(GEN_DIR)/$(TARGET).out
	@echo '-	copying firmware file $(GEN_DIR)/$(TARGET).out to /lib/firmware/$(CHIP)-pru$(PRUN)-fw'
	@cp $(GEN_DIR)/$(TARGET).out /lib/firmware/$(CHIP)-pru$(PRUN)-fw

$(GEN_DIR)/$(TARGET).out: $(GEN_DIR)/$(TARGET).obj
	@echo 'LD	$^' 
	@lnkpru -i$(PRU_CGT)/lib -i$(PRU_CGT)/include $(LFLAGS) -o $@ $^ $(LINKER_COMMAND_FILE) --library=libc.a $(LIBS) $^

$(GEN_DIR)/$(TARGET).obj: $(TARGET).c
	@mkdir -p $(GEN_DIR)
	@echo 'CC	$<'
	@clpru --include_path=$(PRU_CGT)/include $(INCLUDE) $(CFLAGS) -D=PRUN=$(PRUN) -fe $@ $<

clean:
	@echo 'CLEAN	.    PRU $(PRUN)'
	@rm -rf $(GEN_DIR)
