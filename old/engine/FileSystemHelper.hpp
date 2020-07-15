#pragma once

#include <assimp/IOSystem.hpp>

namespace mobagen {
  class FileSystemHelper : public Assimp::IOSystem {
  public:
    FileSystemHelper(void);

    ~FileSystemHelper(void);

	bool Exists(const char* pFile) const override;

    bool ComparePaths(const char *one, const char *second) const;

    char getOsSeparator(void) const;

    std::vector<std::string> ListDirectory(std::string path);

    bool IsDirectory(std::string path);

    Assimp::IOStream *Open(const char *pFile, const char *pMode);

    void Close(Assimp::IOStream *pFile);
    
  };
}