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
    cpr::GetCallback([onFinish](const cpr::Response & r) {
      onFinish(r.error.message,r.text);
      return r.text;
    },cpr::Url(url), headers);
#endif
  }

  void WebRequest::SendWebRequest() {
#if (defined(USE_CURL))

#endif
  }

  std::shared_ptr<WebRequest>
  WebRequest::Post(
      std::string url,
      const std::map<std::string, std::string> &headers,
      const std::string &data) {
  }

//  std::shared_ptr<WebRequest>
//  WebRequest::Post(std::string url,
//                   std::shared_ptr<WwwForm> form) {
//    return std::make_shared<WebRequest>(url,HttpVerbEnum::POST, form->GetHeaders(), form->GetData());
//  }

  std::string WebRequest::GetData() {
#if (defined(USE_CURL))
    return "";
#else
    return "";
#endif
  }




}
