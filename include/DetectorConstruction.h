#ifndef G4TPR2010_DETECTORCONSTRUCTION_H
#define G4TPR2010_DETECTORCONSTRUCTION_H


#include <G4VUserDetectorConstruction.hh>
#include <G4GDMLParser.hh>
#include "RunParameters.h"
#include <G4GDMLParser.hh>

class DetectorConstruction: public G4VUserDetectorConstruction {

public:
    DetectorConstruction(RunParameters& runParameters):
            G4VUserDetectorConstruction(),
            fRunParameters(runParameters)
    {};

    ~DetectorConstruction(){
        // what do I need to delete?
        // fParser is a ref, so I do not delete it?
    };

    virtual void ConstructSDandField();

    virtual G4VPhysicalVolume* Construct();
private:
    RunParameters fRunParameters;
};


#endif //G4TPR2010_DETECTORCONSTRUCTION_H
