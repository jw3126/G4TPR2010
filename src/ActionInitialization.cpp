#include "ActionInitialization.h"

ActionInitialization::ActionInitialization() : G4VUserActionInitialization(){}
ActionInitialization::~ActionInitialization() {}

void ActionInitialization::Build() const
{

    PrimaryGeneratorAction* primaryGeneratorAction = new PrimaryGeneratorAction();
    SetUserAction(primaryGeneratorAction);

    EventAction* eventAction = new EventAction();
    SetUserAction(eventAction);

    SteppingAction* steppingAction = new SteppingAction();
    SetUserAction(steppingAction);

    RunAction* runAction = new RunAction();
    SetUserAction(runAction);

}