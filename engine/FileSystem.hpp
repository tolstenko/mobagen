#pragma once

#include <assimp/IOSystem.hpp>

namespace mobagen {
  class FileSystem : public Assimp::IOSystem {
  public:
    FileSystem(void);

    ~FileSystem(void);

    bool ComparePaths(const char *one, const char *second) const;

    bool Exists(const char *pFile) const;

    char getOsSeparator(void) const;

    std::vector<std::string> ListDirectory(std::string path);

    bool IsFile(std::string path);

    Assimp::IOStream *Open(const char *pFile, const char *pMode);

    void Close(Assimp::IOStream *pFile);
  };
}