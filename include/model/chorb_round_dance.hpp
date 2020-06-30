#ifndef CHORB_ROUND_DANCE_HPP_22062020
#define CHORB_ROUND_DANCE_HPP_22062020

#include <optional>
#include <unordered_map>
#include <vector>

#include "model/chorb_dancer.hpp"

/**
 * @brief The direction in which a dancer grabs/releases another dancer.
 * For example a dancer can grab the dancer to the left, the dancer to the right, or both. 
 */
enum class Direction { LEFT, RIGHT, BOTH };

class ChorbRoundDance {
  friend class StandartChorbRoundDanceBuilder;

 private:
  std::unordered_map<std::string, ChorbDancer> mapNicknameToDancer; /*!< Gives a nickname to the dancer. */

  ChorbDancer* firstDancer; /*!< First dancer in the chorb round dance */
  ChorbDancer* lastDancer; /*!< Last dancer in the chorb round dance */

 public:
  /**
   * @brief Add dancer to chorb round dance.
   * 
   * @param newDancerNickname 
   * @param leftDancerNickname 
   * @param rightDancerNickname 
   * @return true 
   * @return false 
   */
  bool addDancer(const std::string& newDancerNickname,
                 const std::string& leftDancerNickname,
                 const std::string& rightDancerNickname);

  /**
   * @brief Remove dancer from chorb round dance.
   * 
   * @param dancer 
   * @return true 
   * @return false 
   */
  bool removeDancer(const std::string& dancer);

  /**
   * @brief Swap dancer1 with dancer2.
   * 
   * @param dancer1 
   * @param dancer2 
   * @return true 
   * @return false 
   */
  bool swap(const std::string& dancer1, const std::string& dancer2);

  /**
   * @brief The dancer grabs the hand of his left or right neighbor or both.
   * 
   * @param dancer 
   * @param grabbingDirection 
   */
  void grab(const std::string& dancer, Direction grabbingDirection);

  /**
   * @brief The dancer releases the hand of his left or right neighbor or both.
   * 
   * @param dancer 
   * @param releaseDirection 
   */
  void release(const std::string& dancer, Direction releaseDirection);

  /**
   * @brief Returns the dancer if he exists in the dance; otherwise empty optional
   * 
   * @param dancer 
   * @return std::optional<ChorbDancer> 
   */
  std::optional<ChorbDancer> getDancer(const std::string& dancer);

  /**
   * @brief Returns them in the order in which they are grabbed.
   * 
   * @return std::vector<ChorbDancer> 
   */
  std::vector<ChorbDancer> getDancers() const;

 private:
  /**
   * @brief Checks if the two dancers are neighbors.
   * 
   * @param dancer1 
   * @param dancer2 
   * @return true 
   * @return false 
   */
  bool areNeighbours(const std::string& dancer1,
                     const std::string& dancer2) noexcept;

  /**
   * @brief Checks whether the dancer exists and if not, throws NonExistingDancer exception.
   * 
   * @param nickname 
   */
  void checkDancerExists(const std::string& nickname);
};

#endif
