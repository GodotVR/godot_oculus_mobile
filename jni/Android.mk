# Android.mk
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

# define some more paths
# need to make some of these switchable
# note also that godot_headers currently contains the headers for 3.0 so adjust this path to your 3.1 godot installation!
# I am talking to Karroffel to get 3.1 headers in a branch so we can simply point our submodule to that branch
SDK_PATH := $(LOCAL_PATH)/../../../ovr_sdk_mobile_1.9.0
GODOT_HEADERS_PATH := $(LOCAL_PATH)/../godot_headers
JDK_PATH := /Program Files/Java/jdk1.8.0_151

# and configure our build
LOCAL_MODULE := android_gdnative
LOCAL_CPPFLAGS := -std=c++14
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_LDLIBS := -llog

APP_PLATFORM := android-18
NDK_LIBS_OUT := $(LOCAL_PATH)/demo/addons/godot_gearvr/bin/

LOCAL_SRC_FILES := \
ARVRInterface.cpp godot_gearvr.cpp GodotCalls.cpp OS.cpp

# VrApi libraries (this breaks for me)
LOCAL_STATIC_LIBRARIES := $(SDK_PATH)/VrApi/Libs/Android/armeabi-v7a/Debug/libvrapi.so

# VrApi Headers
LOCAL_EXPORT_C_INCLUDES := $(SDK_PATH)/VrApi/Include/

# gdnative and java headers
LOCAL_C_INCLUDES := \
. \
$(GODOT_HEADERS_PATH) \
$(SDK_PATH)/VrApi/Include/ \
$(JDK_PATH)/include \
$(JDK_PATH)/include/linux 

include $(BUILD_SHARED_LIBRARY) 
