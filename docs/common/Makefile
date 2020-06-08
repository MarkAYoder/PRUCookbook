#
# Optional definitions
#
# TARGET - executable to create (currently supports single .c source)
#          should have .<proc>(<n>) extension (lower case, check below for valid options)
#          without TARGET, as of now, we don't have any build targets
#          TODO: work with a list of targets, rather than a single file
# PRUN   - TBD

#
# Directories (external packages, etc.)
#
# COMMON points to where this primary Makefile and shell scripts live.
# PRU_CGT points to the TI PRU compiler directory.
# PRU_SUPPORT points to pru-software-support-package.
# C6X_CGT points to the TI C6X compiler directory.
# TIDL_API_DIR points to the TIDL API install directory.
# GEN_DIR points to where to build the binaries.
# MODEL is the board model (BeagleBoard.org_BeagleBone_AI, TI_AM335x_BeagleBone_Blue, etc.)
COMMON:=$(abspath $(lastword $(MAKEFILE_LIST)/..))
PRU_CGT:=/usr/share/ti/cgt-pru
PRU_SUPPORT:=/usr/lib/ti/pru-software-support-package
PRU_STARTERWARE:=/usr/share/ti/starterware
C6X_CGT:=/usr/share/ti/cgt-c6x
TIDL_API_DIR:=/usr/share/ti/tidl/tidl_api
GEN_DIR:=/tmp/cloud9-examples
MODEL:=$(shell cat /proc/device-tree/model | sed 's/ /_/g' | tr -d '\000')
# $(warning MODEL=$(MODEL),TARGET=$(TARGET),COMMON=$(COMMON))
$(warning MODEL=$(MODEL),TARGET=$(TARGET))

#
# Define PROC and build variables
#
# Arguments:
#   $@ - target name
#
# Variables defined:
#   CHIP - target system-on-chip (am57xx, am335x)
#   CHIP_REV - target system-on-chip with rev (am572x_2_0, am335x)
#   PROC - cpu type (arm, pru, c6x, etc.)
#   PRUN - identifier for target PRU core
#   PRU_DIR - control directory for the PRU
#   CC -
#   LD - 
#   LDFLAGS - 
#   CFLAGS -
#
# Depends on udev rules: https://github.com/beagleboard/customizations/blob/master/etc/udev/rules.d/86-remoteproc-noroot.rules
# Check which model
define target-to-proc =
 ifeq ($(suffix $(basename $(1))),.pru1_0)
  CHIP=am57xx
  CHIP_REV=am572x_2_0
  PRU_DIR=/dev/remoteproc/pruss1-core0
  PRUN=1_0
  PROC=pru
  EXE=.out
 else ifeq ($(suffix $(basename $(1))),.pru1_1)
  CHIP=am57xx
  CHIP_REV=am572x_2_0
  PRU_DIR=/dev/remoteproc/pruss1-core1
  PRUN=1_1
  PROC=pru
  EXE=.out
 else ifeq ($(suffix $(basename $(1))),.pru2_0)
  CHIP=am57xx
  CHIP_REV=am572x_2_0
  PRU_DIR=/dev/remoteproc/pruss2-core0
  PRUN=2_0
  PROC=pru
  EXE=.out
 else ifeq ($(suffix $(basename $(1))),.pru2_1)
  CHIP=am57xx
  CHIP_REV=am572x_2_0
  PRU_DIR=/dev/remoteproc/pruss2-core1
  PRUN=2_1
  PROC=pru
  EXE=.out
 else ifeq ($(suffix $(basename $(1))),.pru0)
  CHIP=am335x
  CHIP_REV=am335x
  PRU_DIR=/dev/remoteproc/pruss-core0
  PRUN=0
  PROC=pru
  EXE=.out
 else ifeq ($(suffix $(basename $(1))),.pru1)
  CHIP=am335x
  CHIP_REV=am335x
  PRU_DIR=/dev/remoteproc/pruss-core1
  PRUN=1
  PROC=pru
  EXE=.out
 else ifeq ($(suffix $(basename $(1))),.tidl)
  CHIP=am57xx
  PROC=tidl
  EXE=.so
 else
  PROC=arm
  EXE=.out
 endif
endef

#
# Arguments:
#   $@ - target name
# 
# Variables required:
#   CHIP - target system-on-chip (am57xx, am335x)
#   CHIP_REV - target system-on-chip with rev (am572x_2_0, am335x)
#   PROC - cpu type (arm, pru, c6x, etc.)
#   PRUN - identifier for target PRU core
#   PRU_DIR - control directory for the PRU
define proc-to-build-vars =
 ifeq ($(PROC),pru)
  LD=lnkpru -o
  LDFLAGS=--reread_libs --warn_sections --stack_size=0x100 --heap_size=0x100 -m $(basename $(1)).map \
   -i$(PRU_CGT)/lib -i$(PRU_CGT)/include $(COMMON)/$(CHIP)_$(PROC).cmd --library=libc.a \
   --library=$(PRU_SUPPORT)/lib/rpmsg_lib.lib
  CC=clpru -fe
  CFLAGS=--include_path=$(COMMON) --include_path=$(PRU_SUPPORT)/include \
   --include_path=$(PRU_SUPPORT)/include/$(CHIP_REV) \
   --include_path=$(PRU_STARTERWARE)/include --include_path=$(PRU_STARTERWARE)/include/hw \
   --include_path=$(PRU_CGT)/include -DCHIP=$(CHIP) -DCHIP_IS_$(CHIP) -DMODEL=$(MODEL) -DPROC=$(PROC) -DPRUN=$(PRUN) \
   -v3 -O2 --printf_support=minimal --display_error_number --endian=little --hardware_mac=on \
   --obj_directory=$(GEN_DIR) --pp_directory=$(GEN_DIR) --asm_directory=$(GEN_DIR) -ppd -ppa --asm_listing \
   --c_src_interlist
 else ifeq ($(PROC),tidl)
  LD=g++ -o
  LDFLAGS=-lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lopencv_imgproc -lopencv_core \
   $(TIDL_API_DIR)/tidl_api.a $(TIDL_API_DIR)/tidl_imgutil.a \
   -lTIOpenCL -locl_util -lpthread
  CXX=g++ -c -o
  CXXFLAGS=-DCHIP=$(CHIP) -DMODEL=$(MODEL) -DPROC=$(PROC) -fPIC -O3 -Wall -Werror -Wno-error=ignored-attributes \
   -I. -I$(TIDL_API_DIR)/inc -std=c++14 -I/usr/share/ti/opencl 
 else
  LD=gcc -o
  LDFLAGS=-lc -lm
  CC=gcc -c -o
  CFLAGS=-DCHIP=$(CHIP) -DMODEL=$(MODEL) -DPROC=$(PROC)
 endif
