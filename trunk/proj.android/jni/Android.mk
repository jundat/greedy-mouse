LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
           ../../Classes/AppDelegate.cpp  \
     ../../Classes/Achievement.cpp  \
     ../../Classes/AchievementManager.cpp  \
     ../../Classes/AchievementScene.cpp  \
     ../../Classes/AudioManager.cpp  \
     ../../Classes/BoardManager.cpp  \
     ../../Classes/CampaignScene.cpp  \
     ../../Classes/CreditsScene.cpp  \
     ../../Classes/DataManager.cpp  \
     ../../Classes/EffectManager.cpp  \
     ../../Classes/FileOperation.cpp  \
     ../../Classes/Global.cpp  \
     ../../Classes/Line.cpp  \
     ../../Classes/LoseDialog.cpp  \
     ../../Classes/MainGameScene.cpp  \
     ../../Classes/Map.cpp  \
     ../../Classes/MapItem.cpp  \
     ../../Classes/MenuScene.cpp  \
     ../../Classes/SplashScene.cpp  \
     ../../Classes/TutScene.cpp  \
     ../../Classes/WinDialog.cpp  \


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)