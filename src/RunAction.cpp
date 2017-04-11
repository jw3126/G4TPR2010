#include <G4ios.hh>
#include <G4AccumulableManager.hh>
#include "RunAction.h"
#include "G4SystemOfUnits.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction(RunContext& ctx) :
        fDose("Dose10", 0),
        fRunContext(ctx)
{
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fDose);
}

RunAction::~RunAction(){
}

void RunAction::UpdateDose(G4double dose){
    fDose += dose;
}

void RunAction::BeginOfRunAction(const G4Run* ){
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Reset();
}



void RunAction::EndOfRunAction(const G4Run* run){

    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();

    G4double dose10 = fDose.GetValue();
    if (IsMaster()) {
        EndOfRunActionMasterExtra(run);
        G4cout
                << G4endl
                << "--------------------End of Global Run-----------------------"
                << G4endl
                ;
    }
    else {
        G4cout
                << G4endl
                << "--------------------End of Local Run------------------------"
                << G4endl
                ;
    }
    G4cout << "dose10:" << dose10 << G4endl;
}

void RunAction::EndOfRunActionMasterExtra(const G4Run *) {
    G4double dose10 = fDose.GetValue();
    G4double energy = fRunContext.GetRunParameters().primaryEnergy;
    fRunContext.GetAnalysis().Record(energy, dose10);
    G4cout << fRunContext.GetRunParameters().primaryEnergy << G4endl;
}
