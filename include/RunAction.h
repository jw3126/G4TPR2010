#ifndef G4TPR2010_RUNACTION_H
#define G4TPR2010_RUNACTION_H


#include <G4UserRunAction.hh>
#include <G4ios.hh>
#include <G4Accumulable.hh>

class RunAction : public G4UserRunAction{

public:
    RunAction();
    ~RunAction();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void UpdateDose10(G4double dose);
    void UpdateDose20(G4double dose);
private:
    G4Accumulable<G4double> fDose10;
    G4Accumulable<G4double> fDose20;


};


#endif //G4TPR2010_RUNACTION_H
