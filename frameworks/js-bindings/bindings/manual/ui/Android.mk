LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := jsb_ui_static

LOCAL_MODULE_FILENAME := libcocos2dxjsbui

LOCAL_SRC_FILES := jsb_cocos2dx_ui_manual.cpp \
                   ../../auto/jsb_cocos2dx_ui_auto.cpp

LOCAL_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_EXPORT_CFLAGS := -DCOCOS2D_JAVASCRIPT

LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/../../../cocos2d-x/extensions \
                    $(LOCAL_PATH)/../../../cocos2d-x/cocos/ui

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)
                            
LOCAL_WHOLE_STATIC_LIBRARIES := spidermonkey_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_jsb_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,external/spidermonkey/prebuilt/android)
$(call import-module,bindings)
$(call import-module,ui)
