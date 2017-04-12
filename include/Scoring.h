//#ifndef G4TPR2010_SCORING_H
//#define G4TPR2010_SCORING_H
//
//
//
//#include <G4LogicalVolume.hh>
//#include <G4Accumulable.hh>
//#include "RunConext.h"
//#include "util.h"
//
//
//class Scoring {
//
//public:
//    inline std::vector<G4LogicalVolume*>& GetWatchedLogicalVolumes() {return fWatchedLogicalVolumes;}
//    inline std::vector<std::string>& GetWatchedScorerNames() {return fWatchedScorerNames;}
//    inline G4bool IsWatched(G4LogicalVolume* vol) {return HasElement(GetWatchedLogicalVolumes(), vol); }
//
//    void RegisterScorer(G4LogicalVolume*, std::string name);
//
//    void Score(G4LogicalVolume* volume, G4double dose);
//
//    //Scoring(RunContext&);
//    ~Scoring(){};
//
//private:
//    // TODO
//    //void Merge(); // merge accumulables
//
//    void ResetEventScores(); // this should be done automatically, when UpdateRunScorers is called
//    void ResetEventScore(std::string name);
//
//    void ResetAccumulables();
//    void ResetAccumulable(std::string name);
//
//    std::vector<std::string>& GetNames(G4LogicalVolume* vol);
//    inline G4double& GetEventScore(std::string name) { return fEventScoreByName[name]; }
//    G4Accumulable<G4double>& GetAccumulable(std::string name) { return fAccumulableByName[name];}
//
//
//
//
//private:
//    // containers accumulating information over a single event:
//    std::vector<G4LogicalVolume*> fWatchedLogicalVolumes;
//    std::vector<std::string> fWatchedScorerNames;
//    std::map<std::string, G4double> fEventScoreByName;
//
//    // general bookkeeping
//    std::map<G4LogicalVolume*, std::vector<std::string>> fNamesByLogicalVolume;
//
//    // facilities for accumulating information over whole run
//    std::map<std::string, G4Accumulable<G4double>> fAccumulableByName;
//    // map<string, G4Accumulable<G4double>> fAccumulable2ByName; // for storing the second momentum
//
//};
//
//
//#endif //G4TPR2010_SCORING_H
