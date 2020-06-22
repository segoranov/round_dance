#ifndef CHORB_ROUND_DANCE_BUILDER_HPP_220602020
#define CHORB_ROUND_DANCE_BUILDER_HPP_220602020

#include <memory>
#include <string>

#include "chorb_dancer.hpp"
#include "chorb_round_dance.hpp"

// TODO SG/DV
// SG: I do not like how RoundDanceBuilder is interface, but
// there is no interface for Dancer or Dance and things feel
// kind of messy, for example the interface RoundDanceBuilder
// returning ChorbRoundDance instead of ptr to interface Dance,
// as is the example in Gang of four book.
class RoundDanceBuilder {
 public:
  using UPtr = std::unique_ptr<RoundDanceBuilder>;  // for convenience
  virtual void addDancer(const std::string& nickname) = 0;
  virtual ChorbRoundDance getRoundDance() const = 0;
};

class ChorbRoundDanceBuilder : public RoundDanceBuilder {
 private:
  ChorbRoundDance dance;

 public:
  virtual void addDancer(const std::string& nickname) override;
  virtual ChorbRoundDance getRoundDance() const override;
};

#endif
