#pragma once
#include "Engine.hpp"
#include "Crystal.hpp"

using namespace mobagen;
class CrystalPicker : public Component {
public:
  CrystalPicker(std::map<Crystal::CrystalType, std::shared_ptr<Texture>> textures, std::map<Crystal::CrystalType, std::shared_ptr<Material>> materials);
  void update(Input *input, std::chrono::microseconds delta) override;
  
  static glm::vec3 MatrixPositionToVec3(int x, int y);
  static glm::i32vec2 Vec3ToMatrixPosition(glm::vec3 pos);
  const char* getType() override;
  void deselect();
  std::shared_ptr<Texture> getTexture(Crystal::CrystalType);
  std::shared_ptr<Material> getMaterial(Crystal::CrystalType);
private:
	Entity * firstSelection; 
	Entity * secondSelection;
	std::map<Crystal::CrystalType, std::shared_ptr<Texture>> m_textures;
	std::map<Crystal::CrystalType, std::shared_ptr<Material>> m_materials;
};


