NDK_TOOLCHAIN_VERSION := 4.9
APP_PLATFORM := android-14
APP_STL := c++_shared
APP_CPPFLAGS += -std=c++17
APP_ABI := armeabi-v7a
ifeq ($(BUILD_TYPE), debug)
   APP_OPTIM := debug
   APP_MODULES := sfml-activity-d AntFarm
else
   APP_OPTIM := release
   APP_MODULES := sfml-activity AntFarm
endif
APP_NAME := AntFarm
