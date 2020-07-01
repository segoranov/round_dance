#ifndef CHORB_ROUND_DANCE_APP_25062020
#define CHORB_ROUND_DANCE_APP_25062020

#include <iostream>
#include <string>
#include <vector>

#include "presenter/chorb_round_dance_presenter.hpp"

class ChorbRoundDanceApp {
 private:
  //! A private presenter variable of type ChorbRoundDancePresenter.
  ChorbRoundDancePresenter presenter;

  //! A private declaration of the function generateDance(const std::string& file).
  /*! The function returns pointer to ChorbRoundDance */
  ChorbRoundDance* generateDance(const std::string& file);

  //! A private enum class.
  /*! Consists of all command operations */
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
  //! A private declaration of the function strToCommand(const std::string& command).
  /*! A function return type is Command, which is enum class.*/
  Command strToCommand(const std::string& command);

  //! A private declaration of the function strToDirection(const std::string& direction).
  /*! A function return type is Direction, which is enum class. */
  Direction strToDirection(const std::string& direction);

  void onAddCommand(const std::vector<std::string>& tokens); /*!< Private declaration of the function onAddCommand(const std::vector<std::string>& tokens). */
  void onInfoCommand(const std::vector<std::string>& tokens); /*!< Private declaration of the function onInfoCommand(const std::vector<std::string>& tokens). */
  void onRemoveCommand(const std::vector<std::string>& tokens); /*!< Private declaration of the function onRemoveCommand(const std::vector<std::string>& tokens). */
  void onReleaseCommand(const std::vector<std::string>& tokens); /*!< Private declaration of the function onReleaseCommand(const std::vector<std::string>& tokens). */
  void onGrabCommand(const std::vector<std::string>& tokens); /*!< Private declaration of the function onGrabCommand(const std::vector<std::string>& tokens). */
  void onSwapCommand(const std::vector<std::string>& tokens); /*!< Private declaration of the function onSwapCommand(const std::vector<std::string>& tokens). */

 public:
  ChorbRoundDanceApp(const std::string& file); /*!< Public declaration of the parameterized constructor. */
  void run(); /*!< Public declaration of the run function. */
};

#endif
