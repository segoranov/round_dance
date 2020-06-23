#include "chorb_round_dance.hpp"

#include <cassert>

const std::list<ChorbDancer>& ChorbRoundDance::getDancers() const {
  return dancers;
}

bool ChorbRoundDance::addDancer(const std::string& newDancer,
                                const std::string& leftDancer,
                                const std::string& rightDancer) {
  assert(dancers.size() >= 3);
  // If leftDancer and rightDancer are not neighbors,
  // return false, print error message to the screen and do nothing.

  // TODO SG/DV
  // What if leftDancer and rightDancer do not exist in the dance? Maybe throw
  // NonExistingDancer exception or something like that?

  // Also, perform the check for no more than 30 symbol nickname.

  // We know that left dancer and right dancer are neighbors at this point.
  // We begin the adding process.
  // d1 (d1.5) d2 d3 d4 d5 d6

  // Locate the leftDancer (with iterator for example)
  // Locate the rightDancer
  // Make the leftDancer grab the newDancer to the right
  // Make the rightDancer grab the newDancer to the left
  // Add the newDancer in the list between leftDancer and rightDancer
}
