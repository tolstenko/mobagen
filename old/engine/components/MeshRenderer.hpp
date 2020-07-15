#pragma once

#include "Component.hpp"
#include "Mesh.hpp"
#include "Material.hpp"

namespace mobagen {
  class MeshRenderer : public Component {
  public:
    MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);

    virtual ~MeshRenderer(void);

    virtual void render(Shader *shader);

    void setMaterial(std::shared_ptr<Material> material);

    std::shared_ptr<Material> getMaterial();

    void setMesh(std::shared_ptr<Mesh> mesh);

    std::shared_ptr<Mesh> getMesh();

    inline virtual const char *getType(void) { return "MESH_RENDERER"; }

  private:
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Material> m_material;
  };
}