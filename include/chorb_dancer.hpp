#ifndef CHORB_DANCER_HPP_22062020
#define CHORB_DANCER_HPP_22062020

#include <string>

// TODO DV Add documentation for below classes/methods where appropriate

class ChorbDancer;

class ChorbDancer {
 private:
  std::string nickname;

  ChorbDancer* dancerToTheLeft{nullptr};
  bool grabbedDancerToTheLeft{false};

  ChorbDancer* dancerToTheRight{nullptr};
  bool grabbedDancerToTheRight{false};

 public:
  explicit ChorbDancer(const std::string& nickname);

  bool hasGrabbedDancerToTheLeft() const noexcept;
  void grabLeftDancer();
  void releaseLeftDancer();
  void setLeftDancer(ChorbDancer* dancer);
  const ChorbDancer* getDancerToTheLeft() const;

  bool hasGrabbedDancerToTheRight() const noexcept;
  void grabRightDancer();
  void releaseRightDancer();
  void setRightDancer(ChorbDancer* dancer);
  const ChorbDancer* getDancerToTheRight() const;

  std::string getNickname() const noexcept;
};

#endif
