#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"

void ChorbRoundDanceBuilder::addDancer(const std::string& nickname) {}

ChorbRoundDance* ChorbRoundDanceBuilder::getRoundDance() { return nullptr; }

StandartChorbRoundDanceBuilder::StandartChorbRoundDanceBuilder() {
  dancePtr = new ChorbRoundDance;
}

void StandartChorbRoundDanceBuilder::addDancer(const std::string& nickname) {
  dancePtr->dancers.push_back(ChorbDancer{nickname});
  ChorbDancer& newDancer = dancePtr->dancers.back();

  if (dancePtr->dancers.size() == 1) {
    return;  // Nothing more to do
  }

  if (dancePtr->dancers.size() == 2) {
    // firstDancer <---> newDancer
    ChorbDancer& firstDancer = dancePtr->dancers.front();
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
  ChorbDancer& firstDancer = dancePtr->dancers.front();
  firstDancer.setLeftDancer(&newDancer);
  firstDancer.grabLeftDancer();

  // The new dancer grabs the first dancer to the right
  newDancer.setRightDancer(&firstDancer);
  newDancer.grabRightDancer();

  // The previous last dancer grabs the new dancer to the right
  ChorbDancer& previousLastDancer = *--(--dancePtr->dancers.end());
  previousLastDancer.setRightDancer(&newDancer);
  previousLastDancer.grabRightDancer();

  // The new dancer grabs the previous last dancer to the left
  newDancer.setLeftDancer(&previousLastDancer);
  newDancer.grabLeftDancer();
}

ChorbRoundDance* StandartChorbRoundDanceBuilder::getRoundDance() {
  return dancePtr;  // TODO should we give up ownership here?
}
