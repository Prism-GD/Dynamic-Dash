#include <memory>
#include <jni.h>
#include <android/log.h>
#include "AppDelegate.h"
namespace { std::unique_ptr<AppDelegate> app; }
void cocos_android_app_init(JNIEnv*){__android_log_print(ANDROID_LOG_DEBUG,"DynamicDash","Starting game");app.reset(new AppDelegate());}