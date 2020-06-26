#include "view/console_chorb_round_dance_view.hpp"

#include <iostream>

void ConsoleChorbRoundDanceView::showRoundDance(const ChorbRoundDance& dance) {
  // TODO
}

void ConsoleChorbRoundDanceView::showInfoAboutDancer(
    const ChorbDancer& dancer) {
  // TODO
}

void ConsoleChorbRoundDanceView::showError(const std::string& error) {
  std::cerr << "ERROR: " << error << std::endl;
}

void ConsoleChorbRoundDanceView::showMessage(const std::string& message) {
  std::cout << "MESSAGE: " << message << std::endl;
}

void ConsoleChorbRoundDanceView::showPrompt(const std::string& prompt) {
  std::cout << '\n' << prompt << "> ";
}
