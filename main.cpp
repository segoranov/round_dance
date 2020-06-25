#include <iostream>

#include "chorb_round_dance_app.hpp"

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

  try {
    ChorbRoundDanceApp app;
    app.generateDance(inputFile);
    app.run();
  } catch (const std::exception& exc) {  // TODO hierarchy of exceptions
    std::cerr << "Error: " << exc.what() << std::endl;
  } catch (...) {
    std::cerr << "Unexpected error...\n";
  }

  std::cout << "Bye, bye...\n";
}
