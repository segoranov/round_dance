#include "chorb_round_dance.hpp"

#include <cassert>

#include "chorb_dancer.hpp"

std::vector<ChorbDancer> ChorbRoundDance::getDancers() const {
  std::vector<ChorbDancer> result;
  result.push_back(*firstDancer);

  const ChorbDancer* currentDancer = firstDancer->getRightDancer();

  while (currentDancer != firstDancer) {
    result.push_back(*currentDancer);
    currentDancer = currentDancer->getRightDancer();
  }

  return result;
}

bool ChorbRoundDance::addDancer(const std::string& newDancerNickname,
                                const std::string& dancer1Nickname,
                                const std::string& dancer2Nickname) {
  // Below implementation is O(1)

  // We should have at least 3 dancers so that the round dance can take place!
  assert(mapNicknameToDancer.size() >= 3);

  // Perform the check for no more than 30 symbol nickname for newDancer.
  // TODO Unit test for above line and create hierarchy of exceptions to throw

  // Check whether dancers exist and throw exception if not
  // TODO create unit tests for below checks
  checkDancerExists(dancer1Nickname);
  checkDancerExists(dancer2Nickname);

  if (!areNeighbours(dancer1Nickname, dancer2Nickname)) {
    // TODO print error message (View?)
    return false;
  }

  // We know that dancer1Nickname and dancer2Nickname are neighbors at this
  // point. Let's find out who is the left one and who is the right one.

  ChorbDancer* leftDancer{nullptr};
  ChorbDancer* rightDancer{nullptr};

  if (mapNicknameToDancer[dancer2Nickname].getLeftDancer()->getNickname() ==
      dancer1Nickname) {
    leftDancer = &mapNicknameToDancer[dancer1Nickname];
    rightDancer = &mapNicknameToDancer[dancer2Nickname];
  } else {
    leftDancer = &mapNicknameToDancer[dancer2Nickname];
    rightDancer = &mapNicknameToDancer[dancer1Nickname];
  }

  // We begin the adding process.
  // Situation: d1 d2 d3(leftDancer) newDancer d4(rightDancer) d5 d6

  // Add the newDancer in the hash map
  mapNicknameToDancer.insert(
      {newDancerNickname, ChorbDancer{newDancerNickname}});

  // Locate the newDancer
  ChorbDancer* newDancer = &mapNicknameToDancer[newDancerNickname];

  // Make the leftDancer grab the newDancer to the right
  leftDancer->setRightDancer(newDancer);
  leftDancer->grabRightDancer();

  // Make the newDancer grab the leftDancer to the left
  newDancer->setLeftDancer(leftDancer);
  newDancer->grabLeftDancer();

  // Make the rightDancer grab the newDancer to the left
  rightDancer->setLeftDancer(newDancer);
  rightDancer->grabLeftDancer();

  // Make the newDancer grab the rightDancer to the right
  newDancer->setRightDancer(rightDancer);
  newDancer->grabRightDancer();

  // If added between the last and the first one,
  // the newDancer will be the last dancer from now on
  const bool addedBetweenLastAndFirst =
      (leftDancer == lastDancer && rightDancer == firstDancer) ||
      (leftDancer == firstDancer && rightDancer == lastDancer);

  if (addedBetweenLastAndFirst) {
    lastDancer = newDancer;
  }

  return true;
}

bool ChorbRoundDance::areNeighbours(
    const std::string& dancer1Nickname,
    const std::string& dancer2Nickname) noexcept {
  // TODO should we do check if they exist? Probably not, it's a private
  // function.

  ChorbDancer* dancer1 = &mapNicknameToDancer[dancer1Nickname];
  ChorbDancer* dancer2 = &mapNicknameToDancer[dancer2Nickname];

  // true if dancer1Nickname is to the left of dancer2Nickname
  const bool orderedD1D2 =
      dancer1->getRightDancer()->getNickname() == dancer2->getNickname() &&
      dancer2->getLeftDancer()->getNickname() == dancer1->getNickname();

  // true if dancer1Nickname is to the right of dancer2Nickname
  const bool orderedD2D1 =
      dancer1->getLeftDancer()->getNickname() == dancer2->getNickname() &&
      dancer2->getRightDancer()->getNickname() == dancer1->getNickname();

  return orderedD1D2 || orderedD2D1;
}

void ChorbRoundDance::checkDancerExists(const std::string& nickname) {
  if (!mapNicknameToDancer.contains(nickname)) {
    throw "The dancer " + nickname + " does not exist in the dance!";
    // TODO SG/DV create hierarchy of exceptions instead
  }
}
