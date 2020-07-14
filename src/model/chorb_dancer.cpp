#include "model/chorb_dancer.hpp"

ChorbDancer::ChorbDancer(const std::string& nickname) : nickname{nickname} {}

bool ChorbDancer::hasGrabbedLeftDancer() const noexcept {
  return grabbedLeftDancer;
}

void ChorbDancer::grabLeftDancer() { grabbedLeftDancer = true; }

void ChorbDancer::releaseLeftDancer() { grabbedLeftDancer = false; }

void ChorbDancer::setLeftDancer(ChorbDancer* dancer) { pLeftDancer = dancer; }

const ChorbDancer* ChorbDancer::getLeftDancer() const { return pLeftDancer; }

bool ChorbDancer::hasGrabbedRightDancer() const noexcept {
  return grabbedRightDancer;
}

void ChorbDancer::grabRightDancer() { grabbedRightDancer = true; }

void ChorbDancer::releaseRightDancer() { grabbedRightDancer = false; }

void ChorbDancer::setRightDancer(ChorbDancer* dancer) { pRightDancer = dancer; }

const ChorbDancer* ChorbDancer::getRightDancer() const { return pRightDancer; }

std::string ChorbDancer::getNickname() const noexcept { return nickname; }
