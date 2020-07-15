#include "MeshRenderer.hpp"
#include <iostream>

namespace mobagen {
  MeshRenderer::MeshRenderer(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
    this->m_mesh = mesh;
    this->m_material = material;
  }

  MeshRenderer::~MeshRenderer(void) {
  }

  void MeshRenderer::render(Shader *shader) {
    shader->setUniformMatrix4f("World", m_parentEntity->getWorldMatrix());

    m_material->bind();
    m_mesh->render();
  }

  void MeshRenderer::setMaterial(std::shared_ptr<Material> material) {
    m_material = material;
  }

  std::shared_ptr<Material> MeshRenderer::getMaterial() {
    return m_material;
  }

  void MeshRenderer::setMesh(std::shared_ptr<Mesh> mesh) {
    m_mesh = mesh;
  }

  std::shared_ptr<Mesh> MeshRenderer::getMesh() {
    return m_mesh;
  }
}