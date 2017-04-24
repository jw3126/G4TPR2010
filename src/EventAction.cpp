#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include "EventAction.h"
#include "G4Event.hh"

EventAction::EventAction(RunAction *runAction) : G4UserEventAction(), fRunAction(runAction) {}
EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* ){
}

void EventAction::EndOfEventAction(const G4Event* ) {
    fRunAction->FinishEvent();
}