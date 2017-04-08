#ifndef G4TPR2010_DETECTORCONSTRUCTION_H
#define G4TPR2010_DETECTORCONSTRUCTION_H


#include <G4VUserDetectorConstruction.hh>

class DetectorConstruction: public G4VUserDetectorConstruction {

public:
    DetectorConstruction(): G4VUserDetectorConstruction() {};
    ~DetectorConstruction(){};
    virtual G4VPhysicalVolume* Construct();
};


#endif //G4TPR2010_DETECTORCONSTRUCTION_H
