#ifndef G4TPR2010_STEPPINGACTION_H
#define G4TPR2010_STEPPINGACTION_H

#include <G4UserSteppingAction.hh>
#include <G4ios.hh>
#include "G4Step.hh"
#include "G4StepPoint.hh"


class SteppingAction : public G4UserSteppingAction {

public:
    SteppingAction();
    ~SteppingAction();
    virtual void UserSteppingAction(const G4Step* step);
};

#endif //G4TPR2010_STEPPINGACTION_H
