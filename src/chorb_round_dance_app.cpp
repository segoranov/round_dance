#include "chorb_round_dance_app.hpp"

#include <fstream>
#include <iterator>
#include <sstream>

#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_director.hpp"
#include "nickname_generator.hpp"
#include "view/console_chorb_round_dance_view.hpp"

ChorbRoundDanceApp::ChorbRoundDanceApp(const std::string& file) {
  auto dance = generateDance(file);
  presenter = ChorbRoundDancePresenter{
      dance, std::make_unique<ConsoleChorbRoundDanceView>()};
}

ChorbRoundDance* ChorbRoundDanceApp::generateDance(const std::string& file) {
  std::ifstream ifs{file};

  if (!ifs.is_open()) {
    throw "Could not open file: " + file;  // TODO hierarchy of exceptions
  }

  auto nicknames = NicknameGenerator::fromStream(ifs);
  if (nicknames.size() < 3) {
    // TODO hierarchy of exceptions
    throw "The input file should contain at least 3 dancers!";
  }

  ifs.close();

  StandartChorbRoundDanceBuilder builder;
  ChorbRoundDanceDirector director;
  director.setBuilder(&builder);
  return director.createChorbRoundDance(nicknames);
}

void ChorbRoundDanceApp::run() {
  std::string userInput;

  volatile bool stillRunning = true;
  while (stillRunning) {
    presenter.showPrompt("Enter command");
    std::getline(std::cin, userInput);

    std::istringstream iss(userInput);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};

    if (tokens.empty()) {
      presenter.onUserError("You did not enter any command.");
      continue;
    }

    COMMAND command = strToCommand(tokens[0]);

    switch (command) {
      case COMMAND::ADD: {
        onAddCommand(tokens);
        break;
      }

      case COMMAND::UNDEFINED: {
        presenter.onUserError("Non existing command.");
        break;
      }

      case COMMAND::EXIT: {
        presenter.onExit();
        stillRunning = false;
        break;
      }

      default: {
        // TODO implement all commands
        presenter.onUserError("Not implemented yet!");
        break;
      }
    }
  }
}

void ChorbRoundDanceApp::onAddCommand(const std::vector<std::string>& tokens) {
  // add <who> <leftDancer> <rightDancer>

  if (tokens.size() != 4) {
    presenter.onUserError("Invalid command.");
  } else {
    const std::string& newDancer = tokens[1];
    const std::string& leftDancer = tokens[2];
    const std::string& rightDancer = tokens[3];
    presenter.onAddDancer(newDancer, leftDancer, rightDancer);
  }
}

ChorbRoundDanceApp::COMMAND ChorbRoundDanceApp::strToCommand(
    const std::string& command) {
  if (command == "add") return COMMAND::ADD;
  if (command == "grab") return COMMAND::GRAB;
  if (command == "release") return COMMAND::RELEASE;
  if (command == "remove") return COMMAND::REMOVE;
  if (command == "print") return COMMAND::PRINT;
  if (command == "info") return COMMAND::INFO;
  if (command == "exit") return COMMAND::EXIT;
  if (command == "swap") return COMMAND::SWAP;
  return COMMAND::UNDEFINED;
}
