#include "Matrix.hpp"
#include <vector>
#include "CrystalPicker.hpp"
#include "Logger.hpp"
#include "Menu.hpp"

Matrix::Matrix()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++) {
			matrix[i][j] = nullptr;
		}
	}
	m_timeToGlobalRun = 0.5;
}

const char * Matrix::getType(void)
{
	return "MATRIX";
}

void Matrix::update(Input *input, std::chrono::microseconds delta)
{
	if (getParent()->getComponent<Menu>()->getTime() < 0)
		return;
	m_timeToGlobalRun -= delta.count()/1000000.0;
	if (m_timeToGlobalRun < 0) {
		if (solve())
			m_timeToGlobalRun = 0.5;
		else
			m_timeToGlobalRun = FLT_MAX;
	}
}

std::shared_ptr<Crystal> Matrix::getElement(int x, int y)
{
	if (x < 0 || x >= 8 || y < 0 || y >= 8)
		return nullptr;
	return matrix[y][x];
}

void Matrix::setElement(int x, int y, std::shared_ptr<Crystal> elem)
{
	matrix[y][x] = elem;
}

bool Matrix::solve()
{
	for (int y = 8; y >= 0; y--)
	{
		for (int x = 0; x < 8; x++)
		{
			if (consume(x, y))
			{
				m_timeToGlobalRun = 0.5;
				return true;
			}
		}
	}
	return false;
}

bool Matrix::canSwap(int x1, int y1, int x2, int y2)
{
  // get elements
  auto a = getElement(x1, y1);
  auto b = getElement(x2, y2);
  
  // make a fake move 
  setElement(x1, y1, b);
  setElement(x2, y2, a);

  // get matches
  auto matchesForA = findMatches(x1, y1);
  auto matchesForB = findMatches(x2, y2);
  auto biggest = matchesForA.size() > matchesForB.size() ? matchesForA : matchesForB;

  // reset the fake move
  setElement(x1, y1, a);
  setElement(x2, y2, b);
  return biggest.size()>=3;
}

bool Matrix::canConsume(int x, int y)
{
	auto matches = findMatches(x, y);
	return matches.size() >= 3;
}

bool Matrix::consume(int x, int y)
{
	auto matches = findMatches(x, y);
	if (matches.size() >= 3)
	{
		getParent()->getComponent<Menu>()->addScore(matches.size()*matches.size());
		bool isHorizontal = false;
		if (abs(matches[0]->getTransform().getPosition().x - matches[1]->getTransform().getPosition().x) > 1)
			isHorizontal = true;

		if (isHorizontal)
		{
			for (int i = 0; i < matches.size(); i++)
			{
				auto pos = CrystalPicker::Vec3ToMatrixPosition(matches[i]->getTargetPosition());

				// tell others to drop
				while (pos.y != 0)
				{
					auto elem = getElement(pos.x, pos.y-1);
					setElement(pos.x, pos.y, elem);
					elem->dropTo(CrystalPicker::MatrixPositionToVec3(pos.x, pos.y));
					pos.y--;
				}

				// make itself drop && set new position
				setElement(pos.x, 0, matches[i]);
				auto startPos = CrystalPicker::MatrixPositionToVec3(pos.x, -2);
				auto newPos = CrystalPicker::MatrixPositionToVec3(pos.x, 0);
				matches[i]->getTransform().setPosition(startPos);
				matches[i]->dropTo(newPos);
				matches[i]->decreaseSizeNow();
				matches[i]->randomize();
			}
		}
		// vertical
		else 
		{
			// find the top
			auto top = CrystalPicker::Vec3ToMatrixPosition(matches[0]->getTargetPosition());

			// drop all above it
			for (int i = top.y - 1; i >= 0; i--)
			{
				auto elem = getElement(top.x, i);
				setElement(top.x, i + matches.size(), elem);
				elem->dropTo(CrystalPicker::MatrixPositionToVec3(top.x, i + matches.size()));
			}

			// drop new crystals
			for (int i = 0; i < matches.size(); i++)
			{
				// make itself drop && set new position
				setElement(top.x, i, matches[i]);
				auto startPos = CrystalPicker::MatrixPositionToVec3(top.x, -2 - matches.size() + i);
				auto newPos = CrystalPicker::MatrixPositionToVec3(top.x, i);
				matches[i]->getTransform().setPosition(startPos);
				matches[i]->dropTo(newPos);
				matches[i]->decreaseSizeNow();
				matches[i]->randomize();
			}
		}
    scheduleGlobalSolve(0.5);
		return true;
	}
	else return false;
}

