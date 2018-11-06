LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := external-jni
LOCAL_SRC_FILES := libs/$(TARGET_ARCH_ABI)/libexternal-jni.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := internal-jni
LOCAL_SRC_FILES := internal.cpp
LOCAL_SHARED_LIBRARIES := external-jni
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS := -llog
include $(BUILD_SHARED_LIBRARY)

