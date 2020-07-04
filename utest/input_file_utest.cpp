#include <cstdio>
#include <fstream>

#include "catch.hpp"
#include "chorb_round_dance_app.hpp"
#include "model/round_dance_exceptions.hpp"

TEST_CASE("Non existing input file should throw proper exception") {
  REQUIRE_THROWS_AS(ChorbRoundDanceApp{"NON_EXISTING_FILE"},
                    ChorbRoundDanceException);
}

TEST_CASE(
    "Existing input file with less than 3 dancers should throw exception") {
  constexpr const char* const TMP_FILE_NAME = "TEMP_INPUT_FILE";
  std::ofstream tempInputFile{TMP_FILE_NAME};
  REQUIRE(tempInputFile.is_open());
  tempInputFile << "dancer1\ndancer2";
  tempInputFile.close();

  REQUIRE_THROWS_AS(ChorbRoundDanceApp{TMP_FILE_NAME},
                    ChorbRoundDanceException);

  REQUIRE(std::remove(TMP_FILE_NAME) == 0);
}

TEST_CASE(
    "Existing input file containing dancer with more than 30 symbols nickname "
    "should throw exception") {
  constexpr const char* const TMP_FILE_NAME = "TEMP_INPUT_FILE";
  std::ofstream tempInputFile{TMP_FILE_NAME};
  REQUIRE(tempInputFile.is_open());
  tempInputFile
      << "dancer1\ndancer2\nTOO_LONG_NICKNAME_CONTAINING_MORE_THAN_THIRTY_SY"
         "MBOLS\ndancer4\ndancer5";
  tempInputFile.close();

  REQUIRE_THROWS_AS(ChorbRoundDanceApp{TMP_FILE_NAME},
                    TooLongNicknameException);

  REQUIRE(std::remove(TMP_FILE_NAME) == 0);
}

TEST_CASE("Existing input file with 3 dancers should not throw exception") {
  constexpr const char* const TMP_FILE_NAME = "TEMP_INPUT_FILE";
  std::ofstream tempInputFile{TMP_FILE_NAME};
  REQUIRE(tempInputFile.is_open());
  tempInputFile << "dancer1\ndancer2\ndancer3";
  tempInputFile.close();

  REQUIRE_NOTHROW(ChorbRoundDanceApp{TMP_FILE_NAME});

  REQUIRE(std::remove(TMP_FILE_NAME) == 0);
}
