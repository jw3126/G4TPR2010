#ifndef G4TPR2010_PRIMARYGENERATORACTION_H
#define G4TPR2010_PRIMARYGENERATORACTION_H


#include <G4ParticleTable.hh>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction {

public:
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event* );

private:
    G4ParticleGun* fParticleGun;
};


#endif //G4TPR2010_PRIMARYGENERATORACTION_H
