#ifndef CHORB_ROUND_DANCE_PRESENTER_HPP_26062020
#define CHORB_ROUND_DANCE_PRESENTER_HPP_26062020

#include <string>

#include "model/chorb_dancer.hpp"
#include "model/chorb_round_dance.hpp"
#include "view/chorb_round_dance_view.hpp"

// TODO should we have an interface for the presenter?

//!  A ChorbDancePresenter class.
/*!
    Used as a mediator between the model and the view (MVP pattern).
*/
class ChorbRoundDancePresenter { 
 private:
  ChorbRoundDance* dance{nullptr}; /*!< Private pointer variable to the chorb round dance. */
  ChorbRoundDanceView::UPtr view{nullptr}; /*!< Private unique pointer variable to the chorb round dance view. */

 public:
  ChorbRoundDancePresenter() = default; /*!< Public declaration of the default constructor. */
  ChorbRoundDancePresenter(ChorbRoundDance* dance,
                           ChorbRoundDanceView::UPtr view);  /*!< Public declaration of the parameterized constructor. */

  /**
   * @brief Public declaration of function that receives as an input the nicknames of the new, left and right dancers of type string.
   *  Interacts with the model and the view when a new dancer is to be added.
   * 
   * @param newDancer 
   * @param leftDancer 
   * @param rightDancer 
   */
  void onAddDancer(const std::string& newDancer, const std::string& leftDancer,
                   const std::string& rightDancer);
  /**
   * @brief Public declaration of function that receives as an input the dancer of type string.
   *  Interacts with the model and the view when a new dancer is to be removed.
   * 
   * @param dancer 
   */
  void onRemoveDancer(const std::string& dancer);
  /**
   * @brief  Public declaration of the function that receives as an input the nickname of the dancer of type string
   *  and grabbing direction of type enum class Direction. Interacts with the model and the view when a dancer is to be grabbed.
   * 
   * @param who 
   * @param grabbingDirection 
   */
  void onGrab(const std::string& who, Direction grabbingDirection);
  /**
   * @brief  Public declaration of the function that receives as an input the nickname of the dancer of type string
   *  and grabbing direction of type enum class Direction. The Interacts with the model and the view when a dancer is to be released.
   * 
   * @param who 
   * @param releaseDirection 
   */
  void onRelease(const std::string& who, Direction releaseDirection);
  /**
   * @brief Public declaration of function that receives as an input the dancer1 and dancer2 of type string.
   *  Interacts with the model and the view when a new dancer is to be swapped. 
   * 
   * @param dancer1 
   * @param dancer2 
   */
  void onSwap(const std::string& dancer1, const std::string& dancer2);

  /**
   * @brief Interacts with the model and the view when exit from the program.
   * 
   */
  void onExit();

  /**
   * @brief Public declaration of function that receives as an input the dancer of type string 
   *  and interacts with the model and the view when shows the information about the dancer.
   * 
   * @param dancer 
   */
  void onShowDancerInfo(const std::string& dancer);

  /**
   * @brief Public declaration of function that interacts with the model and the view when shows all information about dancers.
   * 
   */
  void onShowAllDancersInfo();

  /**
   * @brief Public declaration of function that interacts with the model and the view when shows round dance.
   * 
   */
  void onShowRoundDance();

  /**
   * @brief Public declaration of function that receives as an input the message of type string 
   *  and interacts with the model and the view when shows the message.
   * 
   * @param message 
   */
  void showMessage(const std::string& message);

  /**
   * @brief Public declaration of function that receives as an input the prompt of type string 
   *  and interacts with the model and the view when shows the prompt.
   * 
   * @param prompt 
   */
  void showPrompt(const std::string& prompt);

  /**
   * @brief Public declaration of function that receives as an input error of type string 
   *  and interacts with the model and the view when shows user error message.
   * 
   * @param error 
   */
  void onUserError(const std::string& error);

  /**
   * @brief Public declaration of function that interacts with the model and the view when shows available commands.
   * 
   */
  void showAvailableCommands();
};

#endif
