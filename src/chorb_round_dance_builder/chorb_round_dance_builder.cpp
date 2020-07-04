#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"

#include "model/round_dance_exceptions.hpp"

void ChorbRoundDanceBuilder::addDancer(const std::string& nickname) {}

ChorbRoundDance* ChorbRoundDanceBuilder::getRoundDance() { return nullptr; }

StandartChorbRoundDanceBuilder::StandartChorbRoundDanceBuilder() {
  dancePtr = new ChorbRoundDance;
}

void StandartChorbRoundDanceBuilder::addDancer(const std::string& nickname) {
  if (nickname.size() > 30) {
    throw TooLongNicknameException("Builder: Couldn't add dancer '" + nickname +
                                   "'. Contains more than 30 symbols.");
  }

  dancePtr->mapNicknameToDancer.insert({nickname, ChorbDancer{nickname}});
  ChorbDancer* newDancer = &(dancePtr->mapNicknameToDancer[nickname]);

  if (dancePtr->mapNicknameToDancer.size() == 1) {
    addDancerWhenSizeIs1(newDancer);
  } else if (dancePtr->mapNicknameToDancer.size() == 2) {
    addDancerWhenSizeIs2(newDancer);
  } else {
    addDancerWhenSizeMoreThan2(newDancer);
  }
}

void StandartChorbRoundDanceBuilder::addDancerWhenSizeIs1(
    ChorbDancer* newDancer) {
  dancePtr->firstDancer = dancePtr->lastDancer = newDancer;
}

void StandartChorbRoundDanceBuilder::addDancerWhenSizeIs2(
    ChorbDancer* newDancer) {
  // firstDancer <---> newDancer
  dancePtr->firstDancer->setRightDancer(newDancer);
  dancePtr->firstDancer->grabRightDancer();

  newDancer->setLeftDancer(dancePtr->firstDancer);
  newDancer->grabLeftDancer();

  dancePtr->lastDancer = newDancer;
}

void StandartChorbRoundDanceBuilder::addDancerWhenSizeMoreThan2(
    ChorbDancer* newDancer) {
  // clang-format off

  // Our situation looks like this:
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
