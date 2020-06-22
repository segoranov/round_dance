#include "catch.hpp"
#include "chorb_round_dance_builder.hpp"

SCENARIO("Test building of round dance") {
  GIVEN("Chorb round dance with 3 dancers") {
    ChorbRoundDanceBuilder builder;
    builder.addDancer("dancer1");
    builder.addDancer("dancer2");
    builder.addDancer("dancer3");
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
        REQUIRE(it == dancers.end());
      }

      THEN(
          "All the dancers should have grabbed their left and right partners") {
        auto it = dancers.begin();
        REQUIRE(it->hasGrabbedDancerToTheLeft() && it->hasGrabbedDancerToTheRight());
        ++it;
        REQUIRE(it->hasGrabbedDancerToTheLeft() && it->hasGrabbedDancerToTheRight());
        ++it;
        REQUIRE(it->hasGrabbedDancerToTheLeft() && it->hasGrabbedDancerToTheRight());
      }
    }
  }
}
