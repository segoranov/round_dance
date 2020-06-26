#ifndef CHORB_ROUND_DANCE_APP_25062020
#define CHORB_ROUND_DANCE_APP_25062020

#include <iostream>
#include <string>
#include <vector>

#include "chorb_round_dance.hpp"
#include "view/chorb_round_dance_view.hpp"

class ChorbRoundDanceApp {
 private:
  ChorbRoundDance* dance{nullptr};
  ChorbRoundDanceView::UPtr view{nullptr};

 public:
  // TODO does the View belong in this class? What about Presenter?
  explicit ChorbRoundDanceApp(ChorbRoundDanceView::UPtr view);
  void generateDance(const std::string& file);
  void run();
};

#endif
