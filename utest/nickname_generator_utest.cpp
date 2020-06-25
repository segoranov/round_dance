#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "catch.hpp"
#include "nickname_generator.hpp"

TEST_CASE("Nickname generator generates nicknames correctly from stream") {
  constexpr const char* const tempFileContent =
      "dancer1\ndancer2\ndancer3\ndancer4";
  constexpr const char* const tempFileName =
      "TMP_TEST_INPUT_FILE_WITH_DANCERS_NICKNAMES.txt";

  std::stringstream ss;
  ss << std::string{tempFileContent};

  const auto generatedNicknames = NicknameGenerator::fromStream(ss);
  std::vector<std::string> expectedNicknames{"dancer1", "dancer2", "dancer3",
                                             "dancer4"};

  REQUIRE(generatedNicknames == expectedNicknames);
}
