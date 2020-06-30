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

  presenter.showMessage("Hello and welcome to the chorb round dance app!\n");
  presenter.showAvailableCommands();

  while (stillRunning) {
    presenter.showPrompt("Enter command (type 'help' to show commands)");
    std::getline(std::cin, userInput);

    std::istringstream iss(userInput);
    std::vector<std::string> tokens{std::istream_iterator<std::string>{iss},
                                    std::istream_iterator<std::string>{}};

    if (tokens.empty()) {
      presenter.onUserError("You did not enter any command.");
      continue;
    }

    COMMAND command;
    try {
      command = strToCommand(tokens[0]);
    } catch (...) {  // TODO catch InvalidCommandException
      presenter.onUserError("Non existing command.");
      continue;
    }

    switch (command) {
      case COMMAND::ADD: {
        onAddCommand(tokens);
        break;
      }

      case COMMAND::REMOVE: {
        onRemoveCommand(tokens);
        break;
      }

      case COMMAND::GRAB: {
        try {
          onGrabCommand(tokens);
        } catch (...) {  // TODO catch InvalidDircetionException
          presenter.onUserError("Invalid direction");
        }
        break;
      }

      case COMMAND::RELEASE: {
        try {
          onReleaseCommand(tokens);
        } catch (...) {  // TODO catch InvalidDircetionException
          presenter.onUserError("Invalid direction");
        }
        break;
      }

      case COMMAND::INFO: {
        onInfoCommand(tokens);
        break;
      }

      case COMMAND::PRINT: {
        presenter.onShowRoundDance();
        break;
      }

      case COMMAND::HELP: {
        presenter.showAvailableCommands();
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

void ChorbRoundDanceApp::onInfoCommand(const std::vector<std::string>& tokens) {
  // info <who>

  if (tokens.size() != 2) {
    presenter.onUserError("Invalid command.");
  } else {
    const std::string& who = tokens[1];
    if (who == "all") {
      presenter.onShowAllDancersInfo();
    } else {
      presenter.onShowDancerInfo(who);
    }
  }
}

void ChorbRoundDanceApp::onRemoveCommand(
    const std::vector<std::string>& tokens) {
  // remove <who>

  if (tokens.size() != 2) {
    presenter.onUserError("Invalid command.");
  } else {
    const std::string& dancer = tokens[1];
    presenter.onRemoveDancer(dancer);
  }
}

void ChorbRoundDanceApp::onReleaseCommand(
    const std::vector<std::string>& tokens) {
  // release <who> <left|right|both>
  if (tokens.size() != 3) {
    presenter.onUserError("Invalid command.");
  } else {
    const std::string& dancer = tokens[1];
    Direction direction = strToDirection(tokens[2]);
    presenter.onRelease(dancer, direction);
    presenter.onShowDancerInfo(dancer);
  }
}

void ChorbRoundDanceApp::onGrabCommand(const std::vector<std::string>& tokens) {
  // grab <who> <left|right|both>

  if (tokens.size() != 3) {
    presenter.onUserError("Invalid command.");
  } else {
    const std::string& dancer = tokens[1];
    Direction direction = strToDirection(tokens[2]);
    presenter.onGrab(dancer, direction);
    presenter.onShowDancerInfo(dancer);
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
  if (command == "help") return COMMAND::HELP;
  throw "Undefined command";  // TODO UndefinedCommandException
}

Direction ChorbRoundDanceApp::strToDirection(const std::string& direction) {
  if (direction == "left") return Direction::LEFT;
  if (direction == "right") return Direction::RIGHT;
  if (direction == "both") return Direction::BOTH;
  throw "Invalid direction";  // TODO InvalidDirectionException
}
