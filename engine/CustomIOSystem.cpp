#include "CustomIOSystem.hpp"
#include "CustomIOStream.hpp"

//#include <string>
//#include <stdio.h>
// #include <unistd.h>

namespace mobagen {
  CustomIOSystem::CustomIOSystem(void) {}

  CustomIOSystem::~CustomIOSystem(void) {}

  bool CustomIOSystem::ComparePaths(const char *one, const char *second) const {
    return strcmp(one, second) == 0;
  }

  bool CustomIOSystem::Exists(const char *pFile) const {
#ifndef ANDROID
    // TODO: FIX THIS IN WINDOWS
    //if(access(("../assets/" + std::string(pFile)).c_str(), F_OK) != -1) {
    //  return true;
    //} else {
    //  return false;
    //}
    return true;
#else
    return true;
#endif
  }

  char CustomIOSystem::getOsSeparator(void) const {
    return '/';
  }

  Assimp::IOStream *CustomIOSystem::Open(const char *pFile, const char *pMode) {
    return new CustomIOStream(pFile, pMode);
  }

  void CustomIOSystem::Close(Assimp::IOStream *pFile) {
    delete pFile;
  }
}