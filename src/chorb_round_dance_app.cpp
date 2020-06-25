#include "chorb_round_dance_app.hpp"

#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_director.hpp"
#include "nickname_generator.hpp"

void ChorbRoundDanceApp::generateDance(const std::string& file) {
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
  dance = director.createChorbRoundDance(nicknames);

  std::cout << "Created chorb round dance with the following dancers:\n";
  for (const auto& dancer : dance->getDancers()) {
    std::cout << dancer.getNickname() << std::endl;
  }
}

void ChorbRoundDanceApp::run() {
  std::string userInput;
  while (true) {
    std::cout << "Enter command: ";
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
    // TODO View component instead of simple cout
    // TODO Add ChorbRoundDanceApp to uml diagram
    if (command == "add") {
      const std::string& newDancer = tokens[1];
      const std::string& leftDancer = tokens[2];
      const std::string& rightDancer = tokens[3];
      std::cout << "Adding dancer [" << newDancer << "]"
                << " between "
                << "[" << leftDancer << "] and [" << rightDancer << "]\n";

      const bool newDancerAddedSuccessfully =
          dance->addDancer(newDancer, leftDancer, rightDancer);

      if (newDancerAddedSuccessfully) {
        std::cout << "Added new dancer between " << leftDancer << " and "
                  << rightDancer << "\n";
      } else {
        std::cout << "Could not add new dancer!\n";  // TODO maybe print reason?
      }

    } else if (command == "exit") {
      break;
    } else {
      std::cout << "Not implemented.\n";  // TODO
    }
  }
}
