#include "PrimaryGeneratorAction.h"

PrimaryGeneratorAction::PrimaryGeneratorAction() : G4VUserPrimaryGeneratorAction(){
    G4int n_particle = 1;
    fParticleGun = new G4ParticleGun(n_particle);

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* gamma = particleTable -> FindParticle("gamma");

    G4ParticleMomentum momentumDirection = G4ParticleMomentum(0,0,-1);
    G4ThreeVector position = G4ThreeVector(0, 0, 1*m);

    fParticleGun->SetParticleDefinition(gamma);
    fParticleGun->SetParticleEnergy(7*MeV);
    fParticleGun->SetParticleMomentumDirection(momentumDirection);
    fParticleGun->SetParticlePosition(position);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {delete fParticleGun;}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent) {
    fParticleGun->GeneratePrimaryVertex(anEvent);
}