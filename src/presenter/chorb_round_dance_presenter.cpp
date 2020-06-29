#include "presenter/chorb_round_dance_presenter.hpp"

#include <sstream>

ChorbRoundDancePresenter::ChorbRoundDancePresenter(
    ChorbRoundDance* dance, ChorbRoundDanceView::UPtr view)
    : dance(dance), view(std::move(view)) {}

void ChorbRoundDancePresenter::onAddDancer(const std::string& newDancer,
                                           const std::string& leftDancer,
                                           const std::string& rightDancer) {
  if (dance->getDancer(newDancer).has_value()) {
    view->showError("Dancer '" + newDancer + "' already exists!");
    return;
  }

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

void ChorbRoundDancePresenter::onRemoveDancer(const std::string& dancer) {
  const bool dancerRemoved = dance->removeDancer(dancer);

  if (dancerRemoved && dance->getDancers().size() == 2) {
    view->showMessage("...and the music stops!");
    onExit();
    return;
  }

  if (dancerRemoved) {
    view->showMessage("Free at last!");
  } else {
    view->showMessage("This won't be so easy!");
  }
}

void ChorbRoundDancePresenter::onGrab(const std::string& who,
                                      Direction grabbingDirection) {
  dance->grab(who, grabbingDirection);
}

void ChorbRoundDancePresenter::onRelease(const std::string& who,
                                         Direction releaseDirection) {
  dance->release(who, releaseDirection);
}

void ChorbRoundDancePresenter::onExit() {
  delete dance;
  view->showMessage("Bye, bye... Thanks for playing the dance!\n");
  std::exit(0); // TODO better exit code
}

void ChorbRoundDancePresenter::onShowDancerInfo(const std::string& dancer) {
  auto optDancer = dance->getDancer(dancer);
  if (!optDancer.has_value()) {
    view->showMessage("The dancer " + dancer + " does not exist.");
  } else {
    view->showInfoAboutDancer(optDancer.value());
  }
}

void ChorbRoundDancePresenter::onShowAllDancersInfo() {
  for (const auto& dancer : dance->getDancers()) {
    view->showInfoAboutDancer(dancer);
  }
}

void ChorbRoundDancePresenter::onShowRoundDance() {
  view->showRoundDance(*dance);
}

void ChorbRoundDancePresenter::showPrompt(const std::string& prompt) {
  view->showPrompt(prompt);
}

void ChorbRoundDancePresenter::showMessage(const std::string& message) {
  view->showMessage(message);
}

void ChorbRoundDancePresenter::onUserError(const std::string& error) {
  view->showError(error);
}

void ChorbRoundDancePresenter::showAvailableCommands() {
  view->showAvailableCommands();
}
