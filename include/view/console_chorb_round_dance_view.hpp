#ifndef CONSOLE_VIEW_HPP_260602020
#define CONSOLE_VIEW_HPP_260602020

#include "view/chorb_round_dance_view.hpp"

// Concrete implementation for the console
class ConsoleChorbRoundDanceView : public ChorbRoundDanceView {
 public:
  virtual void showRoundDance(const ChorbRoundDance& dance) override;
  virtual void showInfoAboutDancer(const ChorbDancer& dancer) override;
  virtual void showError(const std::string& error) override;
  virtual void showMessage(const std::string& message) override;
  virtual void showPrompt(const std::string& prompt) override;
  virtual void showAvailableCommands() override;
};

#endif
