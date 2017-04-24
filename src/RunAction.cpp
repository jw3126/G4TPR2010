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
//    G4VPhysicalVolume* physicalWorld = fRunContext.GetParser().GetWorldVolume();
//    fScoring.RegisterScorer(physicalWorld->GetLogicalVolume(), "edepWorld");

    auto& fParser = fRunContext.GetParser();
    const G4GDMLAuxMapType* auxmap = fParser.GetAuxMap();
    G4cout << "Found " << auxmap->size()
           << " volume(s) with auxiliary information."
           << G4endl << G4endl;
    for(G4GDMLAuxMapType::const_iterator iter=auxmap->begin(); iter!=auxmap->end(); iter++)
    {
        G4LogicalVolume* vol = ((*iter).first);
        for (G4GDMLAuxListType::const_iterator vit=(*iter).second.begin();
             vit!=(*iter).second.end(); vit++)
        {
            std::string type = (*vit).type;
            std::string value = (*vit).value;
            if (type == "eDep") {
                fScoring.RegisterScorer(vol, value);
            } else {
                G4cout << "auxtype = " << type << " not supported." << G4endl;
            }
        }
    }
}

RunAction::~RunAction(){
}


void RunAction::BeginOfRunAction(const G4Run* ){
    fScoring.Reset();
    fStartTime = std::chrono::steady_clock::now();

    if (IsMaster()) {
        G4double energy = fRunContext.GetRunParameters().primaryEnergy;
        G4cout << energy / MeV << "MeV" << G4endl;
    }
}



void RunAction::EndOfRunAction(const G4Run* run){
    fScoring.Merge();
    if (IsMaster()) {
        EndOfRunActionMasterExtra(run);
    }

}

void RunAction::EndOfRunActionMasterExtra(const G4Run *) {
    G4double E = fRunContext.GetRunParameters().primaryEnergy;

    // sanity check
//    assert(fScoring.GetNumberOfEvents() == fRunContext.GetRunParameters().nEvent);

    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<int64_t, std::micro> t;
    t = std::chrono::duration_cast<std::chrono::microseconds>(endTime - fStartTime);

    auto& analysis = fRunContext.GetAnalysis();
    auto& names = fScoring.GetWatchedScorerNames();
    for(auto i=names.begin(); i!=names.end(); ++i) {
        std::string name = *i;
        G4double eDep = fScoring.GetRunScore(name);
        G4double eDep2 = fScoring.GetRunScore2(name);

        analysis.Record(E, name, eDep, eDep2, t, fRunContext);
    }
    G4cout
            << G4endl
            << "--------------------End of Global Run-----------------------"
            << G4endl
            ;
}
