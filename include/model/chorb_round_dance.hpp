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
enum class Direction { LEFT, RIGHT, BOTH };

class ChorbRoundDance {
  friend class StandartChorbRoundDanceBuilder;

 private:
  std::unordered_map<std::string, ChorbDancer> mapNicknameToDancer;

  ChorbDancer* pFirstDancer;
  ChorbDancer* pLastDancer;

 public:
  /**
   * Adds new dancer between 'dancer1' and 'dancer2'
   *
   * @return true when adding is successful
   * @return false when 'dancer1' and 'dancer2' are not neighbors
   * @throw NonExistingDancerException if either 'dancer1' or 'dancer2' does not
   * exist
   */
  bool addDancer(const std::string& newDancer, const std::string& dancer1,
                 const std::string& dancer2);

  /**
   * Removes a dancer
   *
   * @return true on successful remove, i.e. when he is released by his
   * neighbors and he has released both of them
   * @return false otherwise
   * @throw NonExistingDancerException if 'dancer' does not exist
   */
  bool removeDancer(const std::string& dancer);

  /**
   * Swaps two dancers
   *
   * @return true on successful swap
   * @return false if 'dancer1' and 'dancer2' are not neighbors
   * @throw NonExistingDancerException if either 'dancer1' or 'dancer2' does not
   * exist
   */
  bool swap(const std::string& dancer1, const std::string& dancer2);

  /**
   * Makes a dancer grab to his left, right or both
   *
   * @throw NonExistingDancerException if 'dancer' does not exist
   */
  void grab(const std::string& dancer, Direction grabbingDirection);

  /**
   * Makes a dancer release to his left, right or both
   *
   * @throw NonExistingDancerException if 'dancer' does not exist
   */
  void release(const std::string& dancer, Direction releaseDirection);

  /**
   * Returns the dancer if he exists in the dance; otherwise empty optional
   */
  std::optional<ChorbDancer> getDancer(const std::string& dancer);

  /**
   * Returns them in the order in which they are grabbed
   */
  std::vector<ChorbDancer> getDancers() const;

 private:
  bool areNeighbours(const std::string& dancer1,
                     const std::string& dancer2) noexcept;

  /**
   * Checks whether the dancer exists
   *
   * @throw NonExistingDancerException if he doesn't
   */
  void checkDancerExists(const std::string& nickname);

  /**
   * Given two neighbours, returns a pair of dancers
   * The first member of the pair is the left dancer, the second is the right
   * dancer
   */
  std::pair<ChorbDancer*, ChorbDancer*> getLeftAndRightDancers(
      const std::string& dancer1, const std::string& dancer2);
};

#endif
