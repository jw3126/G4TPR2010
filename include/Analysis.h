//
// Created by jan on 11.04.17.
//

#ifndef G4TPR2010_ANALYSIS_H
#define G4TPR2010_ANALYSIS_H

#include <chrono>
#include "G4Types.hh"
#include "RunContext.h"

class RunContext;

class Analysis {
public:
    Analysis(){};
    ~Analysis();
    void Initialize();
    void Finish();
    void Record(G4double primaryEnergy,
                std::string detectorName,
                G4double eDep,
                G4double eDep2,
                std::chrono::duration<int64_t, std::micro> t,
                RunContext& ctx
    );
private:
    G4double Std(G4double, G4double , G4int);
    G4double Mean(G4double eDep, G4int nEvents);
};


#endif //G4TPR2010_ANALYSIS_H
