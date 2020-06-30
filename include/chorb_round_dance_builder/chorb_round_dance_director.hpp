#ifndef CHORB_ROUND_DANCE_DIRECTOR_23062020
#define CHORB_ROUND_DANCE_DIRECTOR_23062020

#include <string>
#include <vector>

#include "chorb_round_dance_builder.hpp"

class ChorbRoundDanceDirector {
 private:
  ChorbRoundDanceBuilder* builder;

 public:
  void setBuilder(ChorbRoundDanceBuilder* theBuilder);

  // TODO DV doc
  // Receives as input vector of nicknames and builds a chorb round dance out of
  // them
  ChorbRoundDance* createChorbRoundDance(
      const std::vector<std::string>& nicknames);
};

#endif
