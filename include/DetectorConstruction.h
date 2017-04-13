#ifndef G4TPR2010_DETECTORCONSTRUCTION_H
#define G4TPR2010_DETECTORCONSTRUCTION_H


#include <G4VUserDetectorConstruction.hh>
#include <G4GDMLParser.hh>
#include "RunParameters.h"
#include "RunContext.h"

class DetectorConstruction: public G4VUserDetectorConstruction {

public:
    DetectorConstruction(RunContext& ctx):
            G4VUserDetectorConstruction(),
            fRunContext(ctx)
    {};

    ~DetectorConstruction(){};

    virtual void ConstructSDandField();

    virtual G4VPhysicalVolume* Construct();
private:
    RunContext& fRunContext;
};


#endif //G4TPR2010_DETECTORCONSTRUCTION_H
