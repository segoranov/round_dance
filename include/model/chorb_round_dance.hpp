#ifndef CHORB_ROUND_DANCE_HPP_22062020
#define CHORB_ROUND_DANCE_HPP_22062020

#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "model/chorb_dancer.hpp"

// The direction in which a dancer grabs/releases another dancer.
// For example a dancer can grab the dancer to the left, the dancer to the
// right, or both.
// TODO DV format/improve doc.
enum class Direction { LEFT, RIGHT, BOTH };

class ChorbRoundDance {
  friend class StandartChorbRoundDanceBuilder;

 private:
  std::unordered_map<std::string, ChorbDancer> mapNicknameToDancer;

  ChorbDancer* firstDancer;
  ChorbDancer* lastDancer;

 public:
  // TODO DV add doc
  bool addDancer(const std::string& newDancerNickname,
                 const std::string& leftDancerNickname,
                 const std::string& rightDancerNickname);

  // TODO DV add doc
  bool removeDancer(const std::string& dancer);

  // TODO DV add doc
  bool swap(const std::string& dancer1, const std::string& dancer2);

  // TODO DV add doc
  void grab(const std::string& dancer, Direction grabbingDirection);

  // TODO DV add doc
  void release(const std::string& dancer, Direction releaseDirection);

  /**
   * Returns the dancer if he exists in the dance; otherwise empty optional
   * TODO DV format/improve doc
   */
  std::optional<ChorbDancer> getDancer(const std::string& dancer);

  // Returns them in the order in which they are grabbed
  // TODO DV format doc
  std::vector<ChorbDancer> getDancers() const;

 private:
  bool areNeighbours(const std::string& dancer1,
                     const std::string& dancer2) noexcept;

  // TODO DV doc
  // Checks whether the dancer exists and if not, throws NonExistingDancer
  // exception
  void checkDancerExists(const std::string& nickname);

  // Given two neighbours, returns a pair of dancers
  // The first member of the pair is the left dancer, the second is the right
  // dancer
  std::pair<ChorbDancer*, ChorbDancer*> getLeftAndRightDancers(
      const std::string& dancer1, const std::string& dancer2);
};

#endif
