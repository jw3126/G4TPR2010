#include "ActionInitialization.h"

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    RunAction* runAction = new RunAction(fRunParameters);
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{

    PrimaryGeneratorAction* primaryGeneratorAction = new PrimaryGeneratorAction(fRunParameters);
    SetUserAction(primaryGeneratorAction);

    SteppingAction* steppingAction = new SteppingAction();
    SetUserAction(steppingAction);

    RunAction* runAction = new RunAction(fRunParameters);
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
}