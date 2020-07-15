#pragma once

#include <fstream>

#ifdef ANDROID
  #include "AndroidAssetManager.hpp"
#endif

namespace mobagen {
  enum origin {
    Origin_SET,
    Origin_CUR,
    Origin_END
  };

  class File {
  public:
    File(const std::string &fileName);

    ~File(void);

    size_t read(void *pvBuffer, size_t pSize, size_t pCount);

    size_t write(const void *pvBuffer, size_t pSize, size_t pCount);

    bool seek(size_t pOffset, origin pOrigin);

    size_t tell(void) const;

    size_t fileSize(void) const;

    void flush(void);

    std::string getFileName(void);

  private:
    std::string m_fileName;

#ifndef ANDROID
    std::fstream *m_file;
#else
    AAsset *m_file;
#endif
  };
}