#include "Asset.hpp"

#include <string>

namespace mobagen {
  Asset::Asset(const std::string &fileName) {
    m_ioStream = new File(fileName);
    m_fileSize = m_ioStream->fileSize();
    m_buffer = new char[m_fileSize + 1];
    m_buffer[m_fileSize] = '\0';
  }

  Asset::~Asset(void) {
    delete[] m_buffer;
    delete m_ioStream;
  }

  const char *Asset::read(void) const {
    m_ioStream->read(m_buffer, sizeof(char), m_fileSize);

    return m_buffer;
  }

  File *Asset::getIOStream(void) const {
    return m_ioStream;
  }
}