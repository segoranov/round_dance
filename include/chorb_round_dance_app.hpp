#ifndef CHORB_ROUND_DANCE_APP_25062020
#define CHORB_ROUND_DANCE_APP_25062020

#include <iostream>
#include <string>
#include <vector>

#include "presenter/chorb_round_dance_presenter.hpp"

// TODO Add ChorbRoundDanceApp to uml diagram
class ChorbRoundDanceApp {
 private:
  ChorbRoundDancePresenter presenter;

  ChorbRoundDance* generateDance(const std::string& file);

  enum class COMMAND {
    ADD,
    REMOVE,
    SWAP,
    GRAB,
    RELEASE,
    EXIT,
    INFO,
    PRINT,
    UNDEFINED,
  };

  COMMAND strToCommand(const std::string& command);

  void onAddCommand(const std::vector<std::string>& tokens);

 public:
  ChorbRoundDanceApp(const std::string& file);
  void run();
};

#endif
