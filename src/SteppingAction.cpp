#include "SteppingAction.h"

SteppingAction::SteppingAction(RunAction* runAction):
        G4UserSteppingAction(),
        fRunAction(runAction)
{}

SteppingAction::~SteppingAction(){}

void SteppingAction::UserSteppingAction(const G4Step* step){
    // get volume of the current step
    G4LogicalVolume* volume
            = step->GetPreStepPoint()->GetTouchableHandle()
                    ->GetVolume()->GetLogicalVolume();

    // collect energy deposited in this step
    G4double edep = step->GetTotalEnergyDeposit();
    fRunAction->AddEventScore(volume, edep);
}