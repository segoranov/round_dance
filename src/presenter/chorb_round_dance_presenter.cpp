#include "presenter/chorb_round_dance_presenter.hpp"

#include <sstream>

ChorbRoundDancePresenter::ChorbRoundDancePresenter(
    ChorbRoundDance* dance, ChorbRoundDanceView::UPtr view)
    : dance(dance), view(std::move(view)) {}

void ChorbRoundDancePresenter::onAddDancer(const std::string& newDancer,
                                           const std::string& leftDancer,
                                           const std::string& rightDancer) {
  const bool newDancerAddedSuccessfully =
      dance->addDancer(newDancer, leftDancer, rightDancer);

  if (newDancerAddedSuccessfully) {
    view->showMessage("Added new dancer between " + leftDancer + " and " +
                      rightDancer);
  } else {
    view->showError("Could not add new dancer '" + newDancer + "'. Reason: '" +
                    leftDancer + "' and '" + rightDancer +
                    "' are not neighbors.");
  }
}

void ChorbRoundDancePresenter::onRemoveDancer(const std::string& dancer) {}

void ChorbRoundDancePresenter::onGrab(const std::string& who,
                                      Direction grabbingDirection) {}

void ChorbRoundDancePresenter::onRelease(const std::string& who,
                                         Direction releaseDirection) {}

void ChorbRoundDancePresenter::onExit() {
  delete dance;
  view->showMessage("Bye, bye... Thanks for playing the dance!\n");
}

void ChorbRoundDancePresenter::onShowDancerInfo(const std::string& dancer) {}

void ChorbRoundDancePresenter::onShowRoundDance(/* TODO param? */) {}

void ChorbRoundDancePresenter::showPrompt(const std::string& prompt) {
  view->showPrompt(prompt);
}

void ChorbRoundDancePresenter::onUserError(const std::string& error) {
  view->showError(error);
}
