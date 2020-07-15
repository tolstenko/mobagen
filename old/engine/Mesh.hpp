#pragma once

#include "Vertex.hpp"
#include "MeshData.hpp"

#include <string>
#include <memory>

namespace mobagen {
  class Mesh {
  public:
    Mesh(std::string identifier, Vertex vertices[], int vertSize, unsigned int indices[], int indexSize);

    void reasign(std::string identifier, Vertex vertices[], int vertSize, unsigned int indices[],
                 int indexSize);
    virtual ~Mesh(void);

    void render(void) const;

  private:
    std::shared_ptr<MeshData> m_meshData;
  };
}