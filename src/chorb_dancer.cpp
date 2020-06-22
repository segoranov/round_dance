#include "chorb_dancer.hpp"

AdjacentDancersInfo::AdjacentDancersInfo(ChorbDancer* dancerToTheLeft,
                                         bool grabbedDancerToTheLeft,
                                         ChorbDancer* dancerToTheRight,
                                         bool grabbedDancerToTheRight)
    : dancerToTheLeft{dancerToTheLeft},
      grabbedDancerToTheLeft{grabbedDancerToTheLeft},
      dancerToTheRight{dancerToTheRight},
      grabbedDancerToTheRight{grabbedDancerToTheRight} {}

ChorbDancer::ChorbDancer(const std::string& nickName,
                         const AdjacentDancersInfo& adjacentDancersInfo)
    : nickName{nickName}, adjacentDancersInfo{adjacentDancersInfo} {}

bool ChorbDancer::hasGrabbedLeftDancer() const noexcept {
  return adjacentDancersInfo.grabbedDancerToTheLeft;
}

void ChorbDancer::grabLeftDancer() {
  adjacentDancersInfo.grabbedDancerToTheLeft = true;
}

void ChorbDancer::releaseLeftDancer() {
  adjacentDancersInfo.grabbedDancerToTheLeft = false;
}

bool ChorbDancer::hasGrabbedRightDancer() const noexcept {
  return adjacentDancersInfo.grabbedDancerToTheRight;
}

void ChorbDancer::grabRightDancer() {
  adjacentDancersInfo.grabbedDancerToTheRight = true;
}

void ChorbDancer::releaseRightDancer() {
  adjacentDancersInfo.grabbedDancerToTheRight = false;
}
