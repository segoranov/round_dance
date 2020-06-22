#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"

void ChorbRoundDanceBuilder::addDancer(const std::string& nickname) {
  ChorbDancer& previousLastDancer = dance.dancers.back();

  dance.dancers.push_back(ChorbDancer{nickname});
  ChorbDancer& newDancer = dance.dancers.back();

  if (dance.dancers.size() == 1) {
    return;  // nothing more to do
  }

  // The first dancer in the list grabs the last added dancer
  // The new dancer will be to the left of the first dancer

  dance.dancers.front().setLeftDancer(&newDancer);
  dance.dancers.front().grabLeftDancer();

  // Grab the first dancer
  newDancer.setRightDancer(&dance.dancers.front());
  newDancer.grabRightDancer();

  if (dance.dancers.size() > 2) {
    // Grab the previous last dancer
    newDancer.setLeftDancer(&previousLastDancer);
    newDancer.grabLeftDancer();
  }
}

ChorbRoundDance ChorbRoundDanceBuilder::getRoundDance() const { return dance; }