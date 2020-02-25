#include <utility>

#include "WebRequest.hpp"
#include "Logger.hpp"

namespace mobagen {

  WebRequest::WebRequest() {

    method = &HttpVerb::GET
#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
    easyhandle = nullptr;
    curl_global_init(CURL_GLOBAL_ALL);
#else
#endif
  }

  WebRequest::WebRequest(std::string url) {
    
    method = &kHttpVerbGET;
    this->url = std::move(url);
#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
    curl_global_init(CURL_GLOBAL_ALL);
    easyhandle = nullptr;
#else
#endif
  }

  WebRequest::~WebRequest() {
#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
    if(easyhandle!=nullptr)
      curl_easy_cleanup(easyhandle);
    easyhandle = nullptr;
    curl_global_cleanup(); // TODO: inspect if this is necessary
#endif
  }

  std::shared_ptr<WebRequest> WebRequest::Get(std::string url) {
    std::shared_ptr<WebRequest> req = std::make_shared<WebRequest>();

    req->method = &kHttpVerbGET;
    req->url = std::move(url);
    return req;
  }

  std::string WebRequest::GetRequestHeader(std::string name) {
    return requestHeaders[name];
  }

  std::string WebRequest::GetResponseHeader(std::string name) {
    return responseHeaders[name];
  }

  std::map<std::string, std::string> WebRequest::GetResponseHeaders() {
    return responseHeaders;
  }

  void WebRequest::SetRequestHeader(std::string name, std::string value) {
    requestHeaders[name] = value;
  }

  void WebRequest::SendWebRequest() {
#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
    easyhandle = curl_easy_init();
    curl_easy_setopt(easyhandle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(easyhandle, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(easyhandle, CURLOPT_WRITEDATA, &readBuffer);

    curl_easy_perform(easyhandle);
#endif
  }

  std::string WebRequest::GetData() {
#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
    return readBuffer;
#else
    return "";
#endif
  }
  
  WebRequest::WebRequest(const std::string& url, HttpVerb  std::map<std::string, std::string> headers, std::string body) {
    this->url = url;
    this->headers = headers;
    this->body = body;
  }
}
