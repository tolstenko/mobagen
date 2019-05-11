#pragma once

#include <string>

class DownloadHandler {
public:
  std::string GetData();
  //bool IsDone();
  //std::string GetText();
private:
  std::string data;
};