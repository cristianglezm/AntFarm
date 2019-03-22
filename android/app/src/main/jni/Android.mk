LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := AntFarm

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../../include

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../../../src/*.cpp)
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../../../src/*/*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../../../src/*/*/*.cpp)
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_STATIC_LIBRARIES := JsonBox
LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network

LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main

APP_OPTIM := release
LOCAL_LDLIBS += -llog
LOCAL_CPP_FEATURES += rtti exceptions
LOCAL_CFLAGS += -Wall -std=c++11 -DANDROID -DUSE_MAKE_UNIQUE

include $(BUILD_SHARED_LIBRARY)

$(call import-module, third_party/JsonBox)
$(call import-module, third_party/sfml)
