#ifndef G4TPR2010_PRIMARYGENERATORACTION_H
#define G4TPR2010_PRIMARYGENERATORACTION_H


#include <G4ParticleTable.hh>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "RunParameters.h"
#include "RunContext.h"

// A Rectangle for defining field shapes
struct Rectangle {
    G4double x_min;
    G4double x_max;
    G4double y_min;
    G4double y_max;
    Rectangle():
            x_min(-5*cm),
            x_max(5*cm),
            y_min(-5*cm),
            y_max(5*cm)
    {}
};


class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction {

public:
    PrimaryGeneratorAction(RunContext& ctx);
    ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event* );
    void setZSource(G4double fZSource);

private:
    G4double fZSource;
    RunContext& fRunContext;
    G4ParticleGun* fParticleGun;
    Rectangle fFieldShape;
    G4ThreeVector GenerateMomentum();

};


#endif //G4TPR2010_PRIMARYGENERATORACTION_H
