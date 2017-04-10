#include <G4ios.hh>
#include <G4AccumulableManager.hh>
#include "RunAction.h"

RunAction::RunAction() : fDose("Dose10", 0)
{
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fDose);
}

RunAction::~RunAction(){}

void RunAction::UpdateDose10(G4double dose){
    fDose += dose;
}

void RunAction::BeginOfRunAction(const G4Run* ){
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}

void RunAction::EndOfRunAction(const G4Run* ){

    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    G4double dose10 = fDose.GetValue();
    if (IsMaster()) {
        G4cout
                << G4endl
                << "--------------------End of Global Run-----------------------"
                << G4endl
                ;
    }
    else {
        G4cout
                << G4endl
                << "--------------------End of Local Run------------------------"
                << G4endl
                ;
    }
    G4cout << "dose10:" << dose10 << G4endl;
}