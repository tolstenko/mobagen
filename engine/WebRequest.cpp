#include <utility>

#include "WebRequest.hpp"
#include "Logger.hpp"
#include "HttpVerb.hpp"

namespace mobagen {
  WebRequest::WebRequest() {
    this->url = "";
    this->method = HttpVerbEnum::GET;
    this->headers = std::map<std::string, std::string>();
    this->body = "";

#if defined(USE_CURL)
    curl = curl_easy_init() ;
#endif
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

#if defined(USE_CURL)
    // TODO: this potentially calls "curl_global_init(CURL_GLOBAL_ALL);" so either we call it properly or make this line thread safe
    curl = curl_easy_init();
#endif
  }

  WebRequest::~WebRequest() {
#if defined(USE_CURL)
    if(curl!=nullptr)
      curl_easy_cleanup(curl);
    curl = nullptr;
#endif
  }

  // VERBS
  std::shared_ptr<WebRequest> WebRequest::Get(
      std::string url,
      const std::map<std::string, std::string>& headers) {
    return std::make_shared<WebRequest>(url,HttpVerbEnum::GET,headers);
  }

  void WebRequest::SendWebRequest() {
#if (defined(USE_CURL))
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(curl);
#endif
  }

  std::shared_ptr<WebRequest>
  WebRequest::Post(
      std::string url,
      const std::map<std::string, std::string> &headers,
      const std::string &data) {
    auto req = std::make_shared<WebRequest>(url,HttpVerbEnum::POST,headers,data);
  }

  std::string WebRequest::GetData() {
#if (defined(USE_CURL))
    return readBuffer;
#else
    return "";
#endif
  }


}
