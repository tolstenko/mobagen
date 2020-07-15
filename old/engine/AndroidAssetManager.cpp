#ifdef ANDROID

#include "AndroidAssetManager.hpp"

static AAssetManager* NativeAssetManager = 0;

extern "C"
{
   JNIEXPORT void JNICALL Java_org_libsdl_app_SDLActivity_createAssetManager(JNIEnv* env, jclass clazz, jobject assetManager)
   {
      NativeAssetManager = AAssetManager_fromJava(env, assetManager);
   }
};

namespace mobagen {
  AAssetManager *AndroidAssetManager::getAssetManager(void)
  {
    return NativeAssetManager;
  }
}

#endif
