#ifndef CHORB_ROUND_DANCE_BUILDER_HPP_220602020
#define CHORB_ROUND_DANCE_BUILDER_HPP_220602020

#include <string>

#include "model/chorb_dancer.hpp"
#include "model/chorb_round_dance.hpp"

//!  A ChorbRoundDanceBuilder class. 
class ChorbRoundDanceBuilder {
 public:
 
 /**
  * @brief Public declaration of the virtual function that receives as an input nickname of type string and adds dancer by its nickname.
  *  
  * @param nickname 
  */
  virtual void addDancer(const std::string& nickname);
  
  /**
   * @brief Public declaration of the virtual function that gets pointer to the round dance.
   * 
   * @return ChorbRoundDance* 
   */
  virtual ChorbRoundDance* getRoundDance();  

//!  A StandartChorbRoundDanceBuilder class that inherits ChorbRoundDanceBuilder class
class StandartChorbRoundDanceBuilder : public ChorbRoundDanceBuilder {
 private:
  ChorbRoundDance* dancePtr; /*!< Private pointer variable to the chorb round dance. */

 public:
  StandartChorbRoundDanceBuilder(); /*!< Public declaration of the default constructor. */

  /**
   * @brief Public overriden declaration of the virtual function that receives as an input nickname 
   * of type string and adds dancer by its nickname.
   * 
   * @param nickname 
   */
  virtual void addDancer(const std::string& nickname) override;

  /**
   * @brief Public overriden declaration of the virtual function that gets pointer to the chorb round dance.
   * 
   * @return ChorbRoundDance* 
   */
  virtual ChorbRoundDance* getRoundDance() override;

#endif
