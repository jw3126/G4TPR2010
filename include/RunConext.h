//
// Created by jan on 11.04.17.
//

#ifndef G4TPR2010_RUNCONEXT_H
#define G4TPR2010_RUNCONEXT_H


#include "Analysis.h"
#include "RunParameters.h"

class RunContext {

public:

    RunContext(Analysis& analysis, RunParameters& param):
    fAnalysis(analysis),
    fRunParameters(param)
    {}

    Analysis& GetAnalysis() {return fAnalysis;}
    RunParameters& GetRunParameters() {return fRunParameters;}

private:
    Analysis& fAnalysis;
    RunParameters& fRunParameters;
};


#endif //G4TPR2010_RUNCONEXT_H
