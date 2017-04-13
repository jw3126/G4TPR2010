#ifndef G4TPR2010_RUNACTION_H
#define G4TPR2010_RUNACTION_H


#include <G4UserRunAction.hh>
#include <G4ios.hh>
#include <G4Accumulable.hh>
#include "PrimaryGeneratorAction.h"
#include "RunParameters.h"
#include "RunConext.h"
#include "Scoring.h"

class RunAction : public G4UserRunAction{

public:
    RunAction(RunContext&, Scoring);
    ~RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    inline void AddEventScore(G4LogicalVolume* vol, G4double dose) {fScoring.AddEventScore(vol, dose);}
    void FlushEventScore() {fScoring.FlushEventScores();}
private:
    void EndOfRunActionMasterExtra(const G4Run *);
    RunContext& fRunContext;
    Scoring fScoring; // the RunAction should own Scoring
};


#endif //G4TPR2010_RUNACTION_H
