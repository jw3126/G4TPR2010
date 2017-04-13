//
// Created by jan on 11.04.17.
//

#ifndef G4TPR2010_RUNCONEXT_H
#define G4TPR2010_RUNCONEXT_H


#include "Analysis.h"
#include "RunParameters.h"

class RunContext {

public:

    RunContext(Analysis& analysis, RunParameters& param, G4GDMLParser& parser):
    fAnalysis(analysis),
    fRunParameters(param),
    fParser(parser)
    {}

    Analysis& GetAnalysis() {return fAnalysis;}
    RunParameters& GetRunParameters() {return fRunParameters;}
    G4GDMLParser& GetParser() {return fParser;}



private:
    Analysis& fAnalysis;
    RunParameters& fRunParameters;
    G4GDMLParser& fParser;

};


#endif //G4TPR2010_RUNCONEXT_H
