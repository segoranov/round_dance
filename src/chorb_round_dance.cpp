#include "chorb_round_dance.hpp"

const std::list<ChorbDancer>& ChorbRoundDance::getDancers() const {
  return dancers;
}

bool ChorbRoundDance::addDancer(const std::string& newDancer,
                                const std::string& leftDancer,
                                const std::string& rightDancer) {
  return false;
}
