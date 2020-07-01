#ifndef CHORB_ROUND_DANCE_APP_25062020
#define CHORB_ROUND_DANCE_APP_25062020

#include <iostream>
#include <string>
#include <vector>

#include "presenter/chorb_round_dance_presenter.hpp"

//!  A ChorbRoundDanceApp class.
class ChorbRoundDanceApp {
 private:
  ChorbRoundDancePresenter presenter; /*!< A private presenter variable of type ChorbRoundDancePresenter. */

  /**
   * @brief A private declaration of the function that generates the dance.
   * 
   * @param file 
   * @return ChorbRoundDance* 
   */
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
  
  /**
   * @brief A private declaration of the function that converts string to command.
   * 
   * @param command 
   * @return Command 
   */
  Command strToCommand(const std::string& command);

  /**
   * @brief A private declaration of the function that converts string to direction.
   * 
   * @param direction 
   * @return Direction 
   */
  Direction strToDirection(const std::string& direction);

  /**
   * @brief Private declaration of the function that receives as an input vector of strings.
   * 
   * @param tokens 
   */
  void onAddCommand(const std::vector<std::string>& tokens); 

    /**
   * @brief Private declaration of the function that receives as an input vector of strings.
   * 
   * @param tokens 
   */
  void onInfoCommand(const std::vector<std::string>& tokens); 

  /**
   * @brief Private declaration of the function that receives as an input vector of strings.
   * 
   * @param tokens 
   */
  void onRemoveCommand(const std::vector<std::string>& tokens);

  /**
   * @brief Private declaration of the function that receives as an input vector of strings.
   * 
   * @param tokens 
   */
  void onReleaseCommand(const std::vector<std::string>& tokens); 

  /**
   * @brief Private declaration of the function that receives as an input vector of strings.
   * 
   * @param tokens 
   */
  void onGrabCommand(const std::vector<std::string>& tokens); 

  /**
   * @brief Private declaration of the function that receives as an input vector of strings.
   * 
   * @param tokens 
   */
  void onSwapCommand(const std::vector<std::string>& tokens); 

 public:
  /**
  * @brief Public declaration of the parameterized constructor. Construct a new Chorb Round Dance App object
  * 
  * @param file 
  */
  ChorbRoundDanceApp(const std::string& file); 

  /**
   * @brief Public declaration of the run function.
   * 
   */
  void run();
};

#endif
