#include "FileSystem.h"
#include "imgui.h"


#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include <algorithm>

inline bool ReplaceString(std::string& str, const std::string& oldStr, const std::string& newStr)
{
	bool Finded = false;
	size_t pos = 0;
	while ((pos = str.find(oldStr, pos)) != std::string::npos) {
		Finded = true;
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
	return Finded;
}

inline std::vector<std::string> splitStringVector(const std::string& text, char delimiter)
{
	std::vector<std::string> arr;
	std::string::size_type start = 0;
	std::string::size_type end = text.find(delimiter, start);
	while (end != std::string::npos)
	{
		std::string token = text.substr(start, end - start);
		if (token != "")
			arr.push_back(token);
		start = end + 1;
		end = text.find(delimiter, start);
	}
	arr.push_back(text.substr(start));
	return arr;
}

inline void AppendToBuffer(char* vBuffer, int vBufferLen, std::string vStr)
{
	std::string st = vStr;
	if (st != "" && st != "\n")
		ReplaceString(st, "\n", "");
	int slen = strlen(vBuffer);
	vBuffer[slen] = '\0';
	std::string str = std::string(vBuffer);
	if (str.size() > 0) str += "\n";
	str += vStr;
	int len = vBufferLen - 1;
	if (len > str.size()) len = str.size();
#ifdef MINGW32
	strncpy_s(vBuffer, vBufferLen, str.c_str(), len);
#else
	strncpy(vBuffer, str.c_str(), len);
#endif
	vBuffer[len] = '\0';
}

inline void ResetBuffer(char* vBuffer)
{
	vBuffer[0] = '\0';
}

char FileSystem::FileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER] = "";
int FileSystem::FilterIndex = 0;

FileSystem::FileSystem()
{
	
}

FileSystem::~FileSystem()
{

}

/* Alphabetical sorting */
static int alphaSort(
	const void *a, const void *b)
{
//	return strcoll(((dirent*)a)->d_name, ((dirent*)b)->d_name);
}

static bool stringComparator(FileInfoStruct a, FileInfoStruct b)
{
	bool res;
	if (a.type != b.type) res = (a.type < b.type);
	else res = (a.fileName < b.fileName);
	return res;
}

void FileSystem::ScanDir(std::string vPath)
{
	
}

void FileSystem::SetCurrentDir(std::string vPath)
{
	
}

void FileSystem::ComposeNewPath(std::vector<std::string>::iterator vIter)
{
	m_CurrentPath = "";
	while (vIter != m_CurrentPath_Decomposition.begin())
	{
		if (m_CurrentPath.size() > 0)
			m_CurrentPath = *vIter + "\\" + m_CurrentPath;
		else
			m_CurrentPath = *vIter;
		vIter--;
	}

	if (m_CurrentPath.size() > 0)
		m_CurrentPath = *vIter + "\\" + m_CurrentPath;
	else
		m_CurrentPath = *vIter + "\\";
}