void Matrix::scheduleGlobalSolve(float time)
{
	m_timeToGlobalRun = time;
}

std::vector<std::shared_ptr<Crystal>> Matrix::findMatches(int x, int y)
{
	auto vertical = findVerticalNeighbours(x, y);
	auto horizontal = findHorizontalNeighbours(x, y);
	auto biggest = vertical.size() > horizontal.size() ? vertical : horizontal;
	return biggest;
}

// todo: optimize this
std::vector<std::shared_ptr<Crystal>> Matrix::findMatchesInNeighbours(std::vector<std::shared_ptr<Crystal>> neighbours)
{
	// size 5
	if (neighbours.size() == 5) {
		// match 5
		if (neighbours[0]->getColor() == neighbours[1]->getColor() && neighbours[1]->getColor() == neighbours[2]->getColor() && neighbours[2]->getColor() == neighbours[3]->getColor() && neighbours[3]->getColor() == neighbours[4]->getColor())
			return neighbours;
		// match 4
		if (neighbours[0]->getColor() == neighbours[1]->getColor() && neighbours[1]->getColor() == neighbours[2]->getColor() && neighbours[2]->getColor() == neighbours[3]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[0], neighbours[1], neighbours[2], neighbours[3]};
		if (neighbours[1]->getColor() == neighbours[2]->getColor() && neighbours[2]->getColor() == neighbours[3]->getColor() && neighbours[3]->getColor() == neighbours[4]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[1], neighbours[2], neighbours[3], neighbours[4]};
		// match 3
		if (neighbours[0]->getColor() == neighbours[1]->getColor() && neighbours[1]->getColor() == neighbours[2]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[0], neighbours[1], neighbours[2]};
		if (neighbours[1]->getColor() == neighbours[2]->getColor() && neighbours[2]->getColor() == neighbours[3]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[1], neighbours[2], neighbours[3]};
		if (neighbours[2]->getColor() == neighbours[3]->getColor() && neighbours[3]->getColor() == neighbours[4]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[2], neighbours[3], neighbours[4]};
	}
	// size 4
	if (neighbours.size() == 4) {
		// match 4
		if (neighbours[0]->getColor() == neighbours[1]->getColor() && neighbours[1]->getColor() == neighbours[2]->getColor() && neighbours[2]->getColor() == neighbours[3]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[0], neighbours[1], neighbours[2], neighbours[3]};
		// match 3
		if (neighbours[0]->getColor() == neighbours[1]->getColor() && neighbours[1]->getColor() == neighbours[2]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[0], neighbours[1], neighbours[2]};
		if (neighbours[1]->getColor() == neighbours[2]->getColor() && neighbours[2]->getColor() == neighbours[3]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[1], neighbours[2], neighbours[3]};
	}
	// size 3
	if (neighbours.size() == 3) {
		// match 3
		if (neighbours[0]->getColor() == neighbours[1]->getColor() && neighbours[1]->getColor() == neighbours[2]->getColor())
			return std::vector<std::shared_ptr<Crystal>>{neighbours[0], neighbours[1], neighbours[2]};
	}

	return std::vector<std::shared_ptr<Crystal>>();
}

std::vector<std::shared_ptr<Crystal>> Matrix::findVerticalNeighbours(int x, int y)
{
	std::vector<std::shared_ptr<Crystal>> neighbours;
	
	for (int i = -2; i <= 2; i++)
	{
		auto elem = getElement(x, y + i);
		if (elem != nullptr)
			neighbours.push_back(elem);
	}

	return findMatchesInNeighbours(neighbours);
}

std::vector<std::shared_ptr<Crystal>> Matrix::findHorizontalNeighbours(int x, int y)
{
	std::vector<std::shared_ptr<Crystal>> neighbours;

	for (int i = -2; i <= 2; i++)
	{
		auto elem = getElement(x+i, y);
		if (elem != nullptr)
			neighbours.push_back(elem);
	}

	return findMatchesInNeighbours(neighbours);
}
