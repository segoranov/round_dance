#ifndef CHORB_ROUND_DANCE_VIEW_HPP_26062020
#define CHORB_ROUND_DANCE_VIEW_HPP_26062020

#include <memory>
#include <string>

class ChorbRoundDance;
class ChorbDancer;

// TODO Mock view and unit tests for the view?

//!  A ChorbDanceView class.
/*!
    The interface for the View
*/
class ChorbRoundDanceView {
 public:
  using UPtr = std::unique_ptr<ChorbRoundDanceView>;  // for convenience

  /**
   * @brief A pure virtual function that receives as an input dance of type ChorbRoundDance and shows the round dance.
   * 
   * @param dance 
   */
  virtual void showRoundDance(const ChorbRoundDance& dance) = 0;

  /**
   * @brief A pure virtual function that receives as an input dance of type ChorbDancer and shows the information about the dancer.
   * 
   * @param dancer 
   */
  virtual void showInfoAboutDancer(const ChorbDancer& dancer) = 0;

  /**
   * @brief A pure virtual function that receives as an input error of type string and shows the error.
   * 
   * @param error 
   */
  virtual void showError(const std::string& error) = 0;

  /**
   * @brief A pure virtual function that receives as an input message of type string and shows the message.
   * 
   * @param message 
   */
  virtual void showMessage(const std::string& message) = 0;

  /**
   * @brief A pure virtual function that receives as an input message of type string and shows the prompt.
   * 
   * @param prompt 
   */
  virtual void showPrompt(const std::string& prompt) = 0;

  /**
   * @brief  A pure virtual function that receives as an input message of type string and shows available commands.
   * 
   */
  virtual void showAvailableCommands() = 0;
};

#endif
