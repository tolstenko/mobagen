#pragma once

#include <map>
#include <string>
#include <HttpVerb.hpp>
#include <functional>
#include "CaseInsensitiveCompare.hpp"
#include "Response.hpp"

#if defined(EMSCRIPTEN) && defined(USE_CURL)
#elif defined(USE_CURL)
#include <curl/curl.h>
#endif

namespace mobagen::networking {
  class Request {
  private:
    std::map<std::string, std::string, CaseInsensitiveCompare> headers;
    std::map<std::string, std::string> attributes;
    HttpVerbEnum method;
    std::string url;
    std::string body;
    std::function<void(std::shared_ptr<Response>)> onSuccess;
#if defined(EMSCRIPTEN) && defined(USE_CURL)
#elif defined(USE_CURL)
    CURL* curl;
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
#endif
  public:
    void setHeader(std::string &key, std::string &value);
    void setHeaders(std::map<std::string, std::string> &headers);
    void setAttribute(std::string &key, std::string &value);
    void setMethod(HttpVerbEnum verb);
    void setUrl(std::string& url);
    void setData(std::string& data);
    void send();
    void setOnSuccess(std::function<void(std::shared_ptr<Response>)> &);
    // update
    // error
  private:
    void sendGet();
  };

}