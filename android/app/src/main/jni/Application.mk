NDK_TOOLCHAIN_VERSION := 4.9
APP_PLATFORM := android-14
APP_STL := c++_shared
APP_CPPFLAGS += -std=c++17
APP_ABI := $(TARGET_ARCH_ABI)
ifeq ($(BUILD_TYPE), debug)
   APP_OPTIM := debug
   APP_DEBUG := true
   APP_MODULES := sfml-activity-d AntFarm
else
   APP_OPTIM := release
   APP_DEBUG := false
   APP_MODULES := sfml-activity AntFarm
endif
APP_NAME := AntFarm
