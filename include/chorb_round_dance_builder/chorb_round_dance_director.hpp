#ifndef CHORB_ROUND_DANCE_DIRECTOR_23062020
#define CHORB_ROUND_DANCE_DIRECTOR_23062020

#include <string>
#include <vector>

#include "chorb_round_dance_builder.hpp"

//!  A ChorbRoundDanceDirector class. 
class ChorbRoundDanceDirector {
 private:
  ChorbRoundDanceBuilder* builder; 

 public:
 /**
  * @brief Public declaration of the function that resives as input pointer to chorb round dance builder and sets the builder object.
  * 
  * @param theBuilder 
  */
  void setBuilder(ChorbRoundDanceBuilder* theBuilder);

  
  /**
   * @brief Public declaration of the function that receives as input vector of nicknames of type string 
   * and builds a chorb round dance out of them.
   * 
   * @param nicknames 
   * @return ChorbRoundDance* 
   */
  ChorbRoundDance* createChorbRoundDance(const std::vector<std::string>& nicknames);
};

#endif
