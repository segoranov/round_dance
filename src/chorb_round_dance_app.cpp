#include "chorb_round_dance_app.hpp"

#include <fstream>
#include <iterator>
#include <sstream>

#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_director.hpp"
#include "nickname_generator.hpp"

ChorbRoundDanceApp::ChorbRoundDanceApp(ChorbRoundDanceView::UPtr view)
    : view{std::move(view)} {}

void ChorbRoundDanceApp::generateDance(const std::string& file) {
  std::ifstream ifs{file};

  if (!ifs.is_open()) {
    const std::string error = "Could not open file: " + file;
    view->showError(error);
    throw "Could not open file: " + file;  // TODO hierarchy of exceptions
  }

  auto nicknames = NicknameGenerator::fromStream(ifs);
  if (nicknames.size() < 3) {
    const std::string error =
        "The input file should contain at least 3 dancers!";
    view->showError(error);
    // TODO hierarchy of exceptions
    throw "The input file should contain at least 3 dancers!";
  }

  ifs.close();

  StandartChorbRoundDanceBuilder builder;
  ChorbRoundDanceDirector director;
  director.setBuilder(&builder);
  dance = director.createChorbRoundDance(nicknames);

  std::string message =
      "Created chorb round dance with the following dancers:\n";

  for (const auto& dancer : dance->getDancers()) {
    message += dancer.getNickname() + '\n';
  }

  view->showMessage(message);
}

void ChorbRoundDanceApp::run() {
  std::string userInput;
  while (true) {
    view->showPrompt("Enter command");

    // TODO who is responsible for gathering user input? (std::getline?)
    // TODO What about Presenter?
    std::getline(std::cin, userInput);

    std::istringstream iss(userInput);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};

    const std::string& command = tokens[0];

    // This is just to see something working. It's not
    // comprehensive nor is it perfectly implemented.
    // TODO create enum for commands and use switch/case
    // TODO error handling
    // TODO parsing in another class/method?
    // TODO Add ChorbRoundDanceApp to uml diagram
    if (command == "add") {
      const std::string& newDancer = tokens[1];
      const std::string& leftDancer = tokens[2];
      const std::string& rightDancer = tokens[3];

      std::ostringstream oss;
      oss << "Trying to add dancer [" << newDancer << "]"
          << " between "
          << "[" << leftDancer << "] and [" << rightDancer << "]";

      view->showMessage(oss.str());

      const bool newDancerAddedSuccessfully =
          dance->addDancer(newDancer, leftDancer, rightDancer);

      if (newDancerAddedSuccessfully) {
        std::ostringstream oss;
        oss << "Added new dancer between " << leftDancer << " and "
            << rightDancer << "";
        view->showMessage(oss.str());
      } else {
        view->showError(
            "Could not add new dancer!");  // TODO print reason for failure?
      }

    } else if (command == "exit") {
      break;
    } else {
      view->showMessage("Not implemented.");  // TODO
    }
  }

  view->showMessage("Bye, bye...");
}
