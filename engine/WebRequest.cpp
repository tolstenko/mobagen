#include <utility>

#include "WebRequest.hpp"
#include "Logger.hpp"
#include "HttpVerb.hpp"

#include "WwwTranscoder.hpp"

namespace mobagen {
  WebRequest::WebRequest() {
    this->url = "";
    this->method = HttpVerbEnum::GET;
    this->headers = std::map<std::string, std::string>();
    this->body = "";
  }

  WebRequest::WebRequest(
      const std::string &url,
      const HttpVerbEnum &method,
      const std::map<std::string, std::string>& headers,
      const std::string &body) {
    this->url = url;
    this->method = method;
    this->headers = headers;
    this->body = body;
  }

  WebRequest::~WebRequest() {
#if defined(USE_CURL)

#endif
  }

  // VERBS
  void
  WebRequest::Get(
      std::string &url,
      const std::map<std::string, std::string>& headers,
      const std::function<void(std::string, std::string)>& onFinish) {
#if defined(EMSCRIPTEN) && defined(USE_CURL)
#elif defined(USE_CURL)
    cpr::Header h = (const std::map<std::basic_string<char>, std::basic_string<char>, cpr::CaseInsensitiveCompare> &) headers;
    cpr::GetCallback([onFinish](const cpr::Response& r) {
      onFinish(r.error.message,r.text);
      return r.text;
    },cpr::Url(url), h);
#endif
  }

  void
  WebRequest::Post(
      std::string &url,
      const std::map<std::string, std::string> &headers,
      const std::string &data,
      const std::function<void(std::string, std::string)>& onFinish) {
#if defined(EMSCRIPTEN) && defined(USE_CURL)
#elif defined(USE_CURL)
    cpr::PostCallback([onFinish](const cpr::Response& r) {
      onFinish(r.error.message,r.text);
      return r.text;
    },cpr::Url(url), cpr::Body{data}, headers);
#endif
  }

  std::string WebRequest::GetData() {
#if (defined(USE_CURL))
    return "";
#else
    return "";
#endif
  }




}
