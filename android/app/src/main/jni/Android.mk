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

ifeq ($(BUILD_TYPE), debug)
    LOCAL_STATIC_LIBRARIES := JsonBox_d
    LOCAL_SHARED_LIBRARIES := sfml-system-d
    LOCAL_SHARED_LIBRARIES += sfml-window-d
    LOCAL_SHARED_LIBRARIES += sfml-graphics-d
    LOCAL_SHARED_LIBRARIES += sfml-audio-d
    LOCAL_SHARED_LIBRARIES += sfml-network-d
    LOCAL_SHARED_LIBRARIES += sfml-activity-d
    LOCAL_SHARED_LIBRARIES += openal
    LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main-d

    LOCAL_LDLIBS += -llog
    LOCAL_CFLAGS += -DDEBUG
else
    LOCAL_STATIC_LIBRARIES := JsonBox
    LOCAL_SHARED_LIBRARIES := sfml-system
    LOCAL_SHARED_LIBRARIES += sfml-window
    LOCAL_SHARED_LIBRARIES += sfml-graphics
    LOCAL_SHARED_LIBRARIES += sfml-audio
    LOCAL_SHARED_LIBRARIES += sfml-network
    LOCAL_SHARED_LIBRARIES += sfml-activity
    LOCAL_SHARED_LIBRARIES += openal
    LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main
    LOCAL_CFLAGS += -DNDEBUG -O3
endif

LOCAL_CPP_FEATURES += rtti exceptions
LOCAL_CFLAGS += -Wall -std=c++17 -DANDROID

include $(BUILD_SHARED_LIBRARY)

$(call import-module, third_party/JsonBox)
$(call import-module, third_party/sfml)
