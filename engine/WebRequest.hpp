#pragma once
#include <string>
#include <map>
#include <memory>

#if (defined(APPLE) || defined (__MINGW64__)) && defined(USE_CURL)
#include <curl/curl.h>
#include "DownloadHandler.hpp"
#endif

// TODO: move this to network namespace
namespace mobagen {
  class WebRequest {
  public:
    WebRequest();
    WebRequest(std::string url);
    //WebRequest(Uri uri);
    //WebRequest(std::string url, std::string method);
    //WebRequest(Uri uri, string method);
    //WebRequest(std::string url, std::string method, Networking.DownloadHandler downloadHandler, Networking.UploadHandler uploadHandler);
    //WebRequest(Uri uri, string method, Networking.DownloadHandler downloadHandler, Networking.UploadHandler uploadHandler);
    ~WebRequest();

    // TODO: change these verbs to enum
    // The string "CREATE", commonly used as the verb for an HTTP CREATE request.
    static const std::string kHttpVerbCREATE;
    // The string "DELETE", commonly used as the verb for an HTTP DELETE request.
    static const std::string kHttpVerbDELETE;
    // The string "GET", commonly used as the verb for an HTTP GET request.
    static const std::string kHttpVerbGET;
    // The string "HEAD", commonly used as the verb for an HTTP HEAD request.
    static const std::string kHttpVerbHEAD;
    // The string "POST", commonly used as the verb for an HTTP POST request.
    static const std::string kHttpVerbPOST;
    // The string "PUT", commonly used as the verb for an HTTP PUT request.
    static const std::string kHttpVerbPUT;

// properties
//      certificateHandler	Holds a reference to a CertificateHandler object, which manages certificate validation for this UnityWebRequest.
//      chunkedTransfer	Indicates whether the UnityWebRequest system should employ the HTTP/1.1 chunked-transfer encoding method.
//      disposeCertificateHandlerOnDispose	If true, any CertificateHandler attached to this UnityWebRequest will have CertificateHandler.Dispose called automatically when UnityWebRequest.Dispose is called.
//      disposeDownloadHandlerOnDispose	If true, any DownloadHandler attached to this UnityWebRequest will have DownloadHandler.Dispose called automatically when UnityWebRequest.Dispose is called.
//      disposeUploadHandlerOnDispose	If true, any UploadHandler attached to this UnityWebRequest will have UploadHandler.Dispose called automatically when UnityWebRequest.Dispose is called.
//      downloadedBytes	Returns the number of bytes of body data the system has downloaded from the remote server. (Read Only)
    // Holds a reference to a DownloadHandler object, which manages body data received from the remote server by this UnityWebRequest.
    // std::shared_ptr<DownloadHandler> downloadHandler = std::make_shared<DownloadHandler>();
//      downloadProgress	Returns a floating-point value between 0.0 and 1.0, indicating the progress of downloading body data from the server. (Read Only)
//      error	A human-readable string describing any system errors encountered by this UnityWebRequest object while handling HTTP requests or responses. (Read Only)
//      isDone	Returns true after the UnityWebRequest has finished communicating with the remote server. (Read Only)
//      isHttpError	Returns true after this UnityWebRequest receives an HTTP response code indicating an error. (Read Only)
//      isModifiable	Returns true while a UnityWebRequest’s configuration properties can be altered. (Read Only)
//      isNetworkError	Returns true after this UnityWebRequest encounters a system error. (Read Only)
//      method	Defines the HTTP verb used by this UnityWebRequest, such as GET or POST.
//      redirectLimit	Indicates the number of redirects which this UnityWebRequest will follow before halting with a “Redirect Limit Exceeded” system error.
//      responseCode	The numeric HTTP response code returned by the server, such as 200, 404 or 500. (Read Only)
//      timeout	Sets UnityWebRequest to attempt to abort after the number of seconds in timeout have passed.
//      uploadedBytes	Returns the number of bytes of body data the system has uploaded to the remote server. (Read Only)
//      uploadHandler	Holds a reference to the UploadHandler object which manages body data to be uploaded to the remote server.
//      uploadProgress	Returns a floating-point value between 0.0 and 1.0, indicating the progress of uploading body data to the server.
//      uri	Defines the target URI for the UnityWebRequest to communicate with.
//      url	Defines the target URL for the UnityWebRequest to communicate with.
//      useHttpContinue	Determines whether this UnityWebRequest will include Expect: 100-Continue in its outgoing request headers. (Default: true).


// public methods
//        Abort	If in progress, halts the UnityWebRequest as soon as possible.
//        Dispose	Signals that this UnityWebRequest is no longer being used, and should clean up any resources it is using.
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
    const std::string * method;
    std::string url;

    std::map<std::string,std::string> requestHeaders;
    std::map<std::string,std::string> responseHeaders;

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