bool FileSystem::FileDialog(const char* vName, const char* vFilters, std::string vPath, std::string vDefaultFileName)
{
	bool res = false;

	IsOk = false;

	ImGui::Begin(vName);

	if (vPath.size() == 0) vPath = ".";
	
	if (m_FileList.size() == 0)
	{
		if (vDefaultFileName.size() > 0)
		{
			ResetBuffer(FileNameBuffer);
			AppendToBuffer(FileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, vDefaultFileName);
		}
		
		ScanDir(vPath);
	}

	// show current path
	bool pathClick = false;
	for (std::vector<std::string>::iterator itPathDecomp = m_CurrentPath_Decomposition.begin();
		itPathDecomp != m_CurrentPath_Decomposition.end(); ++itPathDecomp)
	{
		if (itPathDecomp != m_CurrentPath_Decomposition.begin())
			ImGui::SameLine(); 
		if (ImGui::Button((*itPathDecomp).c_str()))
		{
			ComposeNewPath(itPathDecomp);
			pathClick = true;
			break;
		}
	}

	ImVec2 size = ImGui::GetContentRegionMax() - ImVec2(0.0f, 120.0f);

	ImGui::BeginChild("##FileDialog_FileList", size);

	for (std::vector<FileInfoStruct>::iterator it = m_FileList.begin(); it != m_FileList.end(); ++it)
	{
		FileInfoStruct infos = *it;
		
		bool show = true;

		std::string str;
		if (infos.type == 'd') str = "[Dir] " + infos.fileName;
		if (infos.type == 'l') str = "[Link] " + infos.fileName;
		if (infos.type == 'f') str = "[File] " + infos.fileName;
		if (infos.type == 'f' && m_CurrentFilterExt.size() > 0 && infos.ext != m_CurrentFilterExt)
		{
			show = false;
		}
		if (show == true)
		{
			if (ImGui::Selectable(str.c_str(), (infos.fileName == m_SelectedFileName)))
			{
				if (infos.type == 'd')
				{
					if (infos.fileName == "..")
					{
						if (m_CurrentPath_Decomposition.size() > 1)
						{
							std::vector<std::string>::iterator itPathDecomp = m_CurrentPath_Decomposition.end() - 2;
							ComposeNewPath(itPathDecomp);
						}
					}
					else
					{
						m_CurrentPath += "\\" + infos.fileName;
					}
					pathClick = true;
				}
				else
				{
					m_SelectedFileName = infos.fileName;
					ResetBuffer(FileNameBuffer);
					AppendToBuffer(FileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER, m_SelectedFileName);
				}
				break;
			}
		}
	}

	// changement de repertoire
	if (pathClick == true)
	{
		ScanDir(m_CurrentPath);
		m_CurrentPath_Decomposition = splitStringVector(m_CurrentPath, '\\');
		if (m_CurrentPath_Decomposition.size() == 2)
			if (m_CurrentPath_Decomposition[1] == "")
				m_CurrentPath_Decomposition.erase(m_CurrentPath_Decomposition.end() - 1);
	}

	ImGui::EndChild();

	ImGui::Text("File Name : ");

	ImGui::SameLine();

	float width = ImGui::GetContentRegionAvailWidth();
	if (vFilters != 0) width -= 120.0f;
	ImGui::PushItemWidth(width);
	ImGui::InputText("##FileName", FileNameBuffer, MAX_FILE_DIALOG_NAME_BUFFER);
	ImGui::PopItemWidth();

	if (vFilters != 0)
	{
		ImGui::SameLine();

		ImGui::PushItemWidth(100.0f);
		bool comboClick = ImGui::Combo("##Filters", &FilterIndex, vFilters) || m_CurrentFilterExt.size() == 0;
		ImGui::PopItemWidth();
		if (comboClick == true)
		{
			int itemIdx = 0;
			const char* p = vFilters;
			while (*p)
			{
				if (FilterIndex == itemIdx)
				{
					m_CurrentFilterExt = std::string(p);
					break;
				}
				p += strlen(p) + 1;
				itemIdx++;
			}
		}
	}
	
	if (ImGui::Button("Cancel"))
	{
		IsOk = false;
		res = true;
	}

	ImGui::SameLine();

	if (ImGui::Button("Ok"))
	{
		IsOk = true;
		res = true;
	}

	ImGui::End();

	if (res == true)
	{
		m_FileList.clear();
	}

	return res;
}

std::string FileSystem::GetFilepathName()
{
	return GetCurrentPath() + "\\" + GetCurrentFileName();
}

std::string FileSystem::GetCurrentPath()
{
	return m_CurrentPath;
}

std::string FileSystem::GetCurrentFileName()
{
	return std::string(FileNameBuffer);
}

std::string FileSystem::GetCurrentFilter()
{
	return m_CurrentFilterExt;
}
