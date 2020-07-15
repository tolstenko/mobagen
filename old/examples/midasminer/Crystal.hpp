#pragma once
#include "Engine.hpp"
#include "Texture.hpp"
#include "Material.hpp"

using namespace mobagen;
class Crystal : public Component {
public:
  enum CrystalType
  {
	BLUE=0,
	GREEN=1,
	PURPLE=2,
	RED=3,
	YELLOW=4
  };
  Crystal(float scaleX, float scaleY, CrystalType color);

  static std::shared_ptr<Entity> CrystalFactory(
	  std::map<Crystal::CrystalType, std::shared_ptr<Texture>> textures,
	  std::map<Crystal::CrystalType, std::shared_ptr<Material>> materials,
	  int x, int y, Crystal::CrystalType color);

  void randomize();

  void increaseSize();
  void decreaseSize();
  void decreaseSizeNow();
  void swapPositions(std::shared_ptr<Crystal> neighbor, bool regress);
  void dropTo(glm::vec3 target);
  glm::vec3 getTargetPosition();

  void update(Input *input, std::chrono::microseconds delta) override;
  CrystalType getColor();
  const char* getType() override;
private:
  CrystalType m_cystalType;
  float m_targetScale=1;
  float m_scaleX, m_scaleY;
  bool m_scaleNeedsUpdate = false;
  bool m_isSwapping = false;
  bool m_isSwapReturn = false;
  bool m_isDropping = false;
  glm::vec3 m_targetPosition;
  glm::vec3 m_originalPosition;
  float m_velocity = 0;

  void updateScale(double delta);
  void updateSwap(double delta);
  void updateDrop(double delta);
};