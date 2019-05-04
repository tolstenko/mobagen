#include "FileSystemHelper.hpp"
#include "FileSystem.hpp"

namespace mobagen {
  FileSystemHelper::FileSystemHelper(void) {}
  FileSystemHelper::~FileSystemHelper(void) {}

  bool FileSystemHelper::Exists(const char* pFile) const
  {
	  return FileSystem::Exists(pFile);
  }

  bool FileSystemHelper::ComparePaths(const char *one, const char *second) const
  {
    return FileSystem::ComparePaths(one,second);
  }

  char FileSystemHelper::getOsSeparator() const
  {
    return FileSystem::PathSeparator();
  }

  std::vector<std::string> FileSystemHelper::ListDirectory(std::string path)
  {
      return FileSystem::ListDirectory(path);
  }

  Assimp::IOStream *FileSystemHelper::Open(const char *pFile, const char *pMode)
  {
    return FileSystem::Open(pFile,pMode);
  }

  void FileSystemHelper::Close(Assimp::IOStream *pFile)
  {
    return FileSystem::Close(pFile);
  }

  bool FileSystemHelper::IsDirectory(std::string path)
  {
    return FileSystem::IsDirectory(path);
  }
}