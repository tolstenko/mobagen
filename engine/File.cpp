#include "File.hpp"
#include "FileSystem.hpp"

namespace mobagen {
  File::File(const std::string &fileName) {
    m_fileName = fileName;

    if(m_fileName.find(std::string("assets")+FileSystem::PathSeparator())==0)
      m_fileName.erase(0,7);

#ifdef ANDROID
    m_file = AAssetManager_open(AndroidAssetManager::getAssetManager(), m_fileName.c_str(), AASSET_MODE_UNKNOWN);
#elif EMSCRIPTEN
    m_file = new std::fstream(ASSET_DIR + m_fileName, std::ifstream::binary | std::fstream::in | std::fstream::out);
#else
	m_file = new std::fstream((std::string("assets") + FileSystem::PathSeparator() + m_fileName).c_str(), std::ifstream::binary | std::fstream::in | std::fstream::out);
#endif
  }

  File::~File(void) {
#ifndef ANDROID
    delete m_file;
#else
    AAsset_close(m_file);
#endif
  }

  size_t File::read(void *pvBuffer, size_t pSize, size_t pCount) {
#ifndef ANDROID
    m_file->read((char *) pvBuffer, pSize * pCount);
    return m_file->gcount();
#else
    return AAsset_read(m_file, (char *)pvBuffer, pSize * pCount);
#endif
  }

  size_t File::write(const void *pvBuffer, size_t pSize, size_t pCount) {
#ifndef ANDROID
    m_file->write((char *) pvBuffer, pSize * pCount);
    return pSize * pCount;
#else
    return 0;
#endif
  }

  bool File::seek(size_t pOffset, origin pOrigin) {
    switch (pOrigin) {
      case Origin_SET:
#ifndef ANDROID
        m_file->seekg(pOffset, std::ios::beg);
#else
        AAsset_seek(m_file, pOffset, std::ios::beg);
#endif
        break;

      case Origin_CUR:
#ifndef ANDROID
        m_file->seekg(pOffset, std::ios::cur);
#else
        AAsset_seek(m_file, pOffset, std::ios::cur);
#endif
        break;

      case Origin_END:
#ifndef ANDROID
        m_file->seekg(pOffset, std::ios::end);
#else
        AAsset_seek(m_file, pOffset, std::ios::end);
#endif
        break;
    }

#ifndef ANDROID
    if (!m_file->good()) {
      return false;
    }
#endif

    return true;
  }

  size_t File::tell(void) const {
#ifndef ANDROID
    return m_file->tellg();
#else
    return AAsset_getLength(m_file) - AAsset_getRemainingLength(m_file);
#endif
  }

  size_t File::fileSize(void) const {
#ifndef ANDROID
    size_t cur = m_file->tellg();
    m_file->seekg(0, std::ios::end);

    size_t end = m_file->tellg();
    m_file->seekg(cur, std::ios::beg);

    return end;
#else
    return AAsset_getLength(m_file);
#endif
  }

  void File::flush(void) {
#ifndef ANDROID
    m_file->flush();
#endif
  }

  std::string File::getFileName(void) {
    return m_fileName;
  }
}