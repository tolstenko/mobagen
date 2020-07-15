#include "TextureData.hpp"

namespace mobagen {
  TextureData::TextureData(int width, int height, const unsigned char *data, GLenum textureTarget, GLfloat filter) {
    createTexture(width, height, data, textureTarget, filter);
    this->m_width = width;
    this->m_height = height;
  }

  TextureData::~TextureData() {
    glDeleteTextures(1, &m_textureId);
  }

  void
  TextureData::createTexture(int width, int height, const unsigned char *data, GLenum textureTarget, GLfloat filter) {
    m_textureTarget = textureTarget;

    glGenTextures(1, &m_textureId);
    glBindTexture(textureTarget, m_textureId);
    glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, filter);
    // TODO: RE-ENABLE THIS!!
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexImage2D(textureTarget, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    for (int i = 0; i < width * height * 4; i++)
      this->data.push_back(data[i]);
  }

  void TextureData::bind(unsigned int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(m_textureTarget, m_textureId);
  }

  GLuint TextureData::getTextureId() {
    return m_textureId;
  }

  int TextureData::width() { return m_width; }

  int TextureData::height() { return m_height; }
}