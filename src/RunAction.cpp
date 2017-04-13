#include <G4ios.hh>
#include <G4AccumulableManager.hh>
#include <G4GDMLParser.hh>
#include "RunAction.h"
#include "G4SystemOfUnits.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4Run.hh"

RunAction::RunAction(RunContext& ctx, Scoring scoring) :
        fRunContext(ctx),
        fScoring(scoring)
{

    G4VPhysicalVolume* physicalWorld = fRunContext.GetParser().GetWorldVolume();

    fScoring.RegisterScorer(physicalWorld->GetLogicalVolume(), "edepWorld");


}

RunAction::~RunAction(){
}


void RunAction::BeginOfRunAction(const G4Run* ){
    fScoring.Reset();

    if (IsMaster()) {
        G4double energy = fRunContext.GetRunParameters().primaryEnergy;
        G4cout << energy / MeV << "MeV" << G4endl;
    }
}



void RunAction::EndOfRunAction(const G4Run* run){


    G4cout << fScoring.GetRunScore("edepWorld") << G4endl;
    fScoring.Merge();
    G4cout << fScoring.GetRunScore("edepWorld") << G4endl;

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
}

void RunAction::EndOfRunActionMasterExtra(const G4Run *) {

}
