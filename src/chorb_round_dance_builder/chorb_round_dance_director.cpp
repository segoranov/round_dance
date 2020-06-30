#include "chorb_round_dance_builder/chorb_round_dance_director.hpp"

void ChorbRoundDanceDirector::setBuilder(ChorbRoundDanceBuilder* theBuilder) {
  builder = theBuilder;
}

ChorbRoundDance* ChorbRoundDanceDirector::createChorbRoundDance(
    const std::vector<std::string>& nicknames) {
  for (const auto& nickname : nicknames) {
    builder->addDancer(nickname);
  }

  return builder->getRoundDance();
}