endef

#
#
#

ifneq ($(TARGET),)
$(eval $(call target-to-proc,$(TARGET).out))
# $(warning GEN_DIR=$(GEN_DIR),CHIP=$(CHIP),PROC=$(PROC),PRUN=$(PRUN),PRU_DIR=$(PRU_DIR),EXE=$(EXE))

all: stop install start
	@echo "MODEL   = $(MODEL)"
	@echo "PROC    = $(PROC)"
	@echo "PRUN    = $(PRUN)"
	@echo "PRU_DIR = $(PRU_DIR)"

# TODO: think about what we want to say if stop fails
stop:
ifneq ($(PRU_DIR),)
	@echo "-    Stopping PRU $(PRUN)"
	@echo stop > $(PRU_DIR)/state || echo Cannot stop $(PRUN)
endif

start:
ifneq ($(PRU_DIR),)
	@echo write_init_pins.sh
	@$(COMMON)/write_init_pins.sh /lib/firmware/$(CHIP)-pru$(PRUN)-fw
	@echo "-    Starting PRU $(PRUN)"
	@echo start > $(PRU_DIR)/state
else ifeq ($(PROC),tidl)
	ti-mct-heap-check -c
	sudo mjpg_streamer -i "input_opencv.so -r 640x480 -d /dev/$(shell fgrep -v vpe /sys/class/video4linux/video*/name | perl -ne '/\/(video\d+)\/name/ && print $$1') \
	--filter ./$(TARGET)$(EXE)" -o "output_http.so -p 8090 -w /usr/share/mjpg-streamer/www"
else
	./$(TARGET)$(EXE)
endif

install: $(GEN_DIR)/$(TARGET)$(EXE)
ifneq ($(PRU_DIR),)
	@echo '-	copying firmware file $(GEN_DIR)/$(TARGET).out to /lib/firmware/$(CHIP)-pru$(PRUN)-fw'
	@cp $(GEN_DIR)/$(TARGET)$(EXE) /lib/firmware/$(CHIP)-pru$(PRUN)-fw
else
	@cp $(GEN_DIR)/$(TARGET)$(EXE) ./$(TARGET)$(EXE)
endif
endif

%.out: $(GEN_DIR)/%.out
	@echo 'CP	$^'
	@cp $^ $@

%.so: $(GEN_DIR)/%.so
	@echo 'CP	$^'
	@cp $^ $@

# TODO: look up how Makefiles typically break down the output file specification
# $(warning CHIP=$(CHIP),PROC=$(PROC))
# $(warning CC=$(CC),LD=$(LD),CFLAGS=$(CFLAGS),LDFLAGS=$(LDFLAGS))
$(GEN_DIR)/%.out: $(GEN_DIR)/%.o
	@mkdir -p $(GEN_DIR)
	@echo 'LD	$^'
	$(eval $(call target-to-proc,$@))
	$(eval $(call proc-to-build-vars,$@))
	@$(LD) $@ $^ $(LDFLAGS) 

$(GEN_DIR)/%.so: $(GEN_DIR)/%.o
	@mkdir -p $(GEN_DIR)
	@echo 'LD	$^'
	$(eval $(call target-to-proc,$@))
	$(eval $(call proc-to-build-vars,$@))
	@$(LD) $@ -shared $^ $(LDFLAGS) 

$(GEN_DIR)/%.o: %.asm
	@mkdir -p $(GEN_DIR)
	@echo 'CC	$^'
	$(eval $(call target-to-proc,$@))
	$(eval $(call proc-to-build-vars,$@))
	@$(CC) $@ $^ $(CFLAGS)

$(GEN_DIR)/%.o: %.c
	@mkdir -p $(GEN_DIR)
	@echo 'CC	$^'
	$(eval $(call target-to-proc,$@))
	$(eval $(call proc-to-build-vars,$@))
	@$(CC) $@ $^ $(CFLAGS)

$(GEN_DIR)/%.o: %.cpp
	@mkdir -p $(GEN_DIR)
	@echo 'CXX	$^'
	$(eval $(call target-to-proc,$@))
	$(eval $(call proc-to-build-vars,$@))
	@$(CXX) $@ $^ $(CXXFLAGS)

clean:
	@echo 'CLEAN'
	@rm -rf $(GEN_DIR)
