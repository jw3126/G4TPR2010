#include <Randomize.hh>
#include <assert.h>
#include <RunParameters.h>
#include "PrimaryGeneratorAction.h"

PrimaryGeneratorAction::PrimaryGeneratorAction(RunParameters& runParameters) :
        G4VUserPrimaryGeneratorAction(),
        fRunParameters(runParameters),
        fFieldShape(Rectangle())
{
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);
    setZSource(1*m);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* gamma = particleTable -> FindParticle("gamma");

    fParticleGun->SetParticleDefinition(gamma);
    fParticleGun->SetParticleEnergy(fRunParameters.primaryEnergy);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {delete fParticleGun;}


G4ThreeVector PrimaryGeneratorAction::GenerateMomentum()
{
    G4double x_min = fFieldShape.x_min;
    G4double x_max = fFieldShape.x_max;
    G4double y_min = fFieldShape.y_min;
    G4double y_max = fFieldShape.y_max;

    G4double x_l = x_max - x_min;
    G4double y_l = y_max - y_min;

    G4double x, y, z, r2, p;
    G4bool accept;

    while (true) {
        x = x_min + G4UniformRand() * x_l;
        y = y_min + G4UniformRand() * y_l;

        z = - 1*m;
        r2 = x*x + y*y + z*z;  //square distance to focus

        p = (z*z) / r2;
        assert(0 < p);
        assert(p <= 1);

        accept =  (G4UniformRand() < p);
        if (accept) {
            return G4ThreeVector(x,y,z).unit();
        }
    }
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {

    // TODO there should be a builtin function to generate divergent fields
    G4ParticleMomentum momentumDirection = GenerateMomentum();

    fParticleGun->SetParticleMomentumDirection(momentumDirection);
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

void PrimaryGeneratorAction::setZSource(G4double zSource) {
    fZSource = zSource;
    G4ThreeVector position = G4ThreeVector(0, 0, fZSource);
    fParticleGun->SetParticlePosition(position);
}
