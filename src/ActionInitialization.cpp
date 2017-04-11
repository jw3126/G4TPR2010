#include "ActionInitialization.h"

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    RunAction* runAction = new RunAction(fRunContext);
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
//    RunParameters& runParameters = fRunContext.GetRunParameters();

    PrimaryGeneratorAction* primaryGeneratorAction = new PrimaryGeneratorAction(fRunContext);
    SetUserAction(primaryGeneratorAction);

    SteppingAction* steppingAction = new SteppingAction();
    SetUserAction(steppingAction);

    RunAction* runAction = new RunAction(fRunContext);
    SetUserAction(runAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
}