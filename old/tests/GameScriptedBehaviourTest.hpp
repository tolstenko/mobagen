#pragma once
#include "GameScriptedBehaviour.hpp"
#include "Logger.hpp"
using namespace mobagen;

class GameScriptedBehaviourTest : public GameScriptedBehaviour
{
public:
	void Awake() override;
	void Start() override;
	void OnGUI() override;
	void Update() override;
};