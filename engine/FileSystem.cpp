#include "FileSystem.hpp"
#include "FileCustom.hpp"

#include <iterator>
//#include <experimental/filesystem>
//namespace fs = std::experimental::filesystem;

namespace mobagen {
  FileSystem::FileSystem(void) {}

  FileSystem::~FileSystem(void) {}

  bool FileSystem::ComparePaths(const char *one, const char *second) const {
    return strcmp(one, second) == 0;
  }

  bool FileSystem::Exists(const char *pFile) const {
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

  char FileSystem::getOsSeparator(void) const {
    return '/';
  }

  Assimp::IOStream *FileSystem::Open(const char *pFile, const char *pMode) {
    return new FileCustom(pFile, pMode);
  }

  void FileSystem::Close(Assimp::IOStream *pFile) {
    delete pFile;
  }

  std::vector<std::string> FileSystem::ListDirectory(std::string path) {
    std::vector<std::string> contents;

//    for(auto& p: fs::directory_iterator(path))
//      contents.emplace_back(p.path().string());

    return contents;
  }

  bool FileSystem::IsFile(std::string path) {
//    return fs::is_regular_file(path);
  return false;
  }
}