#pragma once

#include <string>
#include <map>

namespace mobagen {
  enum class HttpVerbEnum {
    CONNECT,
    CREATE,
    DELETE,
    GET,
    HEAD,
    OPTIONS,
    PATCH,
    POST,
    PUT,
    TRACE
  };

  class HttpVerb {
  public:
    inline static const std::string CONNECT = "CONNECT";
    inline static const std::string CREATE = "CREATE";
    inline static const std::string DELETE = "DELETE";
    inline static const std::string GET = "GET";
    inline static const std::string HEAD = "HEAD";
    inline static const std::string OPTIONS = "OPTIONS";
    inline static const std::string PATCH = "PATCH";
    inline static const std::string POST = "POST";
    inline static const std::string PUT = "PUT";
    inline static const std::string TRACE = "TRACE";

    static std::string fromEnum(HttpVerbEnum verb) {
      return enumToStr[verb];
    };

    static HttpVerbEnum toEnum(std::string verb) {
      return strToEnum[verb];
    };

  private:
    inline static std::map<HttpVerbEnum, std::string> enumToStr = {
        {HttpVerbEnum::CONNECT, HttpVerb::CONNECT},
        {HttpVerbEnum::CREATE,  HttpVerb::CREATE},
        {HttpVerbEnum::DELETE,  HttpVerb::DELETE},
        {HttpVerbEnum::GET,     HttpVerb::GET},
        {HttpVerbEnum::HEAD,    HttpVerb::HEAD},
        {HttpVerbEnum::OPTIONS, HttpVerb::OPTIONS},
        {HttpVerbEnum::PATCH,   HttpVerb::PATCH},
        {HttpVerbEnum::POST,    HttpVerb::POST},
        {HttpVerbEnum::PUT,     HttpVerb::PUT},
        {HttpVerbEnum::TRACE,   HttpVerb::TRACE},
    };
    inline static std::map<std::string, HttpVerbEnum> strToEnum = {
        {HttpVerb::CONNECT, HttpVerbEnum::CONNECT},
        {HttpVerb::CREATE,  HttpVerbEnum::CREATE},
        {HttpVerb::DELETE,  HttpVerbEnum::DELETE},
        {HttpVerb::GET,     HttpVerbEnum::GET},
        {HttpVerb::HEAD,    HttpVerbEnum::HEAD},
        {HttpVerb::OPTIONS, HttpVerbEnum::OPTIONS},
        {HttpVerb::PATCH,   HttpVerbEnum::PATCH},
        {HttpVerb::POST,    HttpVerbEnum::POST},
        {HttpVerb::PUT,     HttpVerbEnum::PUT},
        {HttpVerb::TRACE,   HttpVerbEnum::TRACE},
    };
  };
}
