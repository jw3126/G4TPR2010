//
// Created by admin on 4/11/17.
//

#ifndef G4TPR2010_RUNPARAMETERS_H
#define G4TPR2010_RUNPARAMETERS_H


#include <pwdefs.hh>
#include <G4String.hh>

// Encapsulates parameters that are constant over a single run.
struct RunParameters {

    G4double primaryEnergy;
    G4String geometryPath;
    G4int nEvent;

};


#endif //G4TPR2010_RUNPARAMETERS_H
