#include <iostream>

#include "chorb_round_dance_app.hpp"
#include "view/console_chorb_round_dance_view.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0]
              << " <input file with dancers' nicknames>\n";
    std::cout
        << "The input file contains dancer nickname on each line, like this:\n";
    std::cout << "dancer1\ndancer2\ndancer3\n\n";
    return 1;
  }

  const std::string inputFile = argv[1];

  ChorbRoundDanceApp app{std::make_unique<ConsoleChorbRoundDanceView>()};
  app.generateDance(inputFile);
  app.run();
}
