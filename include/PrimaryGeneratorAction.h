#ifndef G4TPR2010_PRIMARYGENERATORACTION_H
#define G4TPR2010_PRIMARYGENERATORACTION_H


#include <G4ParticleTable.hh>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

#include "globals.hh"
#include "G4SystemOfUnits.hh"

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
    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event* );

public:
    const Rectangle &getFieldShape() const;

    void setFieldShape(const Rectangle &fFieldShape);
    G4double getZSource() const;
    void setZSource(G4double fZSource);

private:
    G4double fZSource;
    G4double fEnergy;
public:
    G4double getEnergy() const {
        return fEnergy;
    }

    void setEnergy(G4double energy) {
        fEnergy = energy;
    }

private:
    G4ParticleGun* fParticleGun;

private:
    Rectangle fFieldShape;
    G4ThreeVector GenerateMomentum();

};


#endif //G4TPR2010_PRIMARYGENERATORACTION_H
