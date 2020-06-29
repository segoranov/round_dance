#ifndef CHORB_ROUND_DANCE_VIEW_HPP_26062020
#define CHORB_ROUND_DANCE_VIEW_HPP_26062020

#include <memory>
#include <string>

class ChorbRoundDance;
class ChorbDancer;

// TODO Mock view and unit tests for the view?
// The interface for the View
class ChorbRoundDanceView {
 public:
  using UPtr = std::unique_ptr<ChorbRoundDanceView>;  // for convenience
  virtual void showRoundDance(const ChorbRoundDance& dance) = 0;
  virtual void showInfoAboutDancer(const ChorbDancer& dancer) = 0;
  virtual void showError(const std::string& error) = 0;
  virtual void showMessage(const std::string& message) = 0;
  virtual void showPrompt(const std::string& prompt) = 0;
  virtual void showAvailableCommands() = 0;
};

#endif
