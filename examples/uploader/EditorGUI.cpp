//
// Created by Marcos Oliveira on 3/13/21.
//

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "EditorGUI.hpp"
#include <Logger.hpp>
#include "components/MeshRenderer.hpp"
#include <Plane.hpp>
#include <string>
#include <WebRequest.hpp>
#include <filesystem>
#include <imgui.h>
#include <imgui_internal.h>
#include <stdio.h>
#include <iostream>
//#include <sstream>
#include "Material.hpp"
#include "Logger.hpp"

ImVec2 windowFactor;

static bool applied = false;



//using namespace std::chrono_literals;



    enum class FileDialogType {
        OpenFile,
        SelectFolder
    };

    enum class FileDialogSortOrder {
        Up,
        Down,
        None
    };



void EditorGUI::onGUI(ImGuiContext* context)
{
  if(!applied) {

    ImGui::Begin("UPLOADER", nullptr, ImVec2(512*windowFactor.x, 128*windowFactor.y), 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(50*windowFactor.x, 20*windowFactor.y), 0);

        const char* startingFolder = "./";
        const char* optionalFileExtensionFilterString = "";//".jpg;.jpeg;.png;.tiff;.bmp;.gif;.txt";
      static int fileDialogFileSelectIndex = 0;
      static int fileDialogFolderSelectIndex = 0;
      static std::string fileDialogCurrentPath = "./";
      static std::string fileDialogCurrentFile = "";
      static std::string fileDialogCurrentFolder = "";

      static char fileDialogError[500] = "";
      static FileDialogSortOrder fileNameSortOrder = FileDialogSortOrder::None;
      static FileDialogSortOrder sizeSortOrder = FileDialogSortOrder::None;
      static FileDialogSortOrder dateSortOrder = FileDialogSortOrder::None;
      static FileDialogSortOrder typeSortOrder = FileDialogSortOrder::None;

      std::vector<std::filesystem::directory_entry> files;
      std::vector<std::filesystem::directory_entry> folders;

      try {
          for (auto& p : std::filesystem::directory_iterator(fileDialogCurrentPath))
          {
              if (p.is_directory())
              {
                  folders.push_back(p);
              }
              else
              {
                  files.push_back(p);
              }
          }
      } catch (...) { }
        ImGui::Text("Choose the form you want to upload your files to:");
        //const bool browseButtonPressed2 = ImGui::Button("LOAD FILES");
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        //static ImGuiFs::Dialog dlg;
        //const char *chosenPath = dlg.chooseFileDialog(browseButtonPressed2,startingFolder,optionalFileExtensionFilterString);
        ImGui::PopStyleColor(1);

        //if (strlen(dlg.getChosenPath())>0) ImGui::Text("Chosen path: \"%s\"",dlg.getChosenPath());

    //    if(browseButtonPressed2)
    //    {
        ImGui::BeginChild("Directories##1", ImVec2(200, 300), true, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::Selectable("..", false, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(ImGui::GetWindowContentRegionWidth(), 0)))
        {
            if (ImGui::IsMouseDoubleClicked(0))
            {
                fileDialogCurrentPath = std::filesystem::path(fileDialogCurrentPath).parent_path().string();

            }
        }

      for (int i = 0; i < folders.size(); i++)
      {
          if (ImGui::Selectable(folders[i].path().stem().string().c_str(), i == fileDialogFolderSelectIndex, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(ImGui::GetWindowContentRegionWidth(), 0)))
          {
              fileDialogCurrentFile = "";
              if (ImGui::IsMouseDoubleClicked(0)) {
                  fileDialogCurrentPath = folders[i].path().string();
                  fileDialogFolderSelectIndex = 0;
                  fileDialogFileSelectIndex = 0;
                  ImGui::SetScrollHere(0.0f);
                  fileDialogCurrentFolder = "";
              }
              else {
                  fileDialogFolderSelectIndex = i;
                  fileDialogCurrentFolder = folders[i].path().stem().string();
              }
          }
      }
      ImGui::EndChild();

      ImGui::SameLine();

      ImGui::BeginChild("Files##1", ImVec2(550, 300), true, ImGuiWindowFlags_HorizontalScrollbar);
      ImGui::Columns(4);

      static float initialSpacingColumn0 = 230.0f;
      if (initialSpacingColumn0 > 0) {
          ImGui::SetColumnWidth(0, initialSpacingColumn0);
          initialSpacingColumn0 = 0.0f;
      }
      static float initialSpacingColumn1 = 80.0f;
      if (initialSpacingColumn1 > 0) {
          ImGui::SetColumnWidth(1, initialSpacingColumn1);
          initialSpacingColumn1 = 0.0f;
      }
      static float initialSpacingColumn2 = 80.0f;
      if (initialSpacingColumn2 > 0) {
          ImGui::SetColumnWidth(2, initialSpacingColumn2);
          initialSpacingColumn2 = 0.0f;
      }


      if (ImGui::Selectable("File")) {
          sizeSortOrder = FileDialogSortOrder::None;
          dateSortOrder = FileDialogSortOrder::None;
          typeSortOrder = FileDialogSortOrder::None;
          fileNameSortOrder = (fileNameSortOrder == FileDialogSortOrder::Down ? FileDialogSortOrder::Up : FileDialogSortOrder::Down);
      }
      ImGui::NextColumn();
      if (ImGui::Selectable("Size")) {
          fileNameSortOrder = FileDialogSortOrder::None;
          dateSortOrder = FileDialogSortOrder::None;
          typeSortOrder = FileDialogSortOrder::None;
          sizeSortOrder = (sizeSortOrder == FileDialogSortOrder::Down ? FileDialogSortOrder::Up : FileDialogSortOrder::Down);
      }
      ImGui::NextColumn();
      if (ImGui::Selectable("Type")) {
          fileNameSortOrder = FileDialogSortOrder::None;
          dateSortOrder = FileDialogSortOrder::None;
          sizeSortOrder = FileDialogSortOrder::None;
          typeSortOrder = (typeSortOrder == FileDialogSortOrder::Down ? FileDialogSortOrder::Up : FileDialogSortOrder::Down);
      }
      ImGui::NextColumn();
      if (ImGui::Selectable("Date")) {
          fileNameSortOrder = FileDialogSortOrder::None;
          sizeSortOrder = FileDialogSortOrder::None;
          typeSortOrder = FileDialogSortOrder::None;
          dateSortOrder = (dateSortOrder == FileDialogSortOrder::Down ? FileDialogSortOrder::Up : FileDialogSortOrder::Down);
      }
      ImGui::NextColumn();
      ImGui::Separator();

      // Sort files
      if (fileNameSortOrder != FileDialogSortOrder::None) {
          std::sort(files.begin(), files.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
              if (fileNameSortOrder == FileDialogSortOrder::Down) {
                  return a.path().filename().string() > b.path().filename().string();
              }
              else {
                  return a.path().filename().string() < b.path().filename().string();
              }
          });
      }
      else if (sizeSortOrder != FileDialogSortOrder::None) {
          std::sort(files.begin(), files.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
              if (sizeSortOrder == FileDialogSortOrder::Down) {
                  return a.file_size() > b.file_size();
              }
              else {
                  return a.file_size() < b.file_size();
              }
          });
      }
      else if (typeSortOrder != FileDialogSortOrder::None) {
          std::sort(files.begin(), files.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
              if (typeSortOrder == FileDialogSortOrder::Down) {
                  return a.path().extension().string() > b.path().extension().string();
              }
              else {
                  return a.path().extension().string() < b.path().extension().string();
              }
          });
      }
      else if (dateSortOrder != FileDialogSortOrder::None) {
          std::sort(files.begin(), files.end(), [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b) {
              if (dateSortOrder == FileDialogSortOrder::Down) {
                  return a.last_write_time() > b.last_write_time();
              }
              else {
                  return a.last_write_time() < b.last_write_time();
              }
          });
      }

      for (int i = 0; i < files.size(); ++i)
      {
          if (ImGui::Selectable(files[i].path().filename().string().c_str(), i == fileDialogFileSelectIndex, ImGuiSelectableFlags_AllowDoubleClick, ImVec2(ImGui::GetWindowContentRegionWidth(), 0))) {
              fileDialogFileSelectIndex = i;
              fileDialogCurrentFile = files[i].path().filename().string();
              fileDialogCurrentFolder = "";
          }

          ImGui::NextColumn();
          ImGui::TextUnformatted(std::to_string(files[i].file_size()).c_str());
          ImGui::NextColumn();
          ImGui::TextUnformatted(files[i].path().extension().string().c_str());
          ImGui::NextColumn();
          auto ftime = files[i].last_write_time();
          auto st = std::chrono::time_point_cast<std::chrono::system_clock::duration>(ftime - decltype(ftime)::clock::now() + std::chrono::system_clock::now());
          std::time_t tt = std::chrono::system_clock::to_time_t(st);
          std::tm* mt = std::localtime(&tt);
          std::stringstream ss;
          ss << std::put_time(mt, "%F %R");
          ImGui::TextUnformatted(ss.str().c_str());
          ImGui::NextColumn();
      }

      ImGui::EndChild();
            //log_info("UP");
            //ImGui::Begin("Select a file", nullptr, ImGuiWindowFlags_NoResize);

            //ImGui::End();
      //  }
        /*if(ImGui::Button("GET FROM CD"))
        {
            log_info("TESTE");
        }*/

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
  request.SetUrl("http://httpbin.org/post");
  request.AddMultiPart("field","filename.txt",data,"text/plain");
  auto resp =request.Post();
  log_info("%s",resp.text.data());
}








