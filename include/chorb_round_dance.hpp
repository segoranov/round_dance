#ifndef CHORB_ROUND_DANCE_HPP_22062020
#define CHORB_ROUND_DANCE_HPP_22062020

#include <list>
#include <optional>
#include <unordered_map>

class ChorbDancer;

// The direction in which a dancer grabs/releases another dancer.
// For example a dancer can grab the dancer to the left, or to the right, or
// both.
// TODO DV format/improve doc.
enum class Direction { LEFT, RIGHT, BOTH };

class ChorbRoundDance {
  // TODO Is this 'friend' ok? I want the builder
  // to have access to the list of dancers.
  friend class ChorbRoundDanceBuilder;

 private:
  std::list<ChorbDancer> dancers;
  std::unordered_map<std::string, ChorbDancer*> mapNicknameToDancer;

 public:
  // TODO DV add doc
  bool addDancer(const std::string& newDancer, const std::string& leftDancer,
                 const std::string& rightDancer);

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

  const std::list<ChorbDancer>& getDancers() const;
};

#endif
