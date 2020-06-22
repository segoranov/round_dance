#ifndef CHORB_DANCER_HPP_22062020
#define CHORB_DANCER_HPP_22062020

#include <string>

// TODO DV Add documentation for below classes/methods where appropriate

class ChorbDancer;

struct AdjacentDancersInfo {
  AdjacentDancersInfo(ChorbDancer* dancerToTheLeft, bool grabbedDancerToTheLeft,
                      ChorbDancer* dancerToTheRight,
                      bool grabbedDancerToTheRight);

  ChorbDancer* dancerToTheLeft;
  bool grabbedDancerToTheLeft;

  ChorbDancer* dancerToTheRight;
  bool grabbedDancerToTheRight;
};

class ChorbDancer {
 private:
  std::string nickName;
  AdjacentDancersInfo adjacentDancersInfo;

 public:
  explicit ChorbDancer(const std::string& nickName,
                       const AdjacentDancersInfo& adjacentDancersInfo);

  bool hasGrabbedLeftDancer() const noexcept;
  void grabLeftDancer();
  void releaseLeftDancer();

  bool hasGrabbedRightDancer() const noexcept;
  void grabRightDancer();
  void releaseRightDancer();
};

#endif
