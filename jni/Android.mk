# Android.mk
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

SDK_PATH := ../ovr_sdk_mobile
GODOT_HEADERS_PATH := ../godot_headers
JDK_PATH := $(JAVA_HOME)

# Include VrApi
LOCAL_MODULE := vrapi
LOCAL_SRC_FILES := $(SDK_PATH)/VrApi/Libs/Android/armeabi-v7a/Debug/libvrapi.so
LOCAL_EXPORT_C_INCLUDES := $(SDK_PATH)/VrApi/Include/
include $(PREBUILT_SHARED_LIBRARY)

# and configure our build
include $(CLEAR_VARS)
LOCAL_MODULE := libgodot_ovr
LOCAL_CPPFLAGS := -std=c++14
LOCAL_CPP_FEATURES := rtti exceptions

LOCAL_LDLIBS := -llog -landroid -lGLESv3 -lEGL

LOCAL_SRC_FILES := \
  ../src/ARVRInterface.cpp ../src/godot_ovr.cpp ../src/GodotCalls.cpp ../src/OS.cpp ../src/ovrFramebuffer.cpp ../src/ovrCommon.cpp

# gdnative and java headers
LOCAL_C_INCLUDES := \
$(GODOT_HEADERS_PATH) $(JDK_PATH)/include $(JDK_PATH)/include/linux

LOCAL_SHARED_LIBRARIES = vrapi

include $(BUILD_SHARED_LIBRARY)
