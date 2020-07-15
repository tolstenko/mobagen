#pragma once

#ifdef ANDROID

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace mobagen {
  class AndroidAssetManager
  {
  public:
    static AAssetManager *getAssetManager(void);
  };
}

#endif
