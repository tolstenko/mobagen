#include "Crystal.hpp"
#include "Engine.hpp"
#include "Logger.hpp"
#include "CrystalPicker.hpp"
#include "Plane.hpp"
#include "components/MeshRenderer.hpp"
#include <random>
#include "Matrix.hpp"
#include "components/BoxCollider.hpp"

Crystal::Crystal(float scaleX, float scaleY, Crystal::CrystalType color)
{  
  m_scaleX = scaleX; 
  m_scaleY = scaleY;
  m_cystalType = color;
}

std::shared_ptr<Entity> Crystal::CrystalFactory(std::map<Crystal::CrystalType, std::shared_ptr<Texture>> textures, std::map<Crystal::CrystalType, std::shared_ptr<Material>> materials, int x, int y, Crystal::CrystalType color)
{
	auto mesh = Plane::getMesh();
	auto entity = std::make_shared<Entity>();

	auto texture = textures[color];
	auto material = materials[color];

	entity->addComponent<MeshRenderer>(mesh, material);
	entity->getTransform().setPosition(CrystalPicker::MatrixPositionToVec3(x,y));
	entity->getTransform().setScale(glm::vec3(38, 1, 38));
	entity->addComponent<BoxCollider>(glm::vec3(38/2,38/2,38/2), 1);
	entity->getComponent<BoxCollider>()->getRigidBody()->setCollisionFlags(entity->getComponent<BoxCollider>()->getRigidBody()->getCollisionFlags() | btCollisionObject::CF_STATIC_OBJECT);
	entity->addComponent<Crystal>(38, 38, color);
	return entity;
}

void Crystal::randomize()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<> dis(0, 4);
	auto color = (CrystalType)dis(gen);
	getParent()->getComponent<MeshRenderer>()->setMaterial(getParent()->getParent()->getComponent<CrystalPicker>()->getMaterial(color));
	auto tex = getParent()->getParent()->getComponent<CrystalPicker>()->getTexture(color);
	getTransform().setScale(glm::vec3(38, 1, 38));
	m_cystalType = color;
}

void Crystal::increaseSize()
{
	m_targetScale = 1.4;
	m_scaleNeedsUpdate = true;
}

void Crystal::decreaseSize()
{
	m_targetScale = 1;
	m_scaleNeedsUpdate = true;
}

void Crystal::decreaseSizeNow()
{
	m_scaleNeedsUpdate = false;
	m_targetScale = 1;
	auto scale = getTransform().getScale();
	scale.x = m_targetScale * m_scaleX;
	scale.z = m_targetScale * m_scaleY;
	getTransform().setScale(scale);
}

void Crystal::swapPositions(std::shared_ptr<Crystal> neighbor, bool regress)
{ 
	m_targetPosition = neighbor->getTransform().getPosition().xyz();
	m_originalPosition = getTransform().getPosition().xyz();
	m_isSwapReturn = regress;
	m_isSwapping = true;
}

void Crystal::update(Input *input, std::chrono::microseconds delta)
{
  if (m_scaleNeedsUpdate)
    updateScale(delta.count()/1000000.0);
  if (m_isSwapping)
	updateSwap(delta.count()/1000000.0);
  if (m_isDropping)
	updateDrop(delta.count()/1000000.0);
}

Crystal::CrystalType Crystal::getColor()
{
	return m_cystalType;
}

const char * Crystal::getType()
{
	return "CRYSTAL";
}

void Crystal::updateScale(double delta)
{
	auto scale = getParent()->getTransform().getScale();

	auto targetX = m_targetScale * m_scaleX;
	auto deltaX = targetX - scale.x;
	scale.x += deltaX * delta * 20;

	auto targetY = m_targetScale * m_scaleY;
	auto deltaY = targetY - scale.z;
	scale.z += deltaY * delta * 20;

	if (fabs(deltaX) < 1)
		scale.x = targetX;
	if (fabs(deltaY) < 1)
		scale.z = targetY;

	if (fabs(deltaX) < 1 && fabs(deltaY) < 1) {
		m_scaleNeedsUpdate = false;
		getParent()->getTransform().setScale(scale);
	}
	
	getParent()->getTransform().setScale(scale);
}

void Crystal::updateSwap(double delta)
{
	auto position = getParent()->getTransform().getPosition().xyz();

	auto targetX = m_targetPosition.x;
	auto deltaX = targetX - position.x;
	position.x += deltaX * delta *10;

	auto targetY = m_targetPosition.y;
	auto deltaY = targetY - position.y;
	position.y += deltaY * delta *10;

	auto targetZ = m_targetPosition.z;
	auto deltaZ = targetZ - position.z;
	position.z += deltaZ * delta *10;

	if (fabs(deltaX) < 1)
		position.x = targetX;
	if (fabs(deltaY) < 1)
		position.y = targetY;
	if (fabs(deltaZ) < 1)
		position.z = targetZ;

	if (fabs(deltaX) < 1 && fabs(deltaY) < 1 && fabs(deltaZ) < 1) {
		if (m_isSwapReturn)
		{
			m_isSwapReturn = false;
			m_targetPosition = m_originalPosition;
			return;
		}
		else
		{
			m_isSwapping = false;
			getParent()->getParent()->getComponent<CrystalPicker>()->deselect();
			getTransform().setPosition(m_targetPosition);
			auto pos = CrystalPicker::Vec3ToMatrixPosition(getTransform().getPosition().xyz());
			getParent()->getParent()->getComponent<Matrix>()->consume(pos.x,pos.y);
			return;
		}
	}

	getTransform().setPosition(position);
}

void Crystal::updateDrop(double delta)
{
	auto position = getParent()->getTransform().getPosition().xyz();
	auto matrixpos = CrystalPicker::Vec3ToMatrixPosition(getTransform().getPosition().xyz());
	m_velocity -= 50 + matrixpos.x*0.4 + matrixpos.y*0.1;
	auto targetZ = m_targetPosition.z;
	position.z += m_velocity * delta;
		
	if (position.z < targetZ ) {
		m_isDropping = false;
		m_velocity = 0;
		position.z = targetZ;
		if (getParent()->getParent()->getComponent<Matrix>()->canConsume(matrixpos.x, matrixpos.y))
			getParent()->getParent()->getComponent<Matrix>()->scheduleGlobalSolve(0.5);
	}

	getParent()->getTransform().setPosition(position);
}

void Crystal::dropTo(glm::vec3 target)
{
	m_isDropping = true;
	m_velocity = 0;
	m_targetPosition = target;
	m_originalPosition = target;
}

glm::vec3 Crystal::getTargetPosition()
{
	return m_targetPosition;
}
