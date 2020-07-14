#include "model/chorb_round_dance.hpp"

#include <algorithm>
#include <cassert>

#include "model/chorb_dancer.hpp"
#include "model/round_dance_exceptions.hpp"

std::vector<ChorbDancer> ChorbRoundDance::getDancers() const {
  std::vector<ChorbDancer> result;
  result.push_back(*pFirstDancer);

  const ChorbDancer* currentDancer = pFirstDancer->getRightDancer();

  while (currentDancer != pFirstDancer) {
    result.push_back(*currentDancer);
    currentDancer = currentDancer->getRightDancer();
  }

  return result;
}

bool ChorbRoundDance::addDancer(const std::string& newDancer,
                                const std::string& dancer1,
                                const std::string& dancer2) {
  // Below implementation is O(1)

  // We should have at least 3 dancers so that the round dance can take place!
  assert(mapNicknameToDancer.size() >= 3);

  // Perform the check for no more than 30 symbol nickname for newDancer.
  // TODO Unit test for above line and create hierarchy of exceptions to throw

  // Check whether dancers exist and throw exception if not
  // TODO create unit tests for below checks
  checkDancerExists(dancer1);
  checkDancerExists(dancer2);

  if (!areNeighbours(dancer1, dancer2)) {
    return false;
  }

  // We know that dancer1 and dancer2 are neighbors at this
  // point. Let's find out who is the left one and who is the right one.
  auto [pLeftDancer, pRightDancer] = getLeftAndRightDancers(dancer1, dancer2);

  // We begin the adding process.
  // Situation: d1 d2 d3(leftDancer) newDancer d4(rightDancer) d5 d6

  // Add the newDancer in the hash map
  mapNicknameToDancer.insert({newDancer, ChorbDancer{newDancer}});

  // Locate the newDancer
  ChorbDancer* pNewDancer = &mapNicknameToDancer[newDancer];

  // Make the leftDancer grab the newDancer to the right
  pLeftDancer->setRightDancer(pNewDancer);
  pLeftDancer->grabRightDancer();

  // Make the newDancer grab the leftDancer to the left
  pNewDancer->setLeftDancer(pLeftDancer);
  pNewDancer->grabLeftDancer();

  // Make the rightDancer grab the newDancer to the left
  pRightDancer->setLeftDancer(pNewDancer);
  pRightDancer->grabLeftDancer();

  // Make the newDancer grab the rightDancer to the right
  pNewDancer->setRightDancer(pRightDancer);
  pNewDancer->grabRightDancer();

  // If added between the last and the first one,
  // the newDancer will be the last dancer from now on
  const bool addedBetweenLastAndFirst =
      (pLeftDancer == pLastDancer && pRightDancer == pFirstDancer) ||
      (pLeftDancer == pFirstDancer && pRightDancer == pLastDancer);

  if (addedBetweenLastAndFirst) {
    pLastDancer = pNewDancer;
  }

  return true;
}

bool ChorbRoundDance::areNeighbours(const std::string& dancer1,
                                    const std::string& dancer2) noexcept {
  ChorbDancer* pDancer1 = &mapNicknameToDancer[dancer1];
  ChorbDancer* pDancer2 = &mapNicknameToDancer[dancer2];

  // true if pDancer1 is to the left of pDancer2
  const bool orderedD1D2 =
      pDancer1->getRightDancer()->getNickname() == pDancer2->getNickname() &&
      pDancer2->getLeftDancer()->getNickname() == pDancer1->getNickname();

  // true if pDancer1 is to the right of pDancer2
  const bool orderedD2D1 =
      pDancer1->getLeftDancer()->getNickname() == pDancer2->getNickname() &&
      pDancer2->getRightDancer()->getNickname() == pDancer1->getNickname();

  return orderedD1D2 || orderedD2D1;
}

void ChorbRoundDance::checkDancerExists(const std::string& nickname) {
  if (!mapNicknameToDancer.contains(nickname)) {
    throw NonExistingDancerException{"The dancer " + nickname +
                                     " does not exist in the dance!"};
  }
}

std::optional<ChorbDancer> ChorbRoundDance::getDancer(
    const std::string& dancer) {
  if (!mapNicknameToDancer.contains(dancer)) {
    return std::nullopt;
  } else {
    return mapNicknameToDancer[dancer];  // implicitly constructs optional
  }
}

void ChorbRoundDance::grab(const std::string& dancer,
                           Direction grabbingDirection) {
  checkDancerExists(dancer);
  switch (grabbingDirection) {
    case Direction::LEFT: {
      mapNicknameToDancer[dancer].grabLeftDancer();
      break;
    }

    case Direction::RIGHT: {
      mapNicknameToDancer[dancer].grabRightDancer();
      break;
    }

    case Direction::BOTH: {
      mapNicknameToDancer[dancer].grabLeftDancer();
      mapNicknameToDancer[dancer].grabRightDancer();
      break;
    }
  }
}

