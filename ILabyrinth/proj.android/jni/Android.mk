LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/Scene/MenuScene.cpp \
                   ../../Classes/Scene/PickMapScene.cpp \
                   ../../Classes/Scene/GameScene.cpp \
                   ../../Classes/Scene/GameEndScene.cpp \
                   ../../Classes/Utility/VisibleRect.cpp \
                   ../../Classes/Layer/PickMapLayer.cpp \
                   ../../Classes/CustomNode/CharacterSprite.cpp \
                   ../../Classes/CustomNode/PickMapScrollView.cpp \
                   ../../Classes/Sprite/LevelSprite.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Scene \
					$(LOCAL_PATH)/../../Classes/Utility \
					$(LOCAL_PATH)/../../Classes/Layer \
					$(LOCAL_PATH)/../../Classes/CustomNode \
					$(LOCAL_PATH)/../../Classes/Sprite
					
LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,extensions)
$(call import-module,editor-support/cocosbuilder)
$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
