#ifndef CHORB_ROUND_DANCE_APP_25062020
#define CHORB_ROUND_DANCE_APP_25062020

#include <iostream>
#include <string>
#include <vector>

#include "chorb_round_dance.hpp"

class ChorbRoundDanceApp {
 private:
  ChorbRoundDance* dance{nullptr};

 public:
  void generateDance(const std::string& file);
  void run();
};

#endif
