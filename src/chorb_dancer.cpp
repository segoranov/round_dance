#include "chorb_dancer.hpp"

ChorbDancer::ChorbDancer(const std::string& nickname) : nickname{nickname} {}

bool ChorbDancer::hasGrabbedLeftDancer() const noexcept {
  return grabbedLeftDancer;
}

void ChorbDancer::grabLeftDancer() { grabbedLeftDancer = true; }

void ChorbDancer::releaseLeftDancer() { grabbedLeftDancer = false; }

void ChorbDancer::setLeftDancer(ChorbDancer* dancer) { leftDancer = dancer; }

const ChorbDancer* ChorbDancer::getLeftDancer() const { return leftDancer; }

bool ChorbDancer::hasGrabbedRightDancer() const noexcept {
  return grabbedRightDancer;
}

void ChorbDancer::grabRightDancer() { grabbedRightDancer = true; }

void ChorbDancer::releaseRightDancer() { grabbedRightDancer = false; }

void ChorbDancer::setRightDancer(ChorbDancer* dancer) { rightDancer = dancer; }

const ChorbDancer* ChorbDancer::getRightDancer() const { return rightDancer; }

std::string ChorbDancer::getNickname() const noexcept { return nickname; }
