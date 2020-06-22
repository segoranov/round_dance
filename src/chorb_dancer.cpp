#include "chorb_dancer.hpp"

ChorbDancer::ChorbDancer(const std::string& nickname) : nickname{nickname} {}

bool ChorbDancer::hasGrabbedDancerToTheLeft() const noexcept {
  return grabbedDancerToTheLeft;
}

void ChorbDancer::grabLeftDancer() { grabbedDancerToTheLeft = true; }

void ChorbDancer::releaseLeftDancer() { grabbedDancerToTheLeft = false; }

void ChorbDancer::setLeftDancer(ChorbDancer* dancer) {
  dancerToTheLeft = dancer;
}

const ChorbDancer* ChorbDancer::getDancerToTheLeft() const {
  return dancerToTheLeft;
}

bool ChorbDancer::hasGrabbedDancerToTheRight() const noexcept {
  return grabbedDancerToTheRight;
}

void ChorbDancer::grabRightDancer() { grabbedDancerToTheRight = true; }

void ChorbDancer::releaseRightDancer() { grabbedDancerToTheRight = false; }

void ChorbDancer::setRightDancer(ChorbDancer* dancer) {
  dancerToTheRight = dancer;
}

const ChorbDancer* ChorbDancer::getDancerToTheRight() const {
  return dancerToTheRight;
}

std::string ChorbDancer::getNickname() const noexcept { return nickname; }
