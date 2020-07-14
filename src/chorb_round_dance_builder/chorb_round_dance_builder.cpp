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
  dancePtr->pFirstDancer = dancePtr->pLastDancer = newDancer;
}

void StandartChorbRoundDanceBuilder::addDancerWhenSizeIs2(
    ChorbDancer* newDancer) {
  // firstDancer <---> newDancer
  dancePtr->pFirstDancer->setRightDancer(newDancer);
  dancePtr->pFirstDancer->grabRightDancer();

  newDancer->setLeftDancer(dancePtr->pFirstDancer);
  newDancer->grabLeftDancer();

  dancePtr->pLastDancer = newDancer;
}

void StandartChorbRoundDanceBuilder::addDancerWhenSizeMoreThan2(
    ChorbDancer* newDancer) {
  // clang-format off

  // Our situation looks like this:
  // newDancer | <--> firstDancer <--> ... <--> previousLastDancer <--> newDancer <--> | firstDancer

  // clang-format on

  // The first dancer grabs the new dancer to the left
  dancePtr->pFirstDancer->setLeftDancer(newDancer);
  dancePtr->pFirstDancer->grabLeftDancer();

  // The new dancer grabs the first dancer to the right
  newDancer->setRightDancer(dancePtr->pFirstDancer);
  newDancer->grabRightDancer();

  // The previous last dancer grabs the new dancer to the right
  dancePtr->pLastDancer->setRightDancer(newDancer);
  dancePtr->pLastDancer->grabRightDancer();

  // The new dancer grabs the previous last dancer to the left
  newDancer->setLeftDancer(dancePtr->pLastDancer);
  newDancer->grabLeftDancer();

  // The new dancer becomes the last dancer
  dancePtr->pLastDancer = newDancer;
}

ChorbRoundDance* StandartChorbRoundDanceBuilder::getRoundDance() {
  return dancePtr;  // TODO should we give up ownership here?
}
