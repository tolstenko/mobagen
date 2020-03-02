#pragma once
#include <string>
#include <map>
#include <memory>
#include "HttpVerb.hpp"
#include "WwwForm.hpp"
#if USE_CURL
  #include <cpr/cpr.h>
  #include <curl/curl.h>
#elif EMSCRIPTEN
  #include <emscripten/fetch.h>
#endif

// TODO: move this to network namespace
namespace mobagen {
  class WebRequest {
  public:
    WebRequest();
    WebRequest(const std::string &url,
               const HttpVerbEnum &method,
               const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(),
               const std::string &body = "");
    //WebRequest(Uri uri);
    //WebRequest(std::string url, std::string method);
    //WebRequest(Uri uri, string method);
    //WebRequest(std::string url, std::string method, Networking.DownloadHandler downloadHandler, Networking.UploadHandler uploadHandler);
    //WebRequest(Uri uri, string method, Networking.DownloadHandler downloadHandler, Networking.UploadHandler uploadHandler);
    ~WebRequest();

    // Retrieves the value of a custom request header.
//    std::string GetRequestHeader(std::string name);
    // Retrieves the value of a response header from the latest HTTP response received.
//    std::string GetResponseHeader(std::string name);
    // Retrieves a dictionary containing all the response headers received by this UnityWebRequest in the latest HTTP response.
//    std::map<std::string, std::string> GetResponseHeaders();
    // Begin communicating with the remote server.
    void SendWebRequest();
    // Set a HTTP request header to a custom value.
//    void SetRequestHeader(std::string name, std::string value);

    // TODO: Improve this to use download handler
    std::string GetData();
// static methods
//        ClearCookieCache	Clears stored cookies from the cache.
//        Delete	Creates a UnityWebRequest configured for HTTP DELETE.
//        EscapeURL	Escapes characters in a string to ensure they are URL-friendly.
//        GenerateBoundary	Generate a random 40-byte array for use as a multipart form boundary.

  public:
    // Static VERBS functions

    // Get Creates a WebRequest configured to send a HTTP GET request.
    static void Get(
        std::string &url,
        const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(),
        const std::function<void(std::string, std::string)>& callback = nullptr);
//        Head	Creates a UnityWebRequest configured to send a HTTP HEAD request.
//        Post	Creates a UnityWebRequest configured to send form data to a server via HTTP POST.
    static std::shared_ptr<WebRequest> Post(
        std::string url,
        const std::map<std::string, std::string>& headers = std::map<std::string, std::string>(),
        const std::string &data = "");

//    static std::shared_ptr<WebRequest> Post(
//        std::string url,
//        std::shared_ptr<WwwForm> form = nullptr);
//        Put	Creates a UnityWebRequest configured to upload raw data to a remote server via HTTP PUT.
//        SerializeFormSections	Converts a List of IMultipartFormSection objects into a byte array containing raw multipart form data.
//        SerializeSimpleForm	Serialize a dictionary of strings into a byte array containing URL-encoded UTF8 characters.
//        UnEscapeURL	Converts URL-friendly escape sequences back to normal text.

  private:
    // default method
    HttpVerbEnum method;
    std::string url;

    std::map<std::string,std::string> headers;
    std::string body;



#if defined(EMSCRIPTEN) && defined(USE_CURL)
    void downloadProgress(emscripten_fetch_t *fetch) {
      if (fetch->totalBytes) {
        printf("Downloading %s.. %.2f%% complete.\n", fetch->url, fetch->dataOffset * 100.0 / fetch->totalBytes);
      } else {
        printf("Downloading %s.. %lld bytes complete.\n", fetch->url, fetch->dataOffset + fetch->numBytes);
      }
    }
    void downloadSucceeded(emscripten_fetch_t *fetch) {
      printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
      // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
      emscripten_fetch_close(fetch); // Free data associated with the fetch.
    }

    void downloadFailed(emscripten_fetch_t *fetch) {
      printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
      emscripten_fetch_close(fetch); // Also free data on failure.
    }
#elif defined(USE_CURL)
    void setupProgress(){
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    }
#endif
  };
}