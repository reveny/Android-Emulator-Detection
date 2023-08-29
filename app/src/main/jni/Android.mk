LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := emulatordetector

# Code optimization
LOCAL_CFLAGS := -Wno-error=format-security -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fexceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fexceptions -fpermissive
#LOCAL_LDFLAGS += -Wl, --strip-all, --gc-sections, -llog
LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := Main.cpp \

LOCAL_LDLIBS := -llog -landroid -lz -lEGL

include $(BUILD_SHARED_LIBRARY)
