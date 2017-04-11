#ifndef G4TPR2010_RUNACTION_H
#define G4TPR2010_RUNACTION_H


#include <G4UserRunAction.hh>
#include <G4ios.hh>
#include <G4Accumulable.hh>
#include "PrimaryGeneratorAction.h"
#include "RunParameters.h"

class RunAction : public G4UserRunAction{

public:
    RunAction(RunParameters& runParameters);
    ~RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void UpdateDose(G4double dose);
private:
    G4Accumulable<G4double> fDose;
    void EndOfRunActionMasterFinal(const G4Run* );
    RunParameters& fRunParameters;
};


#endif //G4TPR2010_RUNACTION_H
