OUTPUT_DIR = _build
SUBDIRS=$(filter-out _build common,$(shell ls -l | grep ^d | awk '{print $$9}'))
export VERSION=$(shell git describe --always --dirty || echo 'unknown')
export BUILDTIME=$(shell date +"%Y_%m_%d")
export FILE_VERSION = $(BUILDTIME)-$(VERSION)

ifdef OUTPUT_DIRECTORY
OUTPUT_DIR = $(OUTPUT_DIRECTORY)
endif
ifndef RELEASE_DIR
RELEASE_DIR = $(OUTPUT_DIR)
endif

.PHONY: clean all package usb merge_setting dist_clean

package: all
	@echo "package"
usb: 
	@echo use make all to build your release firmware.
merge_setting: 
	@echo use make all to build your release firmware.

all: $(SUBDIRS)
	@echo "all"

# 当目标是一个列表时, 相当于循环, 用$@代表每个目标
# make -C dir 读入指定dir下的makefile
$(SUBDIRS): $(OUTPUT_DIR)
	@echo "subdirs @{SUBDIRS}"
	@-mkdir -p $(OUTPUT_DIR)/$@ 
	@make -C $@ package OUTPUT_DIRECTORY=../$(OUTPUT_DIR)/$@ NRF_PACKAGE_NAME=../$(RELEASE_DIR)/$(BUILD_PREFIX)-$@-nrf52-$(FILE_VERSION).zip BUILD_PREFIX=$(BUILD_PREFIX)-$@
	@make -C $@ usb OUTPUT_DIRECTORY=../$(OUTPUT_DIR)/$@ OUTPUT_BIN=../$(RELEASE_DIR)/$(BUILD_PREFIX)-$@-ch554-$(FILE_VERSION).bin BUILD_PREFIX=$(BUILD_PREFIX)-$@
	@make -C $@ merge_setting OUTPUT_DIRECTORY=../$(OUTPUT_DIR)/$@ NRF_SIGN_HEX_NAME=../$(RELEASE_DIR)/$(BUILD_PREFIX)-$@-nrf52-$(FILE_VERSION).hex BUILD_PREFIX=$(BUILD_PREFIX)-$@
	@echo "parameter ${@}"
	@echo "OUTPUT_DIRECTORY ${@}"
	@echo "NRF_PACKAGE_NAME ${@}"
	@echo "BUILD_PREFIX ${@}"
	@echo "OUTPUT_BIN ${@}"

$(OUTPUT_DIR):
	@-mkdir -p $(OUTPUT_DIR)

dist_clean: 
	-rm -r $(OUTPUT_DIR)/*/

clean:
	-rm -r $(OUTPUT_DIR)


# $@表示参数内容
# make默认执行第一个目标 
# 一个目标（target）就构成一条规则。目标通常是文件名，指明Make命令所要构建的对象
# 除了文件名，目标还可以是某个操作的名字，这称为"伪目标"（phony target）。
# 但是，如果当前目录中，正好有一个文件叫做clean，那么这个命令不会执行。因为Make发现clean文件已经存在，就认为没有必要重新构建了，就不会执行指定的rm命令。
# 为了避免这种情况，可以明确声明clean是"伪目标"，写法 .PHONY: clean


