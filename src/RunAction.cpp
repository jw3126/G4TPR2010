#include <G4ios.hh>
#include <G4AccumulableManager.hh>
#include "RunAction.h"
#include "G4SystemOfUnits.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction(RunParameters& runParameters) :
        fDose("Dose10", 0),
        fRunParameters(runParameters)
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
        EndOfRunActionMasterFinal(run);
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

void RunAction::EndOfRunActionMasterFinal(const G4Run *) {
    G4double dose10 = fDose.GetValue();
    auto analysisManager = G4CsvAnalysisManager::Instance();

    G4double energy = fRunParameters.primaryEnergy;

    analysisManager->FillNtupleDColumn(0, energy/MeV);
    analysisManager->FillNtupleDColumn(1, dose10/gray);
    analysisManager->AddNtupleRow();
    analysisManager->Write();

}
