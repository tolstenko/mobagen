#pragma once
#include <assimp/IOStream.hpp>
#include <vector>

namespace mobagen {
  class FileSystem {
  public:
	static auto Exists(const char* path) -> bool;
	static auto Exists(std::string path) -> bool;
	// TODO: compare paths with "../" 
	static auto ComparePaths(const char* one, const char* second) -> bool;
	// TODO: compare paths with "../" 
	static auto ComparePaths(const std::string& one, const std::string& second) -> bool;
	static auto PathSeparator() -> char;
	static auto ListDirectory(const std::string& path) -> std::vector<std::string>;
	static auto ListDirectory(const char* path) -> std::vector<std::string>;
	static auto ListDirectoryFiles(const std::string& path)->std::vector<std::string>;
	static auto ListDirectoryFiles(const char* path)->std::vector<std::string>;
	static auto ListDirectoryFolders(const std::string& path)->std::vector<std::string>;
	static auto ListDirectoryFolders(const char* path)->std::vector<std::string>;
  	static auto IsFile(const char* path) -> bool;
	static auto IsFile(const std::string& path) -> bool;
	static auto IsDirectory(const char* path) -> bool;
  	static auto IsDirectory(const std::string& path) -> bool;
	static auto Open(const char* pFile, const char* pMode) -> Assimp::IOStream*;
	static auto Open(const std::string& path, const char* pMode) -> Assimp::IOStream*;
	static auto Close(Assimp::IOStream *file) -> void;
  };
}
