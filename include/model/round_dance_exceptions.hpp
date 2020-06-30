#ifndef ROUND_DANCE_EXCEPTIONS_HPP_29062020
#define ROUND_DANCE_EXCEPTIONS_HPP_29062020

#include <stdexcept>
#include <string>

class ChorbRoundDanceException : public std::runtime_error {
 public:
  explicit ChorbRoundDanceException(
      const std::string& message = "ChorbRoundDanceException")
      : std::runtime_error(message) {}
};

class InvalidDirectionException : public ChorbRoundDanceException {
 public:
  explicit InvalidDirectionException(
      const std::string& message = "InvalidDirectionException")
      : ChorbRoundDanceException(message) {}
};

class InvalidCommandException : public ChorbRoundDanceException {
 public:
  explicit InvalidCommandException(
      const std::string& message = "InvalidCommandException")
      : ChorbRoundDanceException(message) {}
};

class NonExistingDancerException : public ChorbRoundDanceException {
 public:
  explicit NonExistingDancerException(
      const std::string& message = "NonExistingDancerException")
      : ChorbRoundDanceException(message) {}
};

#endif
