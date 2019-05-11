#include "Menu.hpp"
#include <imgui.h>

const char* Menu::getType()
{
	return "MENU";
}

void Menu::update(Input *input, std::chrono::microseconds delta)
{
	m_remainingTime -= delta.count()/1000000.0;
}

void Menu::onGUI(ImGuiContext* context)
{
	//ImGui::SetCurrentContext(context);

	if (m_remainingTime > 0)
	{
		ImVec2 pos = ImVec2(50,50);
		ImGui::SetNextWindowPos(pos);
		ImGui::Begin("teste", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse |
			ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
		ImGui::Text("TIME LEFT");
		ImGui::Text("  %.1lf", m_remainingTime);
		ImGui::Text("");
		ImGui::Text("  SCORE  ");
		ImGui::Text("   %d   ", m_score);
		ImGui::End();
	}
	else
	{
		ImVec2 pos = ImVec2(400, 170);
		ImGui::SetNextWindowPos(pos);
		ImGui::SetNextWindowSize(ImVec2(200, 200));
		ImGui::Begin("", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoCollapse  |
			ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
		
		ImGui::SetCursorPos(ImVec2(60,80));
		ImGui::Text("TIME IS UP!");
		ImGui::SetCursorPos(ImVec2(60, 100));
		ImGui::Text("  YOU GOT  ");
		ImGui::SetCursorPos(ImVec2(60, 130));
		ImGui::Text("    %d   ", m_score);
		ImGui::End();
		//ImGui::BeginPopupModal("", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		//	ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders |
		//	ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	}
}

void Menu::addScore(int value)
{
	m_score += value;
}

double Menu::getTime()
{
	return m_remainingTime;
}