void ChorbRoundDance::release(const std::string& dancer,
                              Direction releaseDirection) {
  checkDancerExists(dancer);
  switch (releaseDirection) {
    case Direction::LEFT: {
      mapNicknameToDancer[dancer].releaseLeftDancer();
      break;
    }

    case Direction::RIGHT: {
      mapNicknameToDancer[dancer].releaseRightDancer();
      break;
    }

    case Direction::BOTH: {
      mapNicknameToDancer[dancer].releaseLeftDancer();
      mapNicknameToDancer[dancer].releaseRightDancer();
      break;
    }
  }
}

bool ChorbRoundDance::removeDancer(const std::string& dancer) {
  checkDancerExists(dancer);

  if (mapNicknameToDancer[dancer].hasGrabbedLeftDancer() ||
      mapNicknameToDancer[dancer].hasGrabbedRightDancer() ||
      mapNicknameToDancer[dancer].getLeftDancer()->hasGrabbedRightDancer() ||
      mapNicknameToDancer[dancer].getRightDancer()->hasGrabbedLeftDancer()) {
    return false;
  }

  ChorbDancer* toBeRemoved = &mapNicknameToDancer[dancer];
  ChorbDancer* pLeftDancer =
      &mapNicknameToDancer[toBeRemoved->getLeftDancer()->getNickname()];
  ChorbDancer* pRightDancer =
      &mapNicknameToDancer[toBeRemoved->getRightDancer()->getNickname()];

  // TODO Should left and right dancer grab themselves after removing the dancer
  // in-between them. Not mentioned in SRS?
  pLeftDancer->setRightDancer(pRightDancer);
  pLeftDancer->grabRightDancer();

  pRightDancer->setLeftDancer(pLeftDancer);
  pRightDancer->grabLeftDancer();

  mapNicknameToDancer.erase(dancer);

  if (toBeRemoved == pFirstDancer) {
    pFirstDancer = pRightDancer;
  } else if (toBeRemoved == pLastDancer) {
    pLastDancer = pLeftDancer;
  }

  return true;
}

bool ChorbRoundDance::swap(const std::string& dancer1,
                           const std::string& dancer2) {
  checkDancerExists(dancer1);
  checkDancerExists(dancer2);

  if (!areNeighbours(dancer1, dancer2)) {
    return false;
  }

  // We know that dancer1 and dancer2 are neighbors at this
  // point. Let's find out who is the left one and who is the right one.
  auto [pLeftDancer, pRightDancer] = getLeftAndRightDancers(dancer1, dancer2);

  ChorbDancer* pLeftLeftDancer =
      &mapNicknameToDancer[pLeftDancer->getLeftDancer()->getNickname()];

  ChorbDancer* pRightRightDancer =
      &mapNicknameToDancer[pRightDancer->getRightDancer()->getNickname()];

  // Explanation:
  // If we have d1 d2 d3 d4 and we want to swap d3 and d2, then:
  // d1 is leftLeftDancer
  // d2 is leftDancer
  // d3 is rightDancer
  // d4 is rightRightDancer

  if (pLeftLeftDancer->hasGrabbedRightDancer() ||
      pRightRightDancer->hasGrabbedLeftDancer()) {
    // Cannot swap if they are grabbed by their neighbours
    return false;
  }

  // The algorithm for swapping begins now, after we know we can do it

  // We want to get from 'd1 d2 d3 d4' to 'd1 d3 d2 d4'
  // The algorithm also works if we have only 3 dancers 'd1 d2 d3'

  pLeftDancer->setLeftDancer(pRightDancer);
  pLeftDancer->setRightDancer(pRightRightDancer);

  pRightDancer->setRightDancer(pLeftDancer);
  pRightDancer->setLeftDancer(pLeftLeftDancer);

  pLeftLeftDancer->setRightDancer(pRightDancer);
  pRightRightDancer->setLeftDancer(pLeftDancer);

  if (pFirstDancer == pRightDancer) {
    // means we have swapped the first and the last one
    std::swap(pFirstDancer, pLastDancer);
  } else if (pFirstDancer == pLeftDancer) {
    // means we have swapped the first and the second one
    pFirstDancer = pRightDancer;
  } else if (pLastDancer == pRightDancer) {
    // means we have swapped the last and the before last dancer
    pLastDancer = pLeftDancer;
  }

  return true;
}

std::pair<ChorbDancer*, ChorbDancer*> ChorbRoundDance::getLeftAndRightDancers(
    const std::string& dancer1, const std::string& dancer2) {
  ChorbDancer* pLeftDancer{nullptr};
  ChorbDancer* pRightDancer{nullptr};

  if (mapNicknameToDancer[dancer2].getLeftDancer()->getNickname() == dancer1) {
    pLeftDancer = &mapNicknameToDancer[dancer1];
    pRightDancer = &mapNicknameToDancer[dancer2];
  } else {
    pLeftDancer = &mapNicknameToDancer[dancer2];
    pRightDancer = &mapNicknameToDancer[dancer1];
  }

  return {pLeftDancer, pRightDancer};
}
