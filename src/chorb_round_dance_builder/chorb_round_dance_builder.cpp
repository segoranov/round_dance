#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"

void ChorbRoundDanceBuilder::addDancer(const std::string& nickname) {
  dance.dancers.push_back(ChorbDancer{nickname});
  ChorbDancer& newDancer = dance.dancers.back();

  if (dance.dancers.size() == 1) {
    return;  // Nothing more to do
  }

  if (dance.dancers.size() == 2) {
    // firstDancer <---> newDancer
    ChorbDancer& firstDancer = dance.dancers.front();
    firstDancer.setRightDancer(&newDancer);
    firstDancer.grabRightDancer();

    newDancer.setLeftDancer(&firstDancer);
    newDancer.grabLeftDancer();

    return;
  }

  // clang-format off

  // Our situation now looks like this:
  // newDancer | <--> firstDancer <--> ... <--> previousLastDancer <--> newDancer <--> | firstDancer

  // clang-format on

  // The first dancer grabs the new dancer to the left
  ChorbDancer& firstDancer = dance.dancers.front();
  firstDancer.setLeftDancer(&newDancer);
  firstDancer.grabLeftDancer();

  // The new dancer grabs the first dancer to the right
  newDancer.setRightDancer(&firstDancer);
  newDancer.grabRightDancer();

  // The previous last dancer grabs the new dancer to the right
  ChorbDancer& previousLastDancer = *--(--dance.dancers.end());
  previousLastDancer.setRightDancer(&newDancer);
  previousLastDancer.grabRightDancer();

  // The new dancer grabs the previous last dancer to the left
  newDancer.setLeftDancer(&previousLastDancer);
  newDancer.grabLeftDancer();
}

ChorbRoundDance ChorbRoundDanceBuilder::getRoundDance() const { return dance; }