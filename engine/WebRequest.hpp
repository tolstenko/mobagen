#pragma once
#include <string>
#include <map>
#include <memory>

// TODO: remove this
#if defined(__MINGW64__)
#define WINDOWS_LEAN_AND_MEAN
#include <winsock2.h>
#endif

#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
#include <cstdint> // TODO: remove this line
#include <curl/curl.h>
#include "DownloadHandler.hpp"
#endif

// TODO: move this to network namespace
namespace mobagen {
  class WebRequest {
  public:
    WebRequest();
    WebRequest(
        const std::string& url,
        std::map<std::string,std::string>headers=std::map<std::string,std::string>(),
        std::string body=nullptr);
    //WebRequest(Uri uri);
    //WebRequest(std::string url, std::string method);
    //WebRequest(Uri uri, string method);
    //WebRequest(std::string url, std::string method, Networking.DownloadHandler downloadHandler, Networking.UploadHandler uploadHandler);
    //WebRequest(Uri uri, string method, Networking.DownloadHandler downloadHandler, Networking.UploadHandler uploadHandler);
    ~WebRequest();

  private:

    public:
    // Retrieves the value of a custom request header.
    std::string GetRequestHeader(std::string name);
    // Retrieves the value of a response header from the latest HTTP response received.
    std::string GetResponseHeader(std::string name);
    // Retrieves a dictionary containing all the response headers received by this UnityWebRequest in the latest HTTP response.
    std::map<std::string, std::string> GetResponseHeaders();
    // Begin communicating with the remote server.
    void SendWebRequest();
    // Set a HTTP request header to a custom value.
    void SetRequestHeader(std::string name, std::string value);

    // TODO: Improve this to use download handler
    std::string GetData();
// static methods
//        ClearCookieCache	Clears stored cookies from the cache.
//        Delete	Creates a UnityWebRequest configured for HTTP DELETE.
//        EscapeURL	Escapes characters in a string to ensure they are URL-friendly.
//        GenerateBoundary	Generate a random 40-byte array for use as a multipart form boundary.

    // GetCreates a WebRequest configured to send a HTTP GET request.
    static std::shared_ptr<WebRequest> Get(std::string url);
//        Head	Creates a UnityWebRequest configured to send a HTTP HEAD request.
//        Post	Creates a UnityWebRequest configured to send form data to a server via HTTP POST.
//        Put	Creates a UnityWebRequest configured to upload raw data to a remote server via HTTP PUT.
//        SerializeFormSections	Converts a List of IMultipartFormSection objects into a byte array containing raw multipart form data.
//        SerializeSimpleForm	Serialize a dictionary of strings into a byte array containing URL-encoded UTF8 characters.
//        UnEscapeURL	Converts URL-friendly escape sequences back to normal text.

  private:
    // default method
    const std::string * method{};
    std::string url;

    std::map<std::string,std::string> headers;
    std::string body;

#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
    std::string readBuffer = "";

    static size_t WriteCallback(char *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    CURL* easyhandle;
#else

#endif
  };
}