# Android.mk
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := android_gdnative
LOCAL_CPPFLAGS := -std=c++14
LOCAL_CPP_FEATURES := rtti exceptions
LOCAL_LDLIBS := -llog 

LOCAL_SRC_FILES := \
ARVRInterface.cpp godot_gearvr.cpp GodotCalls.cpp OS.cpp

LOCAL_SRC_FILES := /home/paritosh97/Desktop/GearVR/oculus_mobile_vr/VrApi/Libs/Android/armeabi-v7a/Debug/

LOCAL_EXPORT_C_INCLUDES := /home/paritosh97/Desktop/GearVR/oculus_mobile_vr/VrApi/Include/

LOCAL_C_INCLUDES := \
/home/paritosh97/Desktop/Godot/godot/modules/gdnative/include /usr/local/java/jdk1.8.0_171/include /usr/local/java/jdk1.8.0_171/include/linux 

include $(BUILD_SHARED_LIBRARY) 
