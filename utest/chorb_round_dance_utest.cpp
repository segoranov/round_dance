#include <cassert>
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
  assert(numberOfDancers >= 3);
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

      // TODO!!! extract the below check for order and nicknames in a function
      // It is currently used 3 times and there is a lot code duplication
      // Also, what if we want to create a test with 10000 dancers?
      // This function will be needed!
      THEN(
          "The dancers should have correct nicknames and be in correct order") {
        // We should have: d1 d2 d3 d4

        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer1");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getNickname() == "dancer2");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getNickname() == "dancer3");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

        ++it;
        REQUIRE(it->getNickname() == "dancer4");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1");

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
    }

    delete dance;
  }
}

SCENARIO("Adding dancer to built round dance is correct") {
  GIVEN("A round dance with 4 dancers") {
    ChorbRoundDance* dance = createTestChorbRoundDance(4);

    WHEN("We add a new dancer between the first and the second dancers") {
      REQUIRE(dance->addDancer("dancer1.5", "dancer1", "dancer2") == true);

      THEN(
          "The dancers should have correct nicknames and be in correct order") {
        // We should have: d1 d1.5 d2 d3 d4

        auto dancers = dance->getDancers();
        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer1");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1.5");

        ++it;
        REQUIRE(it->getNickname() == "dancer1.5");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getNickname() == "dancer2");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1.5");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getNickname() == "dancer3");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

        ++it;
        REQUIRE(it->getNickname() == "dancer4");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1");

        ++it;
        REQUIRE(it == dancers.end());
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

    WHEN("We add a dancer between the first and the last dancers") {
      REQUIRE(dance->addDancer("dancer4.5", "dancer4", "dancer1") == true);

      THEN(
          "The dancers should have correct nicknames and be in correct order") {
        // We should have: d1 d2 d3 d4 d4.5

        auto dancers = dance->getDancers();
        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer1");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4.5");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getNickname() == "dancer2");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getNickname() == "dancer3");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

        ++it;

        REQUIRE(it->getNickname() == "dancer4");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4.5");

        ++it;
        REQUIRE(it->getNickname() == "dancer4.5");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1");

        ++it;
        REQUIRE(it == dancers.end());
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

    delete dance;
  }

  GIVEN("A round dance with 3 dancers") {
    ChorbRoundDance* dance = createTestChorbRoundDance(3);
    WHEN("We add 3 new dancers") {
      // We have d1 d2 d3
      REQUIRE(dance->addDancer("dancer1.5", "dancer1", "dancer2") == true);
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer1", "dancer2") ==
              false);
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer2", "dancer1") ==
              false);

      // Now we have d1 d1.5 d2 d3
      REQUIRE(dance->addDancer("dancer3.5", "dancer1", "dancer3") == true);
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer1", "dancer3") ==
              false);
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer3", "dancer1") ==
              false);

      // Now we have d1 d1.5 d2 d3 d3.5
      REQUIRE(dance->addDancer("dancer2.5", "dancer3", "dancer2") == true);
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer3", "dancer2") ==
              false);
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer2", "dancer3") ==
              false);

      // Now we have d1 d1.5 d2 d2.5 d3 d3.5
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer1", "dancer3") ==
              false);
      REQUIRE(dance->addDancer("SHOULD_NOT_BE_ADDED", "dancer1.5", "dancer3") ==
              false);

      THEN(
          "The dancers should have correct nicknames and be in correct order") {
        // We should have d1 d1.5 d2 d2.5 d3 d3.5
        auto dancers = dance->getDancers();
        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer1");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3.5");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1.5");

        ++it;
        REQUIRE(it->getNickname() == "dancer1.5");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getNickname() == "dancer2");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1.5");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2.5");

        ++it;
        REQUIRE(it->getNickname() == "dancer2.5");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;

        REQUIRE(it->getNickname() == "dancer3");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2.5");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3.5");

        ++it;
        REQUIRE(it->getNickname() == "dancer3.5");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1");

        ++it;
        REQUIRE(it == dancers.end());
      }
    }

    delete dance;
  }
}

