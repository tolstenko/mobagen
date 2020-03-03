#pragma once

#include <cstdint>
#include <string>
#include <map>
#include "CaseInsensitiveCompare.hpp"
#include "Error.hpp"

namespace mobagen::networking {
  class Response {
  private:
    std::int32_t status_code;
    std::string text;
    std::map<std::string, std::string, CaseInsensitiveCompare> header;
    std::string url;
//    float elapsed;
//    Cookies cookies;
    Error error;
  };
}