#include "presenter/chorb_round_dance_presenter.hpp"

#include <sstream>

#include "model/round_dance_exceptions.hpp"

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
  try {
    dance->grab(who, grabbingDirection);
  } catch (const NonExistingDancerException& ex) {
    view->showError("The dancer " + who + " does not exist!");
  }
}

void ChorbRoundDancePresenter::onRelease(const std::string& who,
                                         Direction releaseDirection) {
  try {
    dance->release(who, releaseDirection);
  } catch (const NonExistingDancerException& ex) {
    view->showError("The dancer " + who + " does not exist!");
  }
}

void ChorbRoundDancePresenter::onSwap(const std::string& dancer1,
                                      const std::string& dancer2) {
  if (!dance->swap(dancer1, dancer2)) {
    view->showError(
        "Couldn't perform swap. Either the dancers are not neighbors or they "
        "are not released by their neighbors.");
  } else {
    view->showMessage("Swap successful");
  }
}

void ChorbRoundDancePresenter::onExit() {
  delete dance;
  view->showMessage("Bye, bye... Thanks for playing the dance!\n");
  std::exit(0);  // TODO better exit flow?
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
