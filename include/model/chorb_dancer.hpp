#ifndef CHORB_DANCER_HPP_22062020
#define CHORB_DANCER_HPP_22062020

#include <string>

class ChorbDancer {
 private:
  std::string nickname;

  ChorbDancer* pLeftDancer{nullptr};
  bool grabbedLeftDancer{false};

  ChorbDancer* pRightDancer{nullptr};
  bool grabbedRightDancer{false};

 public:
  ChorbDancer() = default;
  explicit ChorbDancer(const std::string& nickname);

  bool hasGrabbedLeftDancer() const noexcept;
  void grabLeftDancer();
  void releaseLeftDancer();
  void setLeftDancer(ChorbDancer* dancer);
  const ChorbDancer* getLeftDancer() const;

  bool hasGrabbedRightDancer() const noexcept;
  void grabRightDancer();
  void releaseRightDancer();
  void setRightDancer(ChorbDancer* dancer);
  const ChorbDancer* getRightDancer() const;

  std::string getNickname() const noexcept;
};

#endif
