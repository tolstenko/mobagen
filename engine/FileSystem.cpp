#include "FileSystem.hpp"
#include "FileCustom.hpp"


#if !defined(_WIN32) && !defined(_WIN64) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
/* UNIX-style OS. ------------------------------------------- */
#include <unistd.h>
#if defined(_POSIX_VERSION)
/* POSIX compliant */
#include <sys/types.h>
#include <sys/dir.h>
#endif
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#include "direntwin.h"
#endif

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

    DIR* dirp = opendir(path.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL)
      contents.push_back(dp->d_name);
    closedir(dirp);

    return contents;
  }

  bool FileSystem::IsDirectory(std::string path) {
    struct stat s;
    if( stat(path.c_str(),&s) == 0 )
    {
      if( s.st_mode & S_IFDIR )
        return true; // dir
//      else if( s.st_mode & S_IFREG )
//        return false; // file
      else
        return false; //something else
    }
    else
      return false;
  }
}