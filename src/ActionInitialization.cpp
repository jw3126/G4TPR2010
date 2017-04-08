#include "ActionInitialization.h"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization(){}
ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    RunAction* runAction = new RunAction;
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{

    PrimaryGeneratorAction* primaryGeneratorAction = new PrimaryGeneratorAction();
    SetUserAction(primaryGeneratorAction);

    SteppingAction* steppingAction = new SteppingAction();
    SetUserAction(steppingAction);

    RunAction* runAction = new RunAction();
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
}