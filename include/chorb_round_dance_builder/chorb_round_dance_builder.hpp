#ifndef CHORB_ROUND_DANCE_BUILDER_HPP_220602020
#define CHORB_ROUND_DANCE_BUILDER_HPP_220602020

#include <string>

#include "model/chorb_dancer.hpp"
#include "model/chorb_round_dance.hpp"

class ChorbRoundDanceBuilder {
 public:
  virtual void addDancer(const std::string& nickname);
  virtual ChorbRoundDance* getRoundDance();
};

class StandartChorbRoundDanceBuilder : public ChorbRoundDanceBuilder {
 private:
  ChorbRoundDance* dancePtr;

  // Below functions help in specific cases when adding a new dancer
  void addDancerWhenSizeIs1(ChorbDancer* newDancer);
  void addDancerWhenSizeIs2(ChorbDancer* newDancer);
  void addDancerWhenSizeMoreThan2(ChorbDancer* newDancer);

 public:
  StandartChorbRoundDanceBuilder();
  virtual void addDancer(const std::string& nickname) override;
  virtual ChorbRoundDance* getRoundDance() override;
};

#endif
