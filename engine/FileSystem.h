#ifndef __IMGUI_FILE_DIALOG_H_
#define __IMGUI_FILE_DIALOG_H_

#include <vector>
#include <string>

#define MAX_FILE_DIALOG_NAME_BUFFER 1024

struct FileInfoStruct
{
	char type;
	std::string filePath;
	std::string fileName;
	std::string ext;
};

class FileSystem
{
private:
	std::vector<FileInfoStruct> m_FileList;
	std::string m_SelectedFileName;
	std::string m_CurrentPath;
	std::vector<std::string> m_CurrentPath_Decomposition;
	std::string m_CurrentFilterExt;

public:
	static char FileNameBuffer[MAX_FILE_DIALOG_NAME_BUFFER];
	static int FilterIndex;
	bool IsOk;

public:
	static FileSystem* Instance()
	{
		static FileSystem *_instance = new FileSystem();
		return _instance;
	}

public:
	FileSystem();
	~FileSystem();

	bool FileDialog(const char* vName, const char* vFilters = 0, std::string vPath = ".", std::string vDefaultFileName = "");
	std::string GetFilepathName();
	std::string GetCurrentPath();
	std::string GetCurrentFileName();
	std::string GetCurrentFilter();

private:
	void ScanDir(std::string vPath);
	void SetCurrentDir(std::string vPath);
	void ComposeNewPath(std::vector<std::string>::iterator vIter);
};


#endif 