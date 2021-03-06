#include "view/console_chorb_round_dance_view.hpp"

#include <iostream>

#include "model/chorb_dancer.hpp"
#include "model/chorb_round_dance.hpp"

void ConsoleChorbRoundDanceView::showRoundDance(const ChorbRoundDance& dance) {
  std::cout << "THE CURRENT CHORB ROUND DANCE:\n";
  for (const auto& dancer : dance.getDancers()) {
    std::cout << dancer.getNickname() << '\n';
  }
  std::cout << '\n';
}

void ConsoleChorbRoundDanceView::showInfoAboutDancer(
    const ChorbDancer& dancer) {
  std::string info;
  info += dancer.getLeftDancer()->getNickname();

  if (dancer.hasGrabbedLeftDancer()) {
    info += " <-";
  } else {
    info += " --";
  }

  if (dancer.getLeftDancer()->hasGrabbedRightDancer()) {
    info += "-> ";
  } else {
    info += "- ";
  }

  info += dancer.getNickname();

  if (dancer.getRightDancer()->hasGrabbedLeftDancer()) {
    info += " <";
  } else {
    info += " -";
  }

  if (dancer.hasGrabbedRightDancer()) {
    info += "--> ";
  } else {
    info += "-- ";
  }

  info += dancer.getRightDancer()->getNickname();

  std::cout << info << std::endl;
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

void ConsoleChorbRoundDanceView::showAvailableCommands() {
  std::cout << "The available commands are:\n";
  std::cout << "\tprint -> prints all participants in the dance\n";
  std::cout << "\tinfo <who|all>\n";
  std::cout << "\tadd <who> <left dancer label> <right dancer label>\n";
  std::cout << "\tremove <who>\n";
  std::cout << "\tswap <who1> <who2>\n";
  std::cout << "\tgrab <who> <left|right|both>\n";
  std::cout << "\trelease <who> <left|right|both>\n";
  std::cout << "\texit\n";
}
