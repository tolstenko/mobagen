#pragma once

#include <map>
#include <string>
#include <HttpVerb.hpp>
#include "CaseInsensitiveCompare.hpp"

namespace mobagen::networking {
  class Request {
  private:
    std::map<std::string, std::string, CaseInsensitiveCompare> headers;
    std::map<std::string, std::string> attributes;
    HttpVerbEnum method;
    std::string url;
    std::string body;
  public:
    void setHeader(std::string &key, std::string &value);
    void setAttribute(std::string &key, std::string &value);
    void setMethod(HttpVerbEnum verb);
    void setUrl(std::string& url);
    void setData(std::string& data);
  };

}