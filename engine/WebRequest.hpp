#pragma once
#ifndef EMSCRIPTEN
#ifdef USE_CURL
#include <cpr/cpr.h>
#endif
#endif
#include <string>
#include <map>

namespace mobagen {
  enum class WebErrorCode {
    OK = 0,
    CONNECTION_FAILURE,
    EMPTY_RESPONSE,
    HOST_RESOLUTION_FAILURE,
    INTERNAL_ERROR,
    INVALID_URL_FORMAT,
    NETWORK_RECEIVE_ERROR,
    NETWORK_SEND_FAILURE,
    OPERATION_TIMEDOUT,
    PROXY_RESOLUTION_FAILURE,
    SSL_CONNECT_ERROR,
    SSL_LOCAL_CERTIFICATE_ERROR,
    SSL_REMOTE_CERTIFICATE_ERROR,
    SSL_CACERT_ERROR,
    GENERIC_SSL_ERROR,
    UNSUPPORTED_PROTOCOL,
    UNKNOWN_ERROR = 1000,
  };

  class WebResponse {
  public:
    int status_code;
    std::string text;
    std::map<std::string, std::string> header;
    std::string url;
    double elapsed;
    std::map<std::string, std::string> cookies;
    WebErrorCode error;
  };

  class WebRequest {

  public:
    WebRequest();

    void SetUrl(const std::string &url);

    void AddHeader(const std::string &key, const std::string &value);

    void SetAuth(const std::string &username, const std::string &password);

    void SetDigest(const std::string &username, const std::string &password);

    void SetBody(const std::string &body);

    void AddParameter(const std::string &key, const std::string &value);

    void AddMultiPart(const std::string &name, const std::string &value, const std::string &content_type = {});

    void AddMultiPart(const std::string &name, const std::int32_t &value, const std::string &content_type = {});

    void AddMultiPart(const std::string &name, const std::string &filename, const std::string &data,
                      const std::string &content_type);

    void SetCookies(const std::string &key, const std::string &value);

    void AddPayload(const std::string &key, const std::string &value);


    WebResponse Post();

    void Get();

  private:

#ifndef EMSCRIPTEN
#ifdef USE_CURL
    cpr::Session m_session;

    cpr::Cookies m_cookies;
    cpr::Header m_header;
    cpr::Parameters m_parameters;
    cpr::Multipart m_multipart = cpr::Multipart(std::initializer_list<cpr::Part>());
    cpr::Payload m_payload = cpr::Payload(std::initializer_list<cpr::Pair>());
    WebResponse m_response;
#endif
#else

#endif
  };
}