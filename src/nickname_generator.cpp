#include "nickname_generator.hpp"

#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_director.hpp"

std::vector<std::string> NicknameGenerator::fromStream(std::istream& is) {
  /*
    Expected format is to have a dancer nickname on each row:
    dancer_1_Nickname
    dancer_2_Nickname
    ...
    dancer_N_nickname
    */

  std::vector<std::string> result;
  std::string nickname;
  while (std::getline(is, nickname)) {
    result.push_back(nickname);
  }

  return result;
}
