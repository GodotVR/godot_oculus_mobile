# Android.mk
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# define some more paths
# need to make some of these switchable
# note also that godot_headers currently contains the headers for 3.0 so adjust this path to your 3.1 godot installation!
# I am talking to Karroffel to get 3.1 headers in a branch so we can simply point our submodule to that branch

SDK_PATH := ../ovr_sdk_mobile_1.14.0
GODOT_HEADERS_PATH := ../godot/modules/gdnative/include/
JDK_PATH := $(JAVA_HOME)

# Include VrApi
LOCAL_MODULE := vrapi
LOCAL_SRC_FILES := ../$(SDK_PATH)/VrApi/Libs/Android/armeabi-v7a/Debug/libvrapi.so
LOCAL_EXPORT_C_INCLUDES := $(SDK_PATH)/VrApi/Include/
include $(PREBUILT_SHARED_LIBRARY)

# and configure our build
LOCAL_MODULE := android_gdnative
LOCAL_CPPFLAGS := -std=c++14
LOCAL_CPP_FEATURES := rtti exceptions

LOCAL_LDLIBS := -llog -lGLESv2


LOCAL_SRC_FILES := \
ARVRInterface.cpp godot_gearvr.cpp GodotCalls.cpp OS.cpp

# gdnative and java headers
LOCAL_C_INCLUDES := \
$(GODOT_HEADERS_PATH) $(JDK_PATH)/include $(JDK_PATH)/include/linux

LOCAL_SHARED_LIBRARIES = vrapi


include $(BUILD_SHARED_LIBRARY)
