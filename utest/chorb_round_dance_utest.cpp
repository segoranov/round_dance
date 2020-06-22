#include "catch.hpp"
#include "chorb_round_dance_builder/chorb_round_dance_builder.hpp"

SCENARIO("Test building of round dance is correct") {
  GIVEN("Chorb round dance with 3 dancers") {
    ChorbRoundDanceBuilder builder;
    builder.addDancer("dancer1");
    builder.addDancer("dancer2");
    builder.addDancer("dancer3");
    builder.addDancer("dancer4");
    ChorbRoundDance dance = builder.getRoundDance();

    WHEN("We retrieve all the dancers") {
      std::list<ChorbDancer> dancers = dance.getDancers();

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
        auto it = dancers.begin();
        REQUIRE(it->hasGrabbedDancerToTheLeft());
        REQUIRE(it->hasGrabbedDancerToTheRight());
        ++it;
        REQUIRE(it->hasGrabbedDancerToTheLeft());
        REQUIRE(it->hasGrabbedDancerToTheRight());
        ++it;
        REQUIRE(it->hasGrabbedDancerToTheLeft());
        REQUIRE(it->hasGrabbedDancerToTheRight());
        ++it;
        REQUIRE(it->hasGrabbedDancerToTheLeft());
        REQUIRE(it->hasGrabbedDancerToTheRight());
      }

      THEN("The left and right partners of all dancers should be correct") {
        auto it = dancers.begin();
        REQUIRE(it->getDancerToTheLeft()->getNickname() == "dancer4");
        REQUIRE(it->getDancerToTheRight()->getNickname() == "dancer2");

        ++it;
        REQUIRE(it->getDancerToTheLeft()->getNickname() == "dancer1");
        REQUIRE(it->getDancerToTheRight()->getNickname() == "dancer3");

        ++it;
        REQUIRE(it->getDancerToTheLeft()->getNickname() == "dancer2");
        REQUIRE(it->getDancerToTheRight()->getNickname() == "dancer4");

        ++it;
        REQUIRE(it->getDancerToTheLeft()->getNickname() == "dancer3");
        REQUIRE(it->getDancerToTheRight()->getNickname() == "dancer1");
      }
    }
  }
}
