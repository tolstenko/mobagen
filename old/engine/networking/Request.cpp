#include <memory>
#include <Logger.hpp>
#include "Request.hpp"
#include <algorithm>

void mobagen::networking::Request::setHeader(std::string &key, std::string &value) {
  headers[key] = value;
}

void mobagen::networking::Request::setAttribute(std::string &key, std::string &value) {
  attributes[key] = value;
}

void mobagen::networking::Request::setMethod(mobagen::HttpVerbEnum verb) {
  method = verb;
}

void mobagen::networking::Request::setUrl(std::string& url) {
  this->url = url;
}

void mobagen::networking::Request::setData(std::string &data) {
  this->body = data;
}

void mobagen::networking::Request::send() {
  switch (this->method) {
    case HttpVerbEnum::POST:
      return;
    case HttpVerbEnum::GET:
      sendGet();
      return;
    default:
      log_err("%s", "Unsupported method");
      return;
  }
}

// todo: move this to a better place
std::vector<std::string> explode( const std::string &delimiter, const std::string &str)
{
  std::vector<std::string> arr;

  int strleng = str.length();
  int delleng = delimiter.length();
  if (delleng==0)
    return arr;//no change

  int i=0;
  int k=0;
  while( i<strleng )
  {
    int j=0;
    while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
      j++;
    if (j==delleng)//found delimiter
    {
      arr.push_back(  str.substr(k, i-k) );
      i+=delleng;
      k=i;
    }
    else
    {
      i++;
    }
  }
  arr.push_back(  str.substr(k, i-k) );
  return arr;
}

void mobagen::networking::Request::sendGet() {
#if defined(EMSCRIPTEN) && defined(USE_CURL)

#elif defined(USE_CURL)
  CURLcode res;

  curl = curl_easy_init(); // todo: make this thread safe
  // set url
  curl_easy_setopt(curl, CURLOPT_URL, this->url.c_str());
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  // set verb
  curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

  // disable check ssl issuer
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

  // set header
  struct curl_slist *list = nullptr;
  for (const auto& element : headers) {
    auto key = element.first;
    auto value = element.second;
    auto entry = key;
    entry = entry.append(": ");
    entry = entry.append(value);
    list = curl_slist_append(list, std::string(entry).c_str());
  }
  if(!headers.empty())
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

  std::shared_ptr<Response> response = std::make_shared<Response>();
  response->url = url;

  // set read buffer
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response->text);

  // set header buffer
  std::string headerBuffer;
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteCallback);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &headerBuffer);

  // set progress
  // https://curl.haxx.se/libcurl/c/progressfunc.html
  if(onUpdate) {
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progressFunc);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA, this);
  }

  // run it baby
  res = curl_easy_perform(curl);
  // if we face some problems
  if(res != CURLE_OK) {
    response->error.message = curl_easy_strerror(res);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response->error.code);
    if(onError!= nullptr)
      onError(response);
    curl_slist_free_all(list);
    curl_easy_cleanup(curl);
    return;
  }

  // status
  curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &response->status_code);

  // process header
  auto lines = explode("\r\n", headerBuffer);
  for(const auto& line : lines){
    if(!line.empty()) {
      auto pair = explode(": ", line);
      if(pair.size()==2)
        response->headers[pair[0]] = pair[1];
    }
  }

  onSuccess(response);

  // free
  curl_slist_free_all(list);
  curl_easy_cleanup(curl);
#endif
}

size_t mobagen::networking::Request::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
  ((std::string*)userp)->append((char*)contents, size * nmemb);
   return size * nmemb;
}

void mobagen::networking::Request::setHeaders(std::map<std::string, std::string> &headers) {
  std::for_each(headers.begin(), headers.end(),
      [this](auto element){
    auto key = element.first;
    auto value = element.second;
    this->headers[key] = value;
  });
}

int mobagen::networking::Request::progressFunc(void *p, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal,
                                               curl_off_t ulnow) {
  // todo: check if this pointer is valid
  auto *req = (Request *)p;

  if(req->onUpdate){
    float upload=0, download=0;
    if(ultotal>0)
      upload = (float)ulnow/(float)ultotal;
    if(dltotal>0)
      download = (float)dlnow/(float)dltotal;

    if(download>upload)
      return (int)req->onUpdate(download);
    else
      return (int)req->onUpdate(upload);
  }
  else
    return 1;
}
