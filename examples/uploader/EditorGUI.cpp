//
// Created by Samuel Carlos on 4/12/18.
//

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "EditorGUI.hpp"
#include <Logger.hpp>
#include "components/MeshRenderer.hpp"
#include <Plane.hpp>
#include <string>
#include <WebRequest.hpp>
#include "Material.hpp"
//#include <imguifilesystem.h>
#include "Logger.hpp"

ImVec2 windowFactor;

static bool applied = false;

void EditorGUI::onGUI(ImGuiContext* context)
{
  if(!applied) {

    ImGui::Begin("UPLOADER", nullptr, ImVec2(128*windowFactor.x, 128*windowFactor.y), 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(370*windowFactor.x, 20*windowFactor.y), 0);

        const char* startingFolder = "./";
        const char* optionalFileExtensionFilterString = "";//".jpg;.jpeg;.png;.tiff;.bmp;.gif;.txt";

        ImGui::Text("Choose the form you want to upload your files to:");
        const bool browseButtonPressed2 = ImGui::Button("LOAD FILES");
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        //static ImGuiFs::Dialog dlg;
        //const char *chosenPath = dlg.chooseFileDialog(browseButtonPressed2,startingFolder,optionalFileExtensionFilterString);
        ImGui::PopStyleColor(1);

        //if (strlen(dlg.getChosenPath())>0) ImGui::Text("Chosen path: \"%s\"",dlg.getChosenPath());

        if(ImGui::Button("GET FROM CD"))
        {
            log_info("TESTE");
        }

    ImGui::End();

  }
}


const char* EditorGUI::getType()
{
  return "EDITORGUI";
}

void EditorGUI::update(Input *input, std::chrono::microseconds delta) {}

EditorGUI::EditorGUI()
{
  auto object = new Object();
  Object::Destroy(object);
  log_info("%x",object->GetInstanceID());

  windowFactor.y = getEngine()->getWindow()->getHeight()/2000.0f;
  windowFactor.x = getEngine()->getWindow()->getWidth()/2000.0f;

  WebRequest request;

  std::string data;
  data.push_back('d');
  data.push_back('\0');
  data.push_back('a');
  data.push_back('t');
  data.push_back('\0');

  log_info("%d",data.size());
  log_info("%d",data.size());
//  request.SetUrl("http://httpbin.org/post");
//  request.AddMultiPart("field","filename.txt",data,"text/plain");
//  auto resp =request.Post();
//  log_info("%s",resp.text.data());
}