TEST_CASE("Releasing and grabbing of dancers is correct") {
  ChorbRoundDance* dance = createTestChorbRoundDance(5);

  REQUIRE(dance->getDancer("dancer3")->hasGrabbedLeftDancer());
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedRightDancer());

  // release and grab left dancer (dancer2 <--> dancer3)
  dance->release("dancer3", Direction::LEFT);
  REQUIRE(!dance->getDancer("dancer3")->hasGrabbedLeftDancer());
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedRightDancer());

  dance->grab("dancer3", Direction::LEFT);
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedLeftDancer());
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedRightDancer());

  // release and grab right dancer (dancer3 <--> dancer4)
  dance->release("dancer3", Direction::RIGHT);
  REQUIRE(!dance->getDancer("dancer3")->hasGrabbedRightDancer());
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedLeftDancer());

  dance->grab("dancer3", Direction::RIGHT);
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedLeftDancer());
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedRightDancer());

  // release both and grab both left and right
  dance->release("dancer3", Direction::BOTH);
  REQUIRE(!dance->getDancer("dancer3")->hasGrabbedRightDancer());
  REQUIRE(!dance->getDancer("dancer3")->hasGrabbedLeftDancer());

  dance->grab("dancer3", Direction::BOTH);
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedRightDancer());
  REQUIRE(dance->getDancer("dancer3")->hasGrabbedLeftDancer());
}

SCENARIO("Removing a dancer from chorb round dance is correct") {
  GIVEN("A round dance with 5 dancers") {
    ChorbRoundDance* dance = createTestChorbRoundDance(5);

    WHEN("We try to remove the 3rd dancer") {
      THEN(
          "The removal should fail because he is not released by his neighbors "
          "and he has not released them") {
        REQUIRE(!dance->removeDancer("dancer3"));
      }
    }

    AND_WHEN("The 3rd dancer releases his neighbors and they release him") {
      dance->release("dancer3", Direction::BOTH);
      dance->release("dancer4", Direction::LEFT);
      dance->release("dancer2", Direction::RIGHT);

      THEN("The removal should be successful") {
        REQUIRE(dance->removeDancer("dancer3"));

        AND_THEN("The dance should have 4 dancers") {
          REQUIRE(dance->getDancers().size() == 4);
        }

        AND_THEN(
            "The dancers should have correct nicknames and be in correct "
            "order") {
          // We should have d1 <--> d2 <--> d4 <--> d5
          auto dancers = dance->getDancers();
          auto it = dancers.begin();
          REQUIRE(it->getNickname() == "dancer1");
          REQUIRE(it->getLeftDancer()->getNickname() == "dancer5");
          REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

          ++it;
          REQUIRE(it->getNickname() == "dancer2");
          REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
          REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

          ++it;
          REQUIRE(it->getNickname() == "dancer4");
          REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
          REQUIRE(it->getRightDancer()->getNickname() == "dancer5");

          ++it;
          REQUIRE(it->getNickname() == "dancer5");
          REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
          REQUIRE(it->getRightDancer()->getNickname() == "dancer1");

          ++it;
          REQUIRE(it == dancers.end());
        }
      }
    }

    WHEN("We remove the first dancer") {
      dance->release("dancer1", Direction::BOTH);
      dance->release("dancer5", Direction::RIGHT);
      dance->release("dancer2", Direction::LEFT);
      REQUIRE(dance->removeDancer("dancer1"));

      THEN(
          "The dancers should have correct nicknames and be in correct "
          "order") {
        // We should have d2<--> d3 <--> d4 <--> d5
        auto dancers = dance->getDancers();
        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer2");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer5");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getNickname() == "dancer3");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

        ++it;
        REQUIRE(it->getNickname() == "dancer4");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer5");

        ++it;
        REQUIRE(it->getNickname() == "dancer5");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it == dancers.end());
      }
    }

    WHEN("We remove the last dancer") {
      dance->release("dancer5", Direction::BOTH);
      dance->release("dancer4", Direction::RIGHT);
      dance->release("dancer1", Direction::LEFT);
      REQUIRE(dance->removeDancer("dancer5"));

      THEN(
          "The dancers should have correct nicknames and be in correct "
          "order") {
        // We should have d1 <--> d2 <--> d3 <--> d4
        auto dancers = dance->getDancers();
        auto it = dancers.begin();
        REQUIRE(it->getNickname() == "dancer1");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer4");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getNickname() == "dancer2");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer1");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getNickname() == "dancer3");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer2");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer4");

        ++it;
        REQUIRE(it->getNickname() == "dancer4");
        REQUIRE(it->getLeftDancer()->getNickname() == "dancer3");
        REQUIRE(it->getRightDancer()->getNickname() == "dancer1");

        ++it;
        REQUIRE(it == dancers.end());
      }

      delete dance;
    }
  }
}
