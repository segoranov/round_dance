#ifndef CHORB_ROUND_DANCE_PRESENTER_HPP_26062020
#define CHORB_ROUND_DANCE_PRESENTER_HPP_26062020

#include <string>

#include "model/chorb_dancer.hpp"
#include "model/chorb_round_dance.hpp"
#include "view/chorb_round_dance_view.hpp"

// TODO should we have an interface for the presenter?
class ChorbRoundDancePresenter {
 private:
  ChorbRoundDance* dance{nullptr};
  ChorbRoundDanceView::UPtr view{nullptr};

 public:
  ChorbRoundDancePresenter() = default;
  ChorbRoundDancePresenter(ChorbRoundDance* dance,
                           ChorbRoundDanceView::UPtr view);

  void onAddDancer(const std::string& newDancer, const std::string& leftDancer,
                   const std::string& rightDancer);
  void onRemoveDancer(const std::string& dancer);
  void onGrab(const std::string& who, Direction grabbingDirection);
  void onRelease(const std::string& who, Direction releaseDirection);
  void onExit();

  void onShowDancerInfo(const std::string& dancer);
  void onShowAllDancersInfo();
  void onShowRoundDance();

  void showMessage(const std::string& message);

  void showPrompt(const std::string& prompt);

  void onUserError(const std::string& error);

  void showAvailableCommands();
};

#endif
