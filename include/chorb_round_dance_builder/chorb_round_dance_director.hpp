#ifndef CHORB_ROUND_DANCE_DIRECTOR_23062020
#define CHORB_ROUND_DANCE_DIRECTOR_23062020

#include <string>
#include <vector>

#include "chorb_round_dance_builder.hpp"

class ChorbRoundDanceDirector {
 private:
  ChorbRoundDanceBuilder* builder;

 public:
 /**
  * @brief Set the Builder object
  * 
  * @param theBuilder 
  */
  void setBuilder(ChorbRoundDanceBuilder* theBuilder);

  
  /**
   * @brief Receives as input vector of nicknames and builds a chorb round dance out of them
   * 
   * @param nicknames 
   * @return ChorbRoundDance* 
   */
  ChorbRoundDance* createChorbRoundDance(
      const std::vector<std::string>& nicknames);
};

#endif
