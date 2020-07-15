#pragma once
#include "Engine.hpp"
#include "Crystal.hpp"

using namespace mobagen;
class Matrix : public Component {
public:
	Matrix();
	virtual const char * getType(void) override;
	void update(Input *input, std::chrono::microseconds delta) override;

	std::shared_ptr<Crystal> getElement(int x, int y);
	void setElement(int x, int y, std::shared_ptr<Crystal> elem);
	bool solve();
	bool canSwap(int x1, int y1, int x2, int y2);
	bool canConsume(int x, int y);
	bool consume(int x, int y);
	void scheduleGlobalSolve(float time);
private:
	std::shared_ptr<Crystal> matrix[8][8];

	std::vector<std::shared_ptr<Crystal>> findMatches(int x, int y);
	std::vector<std::shared_ptr<Crystal>> findMatchesInNeighbours(std::vector<std::shared_ptr<Crystal>> neighbours);
	std::vector<std::shared_ptr<Crystal>> findVerticalNeighbours(int x, int y);
	std::vector<std::shared_ptr<Crystal>> findHorizontalNeighbours(int x, int y);

	std::vector<std::shared_ptr<Crystal>> m_availableCrystals;
	double m_timeToGlobalRun;
};