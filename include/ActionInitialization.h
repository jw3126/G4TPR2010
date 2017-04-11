#ifndef G4TPR2010_ACTIONINITIALIZATION_H
#define G4TPR2010_ACTIONINITIALIZATION_H

#include <G4VUserActionInitialization.hh>
#include "PrimaryGeneratorAction.h"
#include "EventAction.h"
#include "SteppingAction.h"
#include "RunParameters.h"

class ActionInitialization: public G4VUserActionInitialization {

public:
    ActionInitialization(RunContext& runContext):fRunContext(runContext){};
    virtual ~ActionInitialization();
    virtual void BuildForMaster() const;
    virtual void Build() const;
private:
    RunContext& fRunContext;
};


#endif //G4TPR2010_ACTIONINITIALIZATION_H
