
#include <assert.h>
#include "Scoring.h"
#include "util.h"

Scoring::Scoring():
        fNumberOfEvents(nullptr)
{
    fNumberOfEvents = new G4Accumulable<G4int>(0);
    G4AccumulableManager* am = G4AccumulableManager::Instance();
    am->RegisterAccumulable(fNumberOfEvents);
}

void Scoring::ResetAccumulable(std::string name) {
    *GetAccumulable(name) = 0;
}
void Scoring::ResetAccumulable2(std::string name) {
    *GetAccumulable2(name) = 0;
}

void Scoring::ResetRun() {
    for (auto i = fWatchedScorerNames.begin(); i != fWatchedScorerNames.end(); ++i) {
        ResetAccumulable(*i);
        ResetAccumulable2(*i);
    }
    *fNumberOfEvents = 0;
}

void Scoring::ResetEventScores() {
    //vector<string>::const_iterator i;
    for (auto i = fWatchedScorerNames.begin(); i != fWatchedScorerNames.end(); ++i) {
        ResetEventScore(*i);
    }
}

void Scoring::ResetEventScore(string name) {
    GetEventScore(name) = 0;
}



vector<string>& Scoring::GetNames(G4LogicalVolume* vol) {
    if (!HasKey(fNamesByLogicalVolume, vol)) {
        auto v = vector<string>();
        fNamesByLogicalVolume[vol] = v;
    }
    return fNamesByLogicalVolume[vol];
}

void Scoring::RegisterScorer(G4LogicalVolume* vol, string name) {
    vector<string>& names = GetNames(vol);
    assert( !HasElement(names, name) );
    names.push_back(name);

    vector<string>& snames = GetWatchedScorerNames();
    // a scorer may have multiple sensitive volumes. Thats why we need this check
    if ( !HasElement(snames, name) ) {

        snames.push_back(name);
        GetEventScore(name) = 0.;

        G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
        G4Accumulable<double>* acc = new G4Accumulable<double>(0);
        accumulableManager->RegisterAccumulable(acc);
        fAccumulableByName[name] = acc;

        G4Accumulable<double>* acc2 = new G4Accumulable<double>(0);
        accumulableManager->RegisterAccumulable(acc2);
        fAccumulable2ByName[name] = acc2;
    };

    if (!HasElement(fWatchedLogicalVolumes, vol))
    {
        fWatchedLogicalVolumes.push_back(vol);
    }

    assert( GetEventScore(name) == 0. );

}

void Scoring::AddEventScore(G4LogicalVolume *vol, G4double edep) {
    if (edep > 0) {
        if (IsWatched(vol))  {
            vector<string> &names = GetNames(vol);
            for (auto name = names.begin(); name != names.end(); ++name) {
                GetEventScore(*name) += edep;
            }
        }
    }
}

G4double Scoring::GetRunScore(std::string name) {
    return GetAccumulable(name) -> GetValue();
}
G4double Scoring::GetRunScore2(std::string name) {
    return GetAccumulable2(name) -> GetValue();
}

void Scoring::FinishEvent() {
    *fNumberOfEvents += 1;
    for (auto name = fWatchedScorerNames.begin(); name != fWatchedScorerNames.end(); ++name) {
        G4double edep = GetEventScore(*name);
        ResetEventScore(*name);

        auto acc = GetAccumulable(*name);
        *acc += edep;
        auto acc2 = GetAccumulable2(*name);
        *acc2 += edep*edep;
    }
}

void Scoring::Merge() {
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->Merge();
}
