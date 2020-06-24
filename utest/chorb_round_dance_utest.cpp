#include <iostream>
#include <string>
#include <vector>

#include "catch.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_director.hpp"

// TODO DV doc
// The below function is also a demo of the builder pattern
// Example: If numberOfDancers is 3, the constructed dance will have dancers
// with names "dancer1", "dancer2" and "dancer3"
ChorbRoundDance* createTestChorbRoundDance(int numberOfDancers) {
  StandartChorbRoundDanceBuilder builder;
  ChorbRoundDanceDirector director;
  director.setBuilder(&builder);

  std::vector<std::string> nicknames;
  for (int i = 1; i <= numberOfDancers; i++) {
    nicknames.push_back("dancer" + std::to_string(i));
  }

  ChorbRoundDance* dance = director.createChorbRoundDance(nicknames);
  return dance;
}

SCENARIO("Test building of round dance is correct") {
  GIVEN("A round dance with 4 dancers") {
    ChorbRoundDance* dance = createTestChorbRoundDance(4);

    WHEN("We retrieve all the dancers") {
      std::vector<ChorbDancer> dancers = dance->getDancers();

      THEN("The dancers should have correct nicknames") {
        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer1");
        ++it;
        REQUIRE(it->getNickname() == "dancer2");
        ++it;
        REQUIRE(it->getNickname() == "dancer3");
        ++it;
        REQUIRE(it->getNickname() == "dancer4");
        ++it;
        REQUIRE(it == dancers.end());
      }

      THEN(
          "All the dancers should have grabbed their left and right partners") {
        for (const auto& dancer : dancers) {
          REQUIRE(dancer.hasGrabbedLeftDancer());
          REQUIRE(dancer.hasGrabbedRightDancer());
        }
      }

      THEN("The left and right partners of all dancers should be correct") {
        auto it = dancers.begin();
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

        ++it;
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1");
      }
    }

    delete dance;
  }
}

SCENARIO("Adding dancer to built round dance is correct") {
  GIVEN("A round dance with 4 dancers") {
    ChorbRoundDance* dance = createTestChorbRoundDance(4);

    WHEN("We add a new dancer between the first and the second dancers") {
      REQUIRE(dance->addDancer("dancer1.5", "dancer1", "dancer2") == true);

      THEN("The dancers should have correct nicknames") {
        auto dancers = dance->getDancers();
        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer1");
        ++it;
        REQUIRE(it->getNickname() == "dancer1.5");
        ++it;
        REQUIRE(it->getNickname() == "dancer2");
        ++it;
        REQUIRE(it->getNickname() == "dancer3");
        ++it;
        REQUIRE(it->getNickname() == "dancer4");
        ++it;
        REQUIRE(it == dancers.end());
      }

      THEN("The left and right partners of all dancers should be correct") {
        // We should have: d1 d1.5 d2 d3 d4
        auto dancers = dance->getDancers();
        auto it = dancers.begin();
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1.5");

        ++it;
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1.5");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

        ++it;
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1");
      }

      THEN(
          "All the dancers should have grabbed their left and right partners") {
        auto dancers = dance->getDancers();
        for (const auto& dancer : dancers) {
          REQUIRE(dancer.hasGrabbedLeftDancer());
          REQUIRE(dancer.hasGrabbedRightDancer());
        }
      }
    }

    WHEN("We try to add a dancer between the second and the fourth dancers") {
      THEN(
          "The operation should fail because the second and fourth dancers are "
          "not neighbors") {
        REQUIRE(dance->addDancer("SOME_DANCER_NAME", "dancer2", "dancer4") ==
                false);
      }
    }

    delete dance;
  }
}
