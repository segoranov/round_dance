#ifndef CONSOLE_VIEW_HPP_260602020
#define CONSOLE_VIEW_HPP_260602020

#include "view/chorb_round_dance_view.hpp"

// Concrete implementation for the console

//!  A ConsoleChorbRoundDanceView class that public inherits ChorbRoundDanceView class.
class ConsoleChorbRoundDanceView : public ChorbRoundDanceView {
 public:
 /**
  * @brief A virtual overriden function that shows the dance.
  * 
  * @param dance 
  */
  virtual void showRoundDance(const ChorbRoundDance& dance) override;

  /**
   * @brief A virtual overriden function that shows information about the dancer.
   * 
   * @param dancer 
   */
  virtual void showInfoAboutDancer(const ChorbDancer& dancer) override;

  /**
   * @brief  A virtual overriden function that shows the error message.
   * 
   * @param error 
   */
  virtual void showError(const std::string& error) override;

  /**
   * @brief A virtual overriden function that shows the message.
   * 
   * @param message 
   */
  virtual void showMessage(const std::string& message) override;

  /**
   * @brief A virtual overriden function that shows the prompt.
   * 
   * @param prompt 
   */
  virtual void showPrompt(const std::string& prompt) override;

  /**
   * @brief A virtual overriden function that shows the available command.
   * 
   */
  virtual void showAvailableCommands() override;
};

#endif
