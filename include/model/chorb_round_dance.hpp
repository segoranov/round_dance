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

//!  A ChorbRoundDance class. 
class ChorbRoundDance {
  friend class StandartChorbRoundDanceBuilder;

 private:
  std::unordered_map<std::string, ChorbDancer> mapNicknameToDancer; /*!< Gives a nickname to the dancer. */

  //!  A private pointer variable.
  /*!
       Pointer variable points to the first dancer in the chorb round dance.
  */
  ChorbDancer* firstDancer; 

  //!  A private pointer variable.
  /*!
       Pointer variable points to the last dancer in the chorb round dance.
  */
  ChorbDancer* lastDancer;

 public:
 
  /**
   * @brief Public declaration of boolean function that receives as an input the nicknames of the new, left and right dancers of type string.
   *  The function returns true if the addition of a dancer was successful. Otherwise it returns false.
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
   * @brief Public declaration of boolean function that receives as an input the nickname of the dancer of type string
   *  and returns true if the removal of a dancer was successful. Otherwise it returns false.
   * 
   * @param dancer 
   * @return true 
   * @return false 
   */
  bool removeDancer(const std::string& dancer);

  /**
   * @brief Public declaration of boolean function that receives as an input the nicknames of the dancer1 and dancer2 of type string.
   *  The function returns true if the swap of a dancer was successful. Otherwise it returns false.
   * 
   * @param dancer1 
   * @param dancer2 
   * @return true 
   * @return false 
   */
  bool swap(const std::string& dancer1, const std::string& dancer2);

  /**
   * @brief Public declaration of the function that receives as an input the nickname of the dancer of type string
   *  and grabbing direction of type enum class Direction. The function grabs the hand of his left or right neighbor or both.
   * 
   * @param dancer 
   * @param grabbingDirection 
   */
  void grab(const std::string& dancer, Direction grabbingDirection);

  /**
   * @brief Public declaration of the function that receives as an input the nickname of the dancer of type string 
   * and release direction of type enum class Direction. The function releases the hand of his left or right neighbor or both.
   * 
   * @param dancer 
   * @param releaseDirection 
   */
  void release(const std::string& dancer, Direction releaseDirection);

  /**
   * @brief Returns the dancer if he exists in the dance.
   *  Otherwise empty optional
   * 
   * @param dancer 
   * @return std::optional<ChorbDancer> 
   */
  std::optional<ChorbDancer> getDancer(const std::string& dancer);

  /**
   * @brief Public declaration of the function that returns dancers in the order in which they are grabbed.
   * 
   * @return std::vector<ChorbDancer> 
   */
  std::vector<ChorbDancer> getDancers() const;

 private:
  /**
   * @brief Private declaration of boolean function that receives as an input the nicknames of the dancer1 and dancer2 of type string.
   *  The function returns true if the two dancers are neighbors the function. Otherwise returns false. The function does not throw exception.
   * 
   * @param dancer1 
   * @param dancer2 
   * @return true 
   * @return false 
   */
  bool areNeighbours(const std::string& dancer1,
                     const std::string& dancer2) noexcept;

  /**
   * @brief Private declaration of function that that receives as an input nickname of the dancer of type string and
   *  checks whether the dancer exists and if not, throws NonExistingDancer exception.
   * 
   * @param nickname 
   */
  void checkDancerExists(const std::string& nickname);
};

#endif
