#ifndef NICKNAME_GENERATOR_25062020
#define NICKNAME_GENERATOR_25062020

#include <iostream>
#include <string>
#include <vector>

class NicknameGenerator {
 public:
  static std::vector<std::string> fromStream(std::istream& is);
};

#endif
