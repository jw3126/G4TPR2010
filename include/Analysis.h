//
// Created by jan on 11.04.17.
//

#ifndef G4TPR2010_ANALYSIS_H
#define G4TPR2010_ANALYSIS_H

#include "G4Types.hh"

class Analysis {
public:
    Analysis(){};
    ~Analysis();
    void Initialize();
    void Finish();
    void Write();
    void Record(G4double, G4double);
};


#endif //G4TPR2010_ANALYSIS_H
