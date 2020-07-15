#pragma once

#include "File.hpp"

namespace mobagen {
  class Asset {
  public:
    Asset(const std::string &fileName);

    ~Asset(void);

    const char *read(void) const;

    File *getIOStream(void) const;

  private:
    char *m_buffer;
    File *m_ioStream;
    size_t m_fileSize;
  };
}