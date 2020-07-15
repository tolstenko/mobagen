#pragma once
#include <exception>
#include <string>
namespace mobagen {
  class NotImplementedException : public std::exception {
  public:

    // Construct with given error message:
    NotImplementedException(const char *error = "Functionality not yet implemented!") {
      errorMessage = error;
    }

    // Provided for compatibility with std::exception.
    const char *what() const noexcept {
      return errorMessage.c_str();
    }

  private:

    std::string errorMessage;
  };

  class GenericException : public std::exception {
  public:

    // Construct with given error message:
    GenericException(const char *error = "Generic Error!") {
      errorMessage = error;
    }

    // Provided for compatibility with std::exception.
    const char *what() const noexcept {
      return errorMessage.c_str();
    }

  private:

    std::string errorMessage;
  };
}