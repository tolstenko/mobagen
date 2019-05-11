#pragma once

#include "File.hpp"

#include <assimp/IOStream.hpp>

namespace mobagen {
  class FileCustom : public Assimp::IOStream {
    friend class FileSystemHelper;
	friend class FileSystem;

  protected:
    // Constructor protected for private usage by CustomIOSystem
    FileCustom(const char *pFile, const char *pMode);

  public:
    ~FileCustom(void);

    size_t Read(void *pvBuffer, size_t pSize, size_t pCount);

    size_t Write(const void *pvBuffer, size_t pSize, size_t pCount);

    aiReturn Seek(size_t pOffset, aiOrigin pOrigin);

    size_t Tell(void) const;

    size_t FileSize(void) const;

    void Flush(void);

  private:
    File *m_iostream;
  };
}