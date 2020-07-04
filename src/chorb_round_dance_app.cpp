#include "chorb_round_dance_app.hpp"

#include <fstream>
#include <iterator>
#include <sstream>

#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_director.hpp"
#include "model/round_dance_exceptions.hpp"
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
    throw ChorbRoundDanceException("Could not open file: " + file);
  }

  auto nicknames = NicknameGenerator::fromStream(ifs);
  if (nicknames.size() < 3) {
    throw ChorbRoundDanceException(
        "The input file should contain at least 3 dancers!");
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

    Command command;
    try {
      command = strToCommand(tokens[0]);
    } catch (const InvalidCommandException& ex) {
      presenter.onUserError(
          "Please enter valid command. Type 'help' for more info on commands.");
      continue;
    }

    switch (command) {
      case Command::ADD: {
        onAddCommand(tokens);
        break;
      }

      case Command::REMOVE: {
        onRemoveCommand(tokens);
        break;
      }

      case Command::GRAB: {
        try {
          onGrabCommand(tokens);
        } catch (const InvalidDirectionException& ex) {
          presenter.onUserError(
              "Please enter valid direction - <left|right|both>");
        }
        break;
      }

      case Command::RELEASE: {
        try {
          onReleaseCommand(tokens);
        } catch (const InvalidDirectionException& ex) {
          presenter.onUserError(
              "Please enter valid direction - <left|right|both>");
        }
        break;
      }

      case Command::SWAP: {
        onSwapCommand(tokens);
        break;
      }

      case Command::INFO: {
        onInfoCommand(tokens);
        break;
      }

      case Command::PRINT: {
        presenter.onShowRoundDance();
        break;
      }

      case Command::HELP: {
        presenter.showAvailableCommands();
        break;
      }

      case Command::EXIT: {
        presenter.onExit();
        stillRunning = false;
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
  }
}

void ChorbRoundDanceApp::onSwapCommand(const std::vector<std::string>& tokens) {
  // swap <who1> <who2>

  if (tokens.size() != 3) {
    presenter.onUserError("Invalid command.");
  } else {
    const std::string& dancer1 = tokens[1];
    const std::string& dancer2 = tokens[2];
    presenter.onSwap(dancer1, dancer2);
  }
}

ChorbRoundDanceApp::Command ChorbRoundDanceApp::strToCommand(
    const std::string& command) {
  if (command == "add") return Command::ADD;
  if (command == "grab") return Command::GRAB;
  if (command == "release") return Command::RELEASE;
  if (command == "remove") return Command::REMOVE;
  if (command == "print") return Command::PRINT;
  if (command == "info") return Command::INFO;
  if (command == "exit") return Command::EXIT;
  if (command == "swap") return Command::SWAP;
  if (command == "help") return Command::HELP;
  throw InvalidCommandException{};
}

Direction ChorbRoundDanceApp::strToDirection(const std::string& direction) {
  if (direction == "left") return Direction::LEFT;
  if (direction == "right") return Direction::RIGHT;
  if (direction == "both") return Direction::BOTH;
  throw InvalidDirectionException{};
}
