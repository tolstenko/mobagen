#pragma once

#if defined(GLES2)
  #include <GLES2/gl2.h>
#elif defined(GLES3)
  #include <GLES3/gl3.h>
#else
  #include <GL/glew.h>
#endif

#include "Asset.hpp"
#include "TextureData.hpp"

#include <memory>

namespace mobagen {
  class Texture {
  public:
    Texture(const Asset &file, GLenum textureTarget = GL_TEXTURE_2D, GLfloat filter = GL_LINEAR);

    Texture(std::shared_ptr<TextureData> texData);

    ~Texture(void);

    void bind(unsigned int unit = 0) const;

    int width() const;

    int height() const;

    std::shared_ptr<TextureData> getTextureData();

    void setTextureData(std::shared_ptr<TextureData> textureData);

    int getBytesPerPixel() const;

  private:
    std::shared_ptr<TextureData> m_textureData;
    int m_bytesPerPixel;
  };
}