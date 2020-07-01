#ifndef ROUND_DANCE_EXCEPTIONS_HPP_29062020
#define ROUND_DANCE_EXCEPTIONS_HPP_29062020

#include <stdexcept>
#include <string>

//!  A ChorbRoundDanceException class that public inherits std::runtime_error.
class ChorbRoundDanceException : public std::runtime_error {
 public:
  explicit ChorbRoundDanceException(
      const std::string& message = "ChorbRoundDanceException")
      : std::runtime_error(message) {}
};

//!  A InvalidDirectionException class that public inherits ChorbRoundDanceException
class InvalidDirectionException : public ChorbRoundDanceException {
 public:
  explicit InvalidDirectionException(
      const std::string& message = "InvalidDirectionException")
      : ChorbRoundDanceException(message) {}
};

//!  A InvalidCommandException class that public inherits ChorbRoundDanceException
class InvalidCommandException : public ChorbRoundDanceException {
 public:
  explicit InvalidCommandException(
      const std::string& message = "InvalidCommandException")
      : ChorbRoundDanceException(message) {}
};

//!  A NonExistingDancerException class that public inherits ChorbRoundDanceException.
class NonExistingDancerException : public ChorbRoundDanceException {
 public:
  explicit NonExistingDancerException(
      const std::string& message = "NonExistingDancerException")
      : ChorbRoundDanceException(message) {}
};

#endif
