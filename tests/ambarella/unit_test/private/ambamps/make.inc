################################################################################
## make.inc
##
## History:
##    2022/05/20 - [Monica Yang] Created
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
################################################################################


ifeq ($(BUILD_AMBARELLA_UNIT_TESTS_AMBAMPS), y)

LOCAL_PATH	:= $(call my-dir)

################################################

include $(CLEAR_VARS)
LOCAL_TARGET    := test_ambamps
LOCAL_SRCS      := $(LOCAL_PATH)/test_ambamps.cpp \
		$(LOCAL_PATH)/ambamps_graph_ctrl.cpp \
		$(LOCAL_PATH)/ambamps_json_parser.cpp

LOCAL_CFLAGS    := -I$(PREBUILD_OSS_DIR)/opencv/include/opencv4 \
		-I$(PREBUILD_OSS_DIR)/opencv/include \
		-I$(AMB_TOPDIR)/packages/cavalry_mem/inc \
		-I$(AMB_TOPDIR)/packages/nnctrl/$(AMBA_CAVALRY_ARCH)/inc \
		-I$(AMB_TOPDIR)/packages/nnctrl/inc \
		-I$(AMB_TOPDIR)/include/cavalry/$(AMBA_CAVALRY_ARCH) \
		-I$(AMB_TOPDIR)/include/cavalry \
		-I$(PREBUILD_OSS_DIR)/json-c/include \
		-I$(LOCAL_PATH)/ambacnn

LOCAL_LIBS      := libnnctrl.so libcavalry_mem.so

LOCAL_LDFLAGS   := -lpthread -lm -ldl \
		-L$(PREBUILD_OSS_DIR)/opencv/usr/lib \
		-lopencv_core -lopencv_imgproc -lopencv_imgcodecs \
		-L$(PREBUILD_OSS_DIR)/json-c/usr/lib -ljson-c \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/opencv/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libjpeg-turbo/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libpng/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/zlib/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/tbb/usr/lib \
		-Wl,-rpath-link=$(FAKEROOT_DIR)/usr/lib

include $(BUILD_APP)

.PHONY: $(LOCAL_TARGET)
$(LOCAL_TARGET): $(LOCAL_MODULE)
	@mkdir -p $(UNIT_TEST_PATH)/
	@cp -dpRf $< $(UNIT_TEST_PATH)/
	@echo "Build $@ Done."

$(call add-target-into-build, $(LOCAL_TARGET))

#############################################

ifeq ($(BUILD_AMBAMPS_LIVE),y)

include $(CLEAR_VARS)
LOCAL_TARGET    := test_ambamps_live
LOCAL_SRCS      := $(LOCAL_PATH)/test_ambamps_live.cpp \
		$(LOCAL_PATH)/ambamps_graph_ctrl.cpp \
		$(LOCAL_PATH)/ambamps_json_parser.cpp

LOCAL_CFLAGS    := -I$(PREBUILD_OSS_DIR)/opencv/include/opencv4 \
		-I$(PREBUILD_OSS_DIR)/opencv/include \
		-I$(AMB_TOPDIR)/packages/cavalry_mem/inc \
		-I$(AMB_TOPDIR)/packages/nnctrl/$(AMBA_CAVALRY_ARCH)/inc \
		-I$(AMB_TOPDIR)/packages/nnctrl/inc \
		-I$(AMB_TOPDIR)/include/cavalry/$(AMBA_CAVALRY_ARCH) \
		-I$(AMB_TOPDIR)/include/cavalry \
		-I$(AMB_TOPDIR)/packages/eazyai/inc \
		-I$(PREBUILD_OSS_DIR)/json-c/include \
		-I$(LOCAL_PATH)/ambacnn

LOCAL_LIBS      := libnnctrl.so libcavalry_mem.so libeazyai.so

LOCAL_LDFLAGS   := -lpthread -lm -ldl \
		-L$(PREBUILD_OSS_DIR)/opencv/usr/lib \
		-lopencv_core -lopencv_imgproc -lopencv_imgcodecs \
		-L$(PREBUILD_OSS_DIR)/json-c/usr/lib -ljson-c \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/opencv/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libjpeg-turbo/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libpng/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/zlib/usr/lib \
		-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/tbb/usr/lib \
		-Wl,-rpath-link=$(FAKEROOT_DIR)/usr/lib

include $(BUILD_APP)

.PHONY: $(LOCAL_TARGET)
$(LOCAL_TARGET): $(LOCAL_MODULE)
	@mkdir -p $(UNIT_TEST_PATH)/
	@cp -dpRf $< $(UNIT_TEST_PATH)/
	@echo "Build $@ Done."

$(call add-target-into-build, $(LOCAL_TARGET))

endif

################################################

endif

