LOCAL_PATH := $(call my-dir)/..
include $(CLEAR_VARS)

LOCAL_MODULE    := emulatordetector

# Code optimization
LOCAL_CPPFLAGS += -fexceptions -Werror -Wextra -Wpedantic -Wshadow -Wconversion -Wnull-dereference -Wdeclaration-after-statement -Wno-shorten-64-to-32 -Wno-variadic-macros -s -std=c++20

ifeq ($(NDK_DEBUG),0)
    $(warning Building native library in release mode)

    LOCAL_CPPFLAGS += -O1
    LOCAL_CPPFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
    LOCAL_CPPFLAGS += -fno-unwind-tables -fno-asynchronous-unwind-tables -fomit-frame-pointer

    LOCAL_LDFLAGS += -Wl,--strip-all -Wl,--exclude-libs,ALL
endif

LOCAL_SRC_FILES := Main.cpp \
                   EmulatorDetection.cpp \

LOCAL_LDLIBS := -llog -landroid

include $(BUILD_SHARED_LIBRARY)
