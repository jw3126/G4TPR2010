////
//// Created by jan on 12.04.17.
////
//
//#include <assert.h>
//#include "Scoring.h"
//#include "util.h"
//
//
//
//void Scoring::ResetAccumulable(std::string name) {
//    GetAccumulable(name) = 0;
//}
//
//void Scoring::ResetAccumulables() {
//    for (auto i = fWatchedScorerNames.begin(); i != fWatchedScorerNames.end(); ++i) {
//        ResetAccumulable(*i);
//    }
//}
//
//void Scoring::ResetEventScores() {
//    //vector<string>::const_iterator i;
//    for (auto i = fWatchedScorerNames.begin(); i != fWatchedScorerNames.end(); ++i) {
//        ResetEventScore(*i);
//    }
//}
//
//void Scoring::ResetEventScore(string name) {
//    GetEventScore(name) = 0;
//}
//
//
//
//vector<string>& Scoring::GetNames(G4LogicalVolume* vol) {
//    if (!HasKey(fNamesByLogicalVolume, vol)) {
//        auto v = vector<string>();
//        fNamesByLogicalVolume[vol] = v;
//    }
//    return fNamesByLogicalVolume[vol];
//}
//
//void Scoring::RegisterScorer(G4LogicalVolume* vol, string name) {
//    vector<string>& names = GetNames(vol);
//    assert( !HasElement(names, name) );
//    names.push_back(name);
//
//    vector<string>& snames = GetWatchedScorerNames();
//    // a scorer may have multiple sensitive volumes. Thats why we need this check
//    if ( !HasElement(snames, name) ) {
//        snames.push_back(name);
//        GetEventScore(name) = 0.;
//    };
//
//    assert( GetEventScore(name) = 0. );
//
//}
//
//void Scoring::Score(G4LogicalVolume *vol, G4double dose) {
//    if ( IsWatched(vol) ) {
//        vector<string>& names = GetNames(vol);
//        for(auto i=names.begin(); i!=names.end(); ++i) {
//            GetEventScore(*i) += dose;
//        }
//    }
//}
