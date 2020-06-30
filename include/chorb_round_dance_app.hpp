#ifndef CHORB_ROUND_DANCE_APP_25062020
#define CHORB_ROUND_DANCE_APP_25062020

#include <iostream>
#include <string>
#include <vector>

#include "presenter/chorb_round_dance_presenter.hpp"

class ChorbRoundDanceApp {
 private:
  ChorbRoundDancePresenter presenter;

  ChorbRoundDance* generateDance(const std::string& file);

  enum class Command {
    ADD,
    REMOVE,
    SWAP,
    GRAB,
    RELEASE,
    EXIT,
    INFO,
    PRINT,
    HELP,
  };

  Command strToCommand(const std::string& command);
  Direction strToDirection(const std::string& direction);

  void onAddCommand(const std::vector<std::string>& tokens);
  void onInfoCommand(const std::vector<std::string>& tokens);
  void onRemoveCommand(const std::vector<std::string>& tokens);
  void onReleaseCommand(const std::vector<std::string>& tokens);
  void onGrabCommand(const std::vector<std::string>& tokens);

 public:
  ChorbRoundDanceApp(const std::string& file);
  void run();
};

#endif
