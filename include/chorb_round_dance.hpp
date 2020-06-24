#ifndef CHORB_ROUND_DANCE_HPP_22062020
#define CHORB_ROUND_DANCE_HPP_22062020

#include <optional>
#include <unordered_map>
#include <vector>

#include "chorb_dancer.hpp"

// The direction in which a dancer grabs/releases another dancer.
// For example a dancer can grab the dancer to the left, or to the right, or
// both.
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
  // TODO SG/DV: We can throw exception here, for example
  // DancerNotExistingException, when the dancer does not exist in the dance
  void grab(const std::string& dancer, Direction grabbingDirection);

  // TODO DV add doc
  // TODO SG/DV: We can throw exception here, for example
  // DancerNotExistingException, when the dancer does not exist in the dance
  void release(const std::string& dancer, Direction releaseDirection);

  /**
   * Returns the dancer if he exists in the dance; otherwise empty optional
   * TODO DV format/improve doc
   */
  std::optional<ChorbDancer> getDancer(const std::string& dancer) const;

  // Returns them in the order in which they are grabbed
  // TODO DV format doc
  std::vector<ChorbDancer> getDancers() const;

 private:
  bool areNeighbours(const std::string& dancer1,
                     const std::string& dancer2) noexcept;

  // TODO DV doc
  // Checks whether the dancer exists and if not, throws exception
  void checkDancerExists(const std::string& nickname);
};

#endif
