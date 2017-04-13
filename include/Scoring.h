#ifndef G4TPR2010_SCORING_H
#define G4TPR2010_SCORING_H



#include <G4LogicalVolume.hh>
#include <G4Accumulable.hh>
#include "RunConext.h"
#include "util.h"
#include <G4AccumulableManager.hh>

class Scoring {

public:
    inline std::vector<G4LogicalVolume*>& GetWatchedLogicalVolumes() {return fWatchedLogicalVolumes;}
    inline std::vector<std::string>& GetWatchedScorerNames() {return fWatchedScorerNames;}
    inline G4bool IsWatched(G4LogicalVolume* vol) {return HasElement(GetWatchedLogicalVolumes(), vol); }

    void RegisterScorer(G4LogicalVolume*, std::string name);

    void AddEventScore(G4LogicalVolume *volume, G4double edep);
    inline G4double& GetEventScore(std::string name) { return fEventScoreByName[name]; }

    G4double GetRunScore(std::string name); // should this flush automatically?
    Scoring();
    ~Scoring(){};
    void FlushEventScores();
    void ResetAccumulables();
    void ResetEventScores(); // this should be done automatically, when UpdateRunScorers is called
    void Reset(){ResetEventScores(); ResetAccumulables();}
    void Merge();

private:
    // TODO
    //void Merge(); // merge accumulables

    void ResetEventScore(std::string name);

    void ResetAccumulable(std::string name);

    std::vector<std::string>& GetNames(G4LogicalVolume* vol);

    // accumulates are owned by the AccumulateManager, we can only pass pointers and not refs
    G4Accumulable<G4double>* GetAccumulable(std::string name) { return fAccumulableByName[name]; }



private:

    // general bookkeeping
    std::map<G4LogicalVolume*, std::vector<std::string>> fNamesByLogicalVolume;
    std::vector<G4LogicalVolume*> fWatchedLogicalVolumes;
    std::vector<std::string> fWatchedScorerNames;

    // containers accumulating information over a single event:
    std::map<std::string, G4double> fEventScoreByName;



    // facilities for accumulating information over whole run
    std::map<std::string, G4Accumulable<G4double>*> fAccumulableByName;

};


#endif //G4TPR2010_SCORING_H
