#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include <map>
#include <memory>

namespace mobagen {
  class WwwForm {
  private:
    bool containsFiles = false;
    std::vector<std::vector<uint8_t>> formData;
    std::vector<std::string> fieldNames;
    std::vector<std::string> fileNames;
    std::vector<std::string> types;
    std::string boundary;
    std::map<std::string, std::string> headers;

  public:
    WwwForm();

    void AddField(std::string &fieldName, std::string &value);
    void AddBinaryData(std::string &fieldName, std::vector<uint8_t> &contents);
    void AddBinaryData(std::string &fieldName, std::vector<uint8_t> &contents, std::string &fileName);
    void AddBinaryData(std::string &fieldName, std::vector<uint8_t> &contents, std::string &fileName, std::string &mimeType);

    std::map<std::string, std::string>& GetHeaders();
    void SetHeader(const std::string& key, const std::string& value);
    void RemoveHeader(const std::string& key);

    std::vector<uint8_t> GetData();
  };
}