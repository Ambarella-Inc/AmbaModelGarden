###########################################################
## amba.mk
##
## History:
##    2023/08/07 - [Monica Yang] created
##
## Copyright [2022] Ambarella International LP.
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##   http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
###########################################################

#DEPS(amba.mk) cv-ambamps-test(jobserver %): &&?board &&??ambcavalry-header &&??ambvideo-header \
		&&??libnnctrl &&??libcavalrymem &&??libvproc &&??libeazyai \
		&&??prebuild-opencv &&??prebuild-json-c \
		AMBA_SOC!=s6lm unselect

PACKAGE_NAME = cv-ambamps-test
PACKAGE_DEPS = generic-header ambcavalry-header ambvideo-header board
PACKAGE_DEPS += libnnctrl libcavalrymem libvproc libeazyai libeazyai-comm
PACKAGE_DEPS += opencv4 json-c

PREBUILD_OSS_DIR = $(ENV_TOP_DIR)/prebuild/oss/$(AMBA_CPU_ARCH)

BOARD_CONFIG ?= $(ENV_DEP_ROOT)/usr/include/board/board_config
include $(BOARD_CONFIG)

.PHONY: all clean install

all:
	@echo "Build $(PACKAGE_NAME) Done."

include $(ENV_MAKE_DIR)/inc.app.mk

################ Package ambamps ################

ifeq ($(AMBA_CAVALRY_ARCH),cavalry_v2)

test_ambamps-ldflags = $(patsubst %,-l%,nnctrl cavalry_mem json-c opencv_core opencv_imgproc opencv_imgcodecs)
test_ambamps-ldflags += -lpthread -lm -ldl \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/opencv/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libjpeg-turbo/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libpng/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/zlib/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/tbb/usr/lib \
		-Wl,-rpath-link=$(FAKEROOT_DIR)/usr/lib

test_ambamps-cflags := -Iambacnn -D AMBAMPS_CAVALRY_V2=1

test_ambamps-srcs = test_ambamps.cpp \
		ambamps_graph_ctrl.cpp \
		ambamps_json_parser.cpp

$(call set_flags,CFLAGS,$(test_ambamps-srcs),${test_ambamps-cflags})
$(eval $(call add-bin-build,test_ambamps,$(test_ambamps-srcs),$(test_ambamps-ldflags)))

endif

#####

test_ambamps_live-ldflags = $(patsubst %,-l%,nnctrl cavalry_mem json-c eazyai opencv_core opencv_imgproc opencv_imgcodecs)
test_ambamps_live-ldflags += -lpthread -lm -ldl \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/opencv/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libjpeg-turbo/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libpng/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/zlib/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/tbb/usr/lib \
		-Wl,-rpath-link=$(FAKEROOT_DIR)/usr/lib

test_ambamps_live-cflags := -Iambacnn

ifeq ($(AMBA_CAVALRY_ARCH),cavalry_v2)
test_ambamps_live-cflags += -D AMBAMPS_CAVALRY_V2=1
else ifeq ($(AMBA_CAVALRY_ARCH),cavalry_v3)
test_ambamps_live-cflags += -D AMBAMPS_CAVALRY_V3=1
endif

test_ambamps_live-srcs = test_ambamps_live.cpp \
		ambamps_graph_ctrl.cpp \
		ambamps_json_parser.cpp

$(call set_flags,CFLAGS,$(test_ambamps_live-srcs),$(test_ambamps_live-cflags))
$(eval $(call add-bin-build,test_ambamps_live,$(test_ambamps_live-srcs),$(test_ambamps_live-ldflags)))

all: $(BIN_TARGETS)

clean: clean_objs
	@-rm -f $(BIN_TARGETS)
	@echo "Clean $(PACKAGE_NAME) Done."

install: install_bins

%: $(OUT_PATH)/%
	@echo "Build $@ Done."
