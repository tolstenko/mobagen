#include "FileCustom.hpp"

#include <string>

namespace mobagen {
  FileCustom::FileCustom(const char *pFile, const char *pMode) {
    m_iostream = new File(std::string(pFile));
  }

  FileCustom::~FileCustom(void) {
    delete m_iostream;
  }

  size_t FileCustom::Read(void *pvBuffer, size_t pSize, size_t pCount) {
    return m_iostream->read(pvBuffer, pSize, pCount);
  }

  size_t FileCustom::Write(const void *pvBuffer, size_t pSize, size_t pCount) {
    return m_iostream->write(pvBuffer, pSize, pCount);
  }

  aiReturn FileCustom::Seek(size_t pOffset, aiOrigin pOrigin) {
    switch (pOrigin) {
      case aiOrigin_SET:
        return m_iostream->seek(pOffset, Origin_SET) ? AI_SUCCESS : AI_FAILURE;
        break;

      case aiOrigin_CUR:
        return m_iostream->seek(pOffset, Origin_CUR) ? AI_SUCCESS : AI_FAILURE;
        break;

      case aiOrigin_END:
        return m_iostream->seek(pOffset, Origin_END) ? AI_SUCCESS : AI_FAILURE;
        break;
    }
  }

  size_t FileCustom::Tell(void) const {
    return m_iostream->tell();
  }

  size_t FileCustom::FileSize(void) const {
    return m_iostream->fileSize();
  }

  void FileCustom::Flush(void) {
    m_iostream->flush();
  }
}