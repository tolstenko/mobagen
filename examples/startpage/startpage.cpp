
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "startpage.hpp"
#include <Logger.hpp>
#include "components/MeshRenderer.hpp"
#include <Plane.hpp>
#include <string>
#include <WebRequest.hpp>
#include "Material.hpp"
#include "Logger.hpp"

ImVec2 windowFactor;
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

static bool applied = false;

void StartPage::onGUI(ImGuiContext* context)
{




  if(!applied) {

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove |  ImGuiWindowFlags_HorizontalScrollbar| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
	ImGui::Begin("Start Page", nullptr, ImVec2(128 * windowFactor.x, 128 * windowFactor.y), 0,  ImGuiWindowFlags_NoMove);
	
	ImGui::SetWindowPos(ImVec2(0, 0), 0);
	ImGui::AlignTextToFramePadding();
	ImGui::TextUnformatted("Recent Projects");
	ImGui::Separator();
	ImGui::BeginGroup(); {
		
		ImGui::BeginChild("projects_content",
			ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, ImGui::GetContentRegionAvail().y*0.9f),
			true,flags);
	// This field is the body and list of recent projects 	

		std::string dir = ".";

		//if (argv[1])
		//	dir = argv[1];

		for (auto& item : fs::recursive_directory_iterator(dir))
		{
			if (!fs::is_regular_file(item.path()))
				continue;

			ImGui::Selectable(item.path().string().c_str());
			//ImGui::Selectable("C:/Users/Marquinhos/mobagen");
			// open text file here
			//std::cout << " " << item.path().string() << '\n';
		}

		/*ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/examples");
		ImGui::Selectable("C:/Users/Marquinhos/mobagen/dependencies");*/

		ImGui::EndChild();
	}
	ImGui::EndGroup();
	ImGui::SameLine();

	ImGui::BeginGroup(); {
		
		ImGui::Button("New Project");
		ImGui::Button("Recent Projects");
		
	}
	ImGui::EndGroup();


	
	ImGui::End(); //end

  } //end
}//end


const char* StartPage::getType()
{
  return "StartPage";
}

void StartPage::update(Input *input, std::chrono::microseconds delta) {}

StartPage::StartPage()
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








