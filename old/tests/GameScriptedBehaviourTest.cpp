//
// Created by Alexandre Tolstenko Nogueira on 6/26/18.
//

#include "GameScriptedBehaviourTest.hpp"

void GameScriptedBehaviourTest::Awake()
{
	log_info("%s","ScriptedBehaviour Awake");
}

void GameScriptedBehaviourTest::Start()
{
	log_info("%s", "ScriptedBehaviour Start");
}

void GameScriptedBehaviourTest::OnGUI()
{
	log_info("%s", "ScriptedBehaviour OnGUI()");
}

void GameScriptedBehaviourTest::Update()
{
	log_info("%s", "ScriptedBehaviour Update()");
}
