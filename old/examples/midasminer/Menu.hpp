#pragma once
#include "Engine.hpp"

using namespace mobagen;
class Menu : public Component
{
public:
	const char* getType() override;
//	void updateInput(Input* input, double delta) override {};
	void update(Input *input, std::chrono::microseconds delta) override;
	void render(Shader* shader) override {};
	void registerWithEngine(Engine* engine) override {};
	void deregisterFromEngine(Engine* engine) override {};
	void onGUI(ImGuiContext* context) override;
	void addScore(int value);
	double getTime();
private:
	double m_remainingTime = 60;
	int m_score = 0;
};
