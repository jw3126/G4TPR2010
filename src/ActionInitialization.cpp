#include "ActionInitialization.h"

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const {
    Scoring scoring = Scoring();
    RunAction* runAction = new RunAction(fRunContext, scoring);
    SetUserAction(runAction);
}

void ActionInitialization::Build() const
{

    PrimaryGeneratorAction* primaryGeneratorAction = new PrimaryGeneratorAction(fRunContext);
    SetUserAction(primaryGeneratorAction);

    Scoring scoring = Scoring();

    RunAction* runAction = new RunAction(fRunContext, scoring);
    SetUserAction(runAction);

    SteppingAction* steppingAction = new SteppingAction(runAction);
    SetUserAction(steppingAction);

    EventAction* eventAction = new EventAction(runAction);
    SetUserAction(eventAction);
}