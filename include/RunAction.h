#ifndef G4TPR2010_RUNACTION_H
#define G4TPR2010_RUNACTION_H


#include <G4UserRunAction.hh>
#include <G4ios.hh>
#include <G4Accumulable.hh>
#include "PrimaryGeneratorAction.h"
#include "RunParameters.h"
#include "RunConext.h"

class RunAction : public G4UserRunAction{

public:
    RunAction(RunContext& runContext);
    ~RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void UpdateDose(G4double dose);
private:
    G4Accumulable<G4double> fDose;
    void EndOfRunActionMasterExtra(const G4Run *);
    RunContext& fRunContext;
};


#endif //G4TPR2010_RUNACTION_H
