#ifndef G4TPR2010_EVENTACTION_H
#define G4TPR2010_EVENTACTION_H


#include <G4UserEventAction.hh>
#include "RunAction.h"

class EventAction : public G4UserEventAction{

public:
    EventAction(RunAction *fRunAction);
    ~EventAction();
    virtual void BeginOfEventAction(const G4Event* );
    virtual void EndOfEventAction(const G4Event* );
private:
    RunAction* fRunAction;
};


#endif //G4TPR2010_EVENTACTION_H
