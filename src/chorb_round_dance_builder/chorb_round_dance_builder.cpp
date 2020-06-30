#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"

void ChorbRoundDanceBuilder::addDancer(const std::string& nickname) {}

ChorbRoundDance* ChorbRoundDanceBuilder::getRoundDance() { return nullptr; }

StandartChorbRoundDanceBuilder::StandartChorbRoundDanceBuilder() {
  dancePtr = new ChorbRoundDance;
}

void StandartChorbRoundDanceBuilder::addDancer(const std::string& nickname) {
  // TODO Check no more than 30 symbols nickname
  // TODO Implement and throw TooLongNicknameException if more than 30 symbols

  dancePtr->mapNicknameToDancer.insert({nickname, ChorbDancer{nickname}});
  ChorbDancer* newDancer = &(dancePtr->mapNicknameToDancer[nickname]);

  if (dancePtr->mapNicknameToDancer.size() == 1) {
    dancePtr->firstDancer = dancePtr->lastDancer = newDancer;
    return;
  }

  if (dancePtr->mapNicknameToDancer.size() == 2) {
    // firstDancer <---> newDancer
    dancePtr->firstDancer->setRightDancer(newDancer);
    dancePtr->firstDancer->grabRightDancer();

    newDancer->setLeftDancer(dancePtr->firstDancer);
    newDancer->grabLeftDancer();

    dancePtr->lastDancer = newDancer;

    return;
  }

  // clang-format off

  // Our situation now looks like this:
  // newDancer | <--> firstDancer <--> ... <--> previousLastDancer <--> newDancer <--> | firstDancer

  // clang-format on

  // The first dancer grabs the new dancer to the left
  dancePtr->firstDancer->setLeftDancer(newDancer);
  dancePtr->firstDancer->grabLeftDancer();

  // The new dancer grabs the first dancer to the right
  newDancer->setRightDancer(dancePtr->firstDancer);
  newDancer->grabRightDancer();

  // The previous last dancer grabs the new dancer to the right
  dancePtr->lastDancer->setRightDancer(newDancer);
  dancePtr->lastDancer->grabRightDancer();

  // The new dancer grabs the previous last dancer to the left
  newDancer->setLeftDancer(dancePtr->lastDancer);
  newDancer->grabLeftDancer();

  // The new dancer becomes the last dancer
  dancePtr->lastDancer = newDancer;
}

ChorbRoundDance* StandartChorbRoundDanceBuilder::getRoundDance() {
  return dancePtr;  // TODO should we give up ownership here?
}
