#include "chorb_round_dance.hpp"

#include <cassert>

#include "chorb_dancer.hpp"

const std::list<ChorbDancer>& ChorbRoundDance::getDancers() const {
  return dancers;
}

bool ChorbRoundDance::addDancer(const std::string& newDancerNickname,
                                const std::string& leftDancerNickname,
                                const std::string& rightDancerNickname) {
  assert(dancers.size() >= 3);

  if (!areNeighbours(leftDancerNickname, rightDancerNickname)) {
    // TODO print error message (View?)
    return false;
  }

  // TODO SG/DV
  // What if leftDancer and rightDancer do not exist in the dance? Maybe throw
  // NonExistingDancer exception or something like that?
  // TODO Create unit test for above lines

  // Also, perform the check for no more than 30 symbol nickname.
  // TODO Unit test for above line

  // We know that left dancer and right dancer are neighbors at this point.
  // We begin the adding process.
  // d1 (d1.5) d2 d3 d4 d5 d6

  // Locate the leftDancer
  auto itLeftDancer = locateDancer(leftDancerNickname);

  // Locate the rightDancer
  auto itRightDancer = locateDancer(rightDancerNickname);

  // Add the newDancer in the list between leftDancer and rightDancer
  dancers.insert(itRightDancer, ChorbDancer{newDancerNickname});

  // Locate the newDancer
  auto itNewDancer = locateDancer(newDancerNickname);

  // Make the leftDancer grab the newDancer to the right
  itLeftDancer->setRightDancer(&(*itNewDancer));
  itLeftDancer->grabRightDancer();

  // Make the newDancer grab the leftDancer to the left
  itNewDancer->setLeftDancer(&(*itLeftDancer));
  itNewDancer->grabLeftDancer();

  // Make the rightDancer grab the newDancer to the left
  itRightDancer->setLeftDancer(&(*itNewDancer));
  itRightDancer->grabLeftDancer();

  // Make the newDancer grab the rightDancer to the right
  itNewDancer->setRightDancer(&(*itRightDancer));
  itNewDancer->grabRightDancer();

  return true;
}

bool ChorbRoundDance::areNeighbours(const std::string& dancer1,
                                    const std::string& dancer2) noexcept {
  auto itDancer1 = locateDancer(dancer1);
  auto itDancer2 = locateDancer(dancer1);

  return (itDancer1->getRightDancer() == &(*itDancer2) &&
          itDancer2->getLeftDancer() == &(*itDancer1))

         ||

         (itDancer1->getLeftDancer() == &(*itDancer2) &&
          itDancer2->getRightDancer() == &(*itDancer1));
}

std::list<ChorbDancer>::iterator ChorbRoundDance::locateDancer(
    const std::string& nickname) {
  auto it = dancers.begin();
  while (it->getNickname() != nickname) ++it;
  return it;
};
