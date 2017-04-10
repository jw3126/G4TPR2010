#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include "EventAction.h"
#include "G4Event.hh"

EventAction::EventAction(RunAction *runAction) : G4UserEventAction(), fRunAction(runAction) {}
EventAction::~EventAction() {}

void EventAction::BeginOfEventAction(const G4Event* ){
}

// should this be put into a class?
// why is this so involved, is there a simpler way?
G4double ReadScorer(const G4Event* evt, const G4String scorerName, const G4int copyNo=0) {

    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
    G4int collectionID = sdManager->GetCollectionID(scorerName);

    G4VHitsCollection* hitCollection = HCE->GetHC(collectionID);
    G4THitsMap<G4double>* tHitsMap = dynamic_cast<G4THitsMap<G4double>*>(hitCollection); // const_cast? static_cast?

    // only keys of copyNo's with a hit are in the hitsMap
    std::map<G4int, G4double*>* hitsMap = tHitsMap->GetMap();

    std::map<int, double *>::iterator pos;
    pos = hitsMap->find(copyNo);
    if (pos == hitsMap -> end())
    {
        //G4cout << copyNo << "not in hitsMap" << G4endl;
        return 0.;
    } else {
        //G4cout << "hit" << G4endl;
        return *(pos->second);
    }

}


void EventAction::EndOfEventAction(const G4Event* evt) {

    G4double dose = ReadScorer(evt, "detector/dose");
    fRunAction->UpdateDose(dose);

}