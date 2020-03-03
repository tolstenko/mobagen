#include "Request.hpp"

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
