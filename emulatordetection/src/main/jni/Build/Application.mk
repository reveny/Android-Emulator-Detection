APP_ABI := arm64-v8a armeabi-v7a x86 x86_64
APP_STL := c++_static
APP_OPTIM := release
APP_SUPPORT_FLEXIBLE_PAGE_SIZES := true

ifeq ($(NDK_DEBUG),1)
    APP_CPPFLAGS += -DDEBUG_BUILD=1
else
    APP_CPPFLAGS += -DDEBUG_BUILD=0
endif