#ifndef G4TPR2010_ACTIONINITIALIZATION_H
#define G4TPR2010_ACTIONINITIALIZATION_H

#include <G4VUserActionInitialization.hh>
#include "PrimaryGeneratorAction.h"
#include "EventAction.h"
#include "SteppingAction.h"

class ActionInitialization: public G4VUserActionInitialization {

public:
    ActionInitialization() ;
    virtual ~ActionInitialization();
    virtual void Build() const;
};


#endif //G4TPR2010_ACTIONINITIALIZATION_H
