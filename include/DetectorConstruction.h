#ifndef G4TPR2010_DETECTORCONSTRUCTION_H
#define G4TPR2010_DETECTORCONSTRUCTION_H


#include <G4VUserDetectorConstruction.hh>

class DetectorConstruction: public G4VUserDetectorConstruction {

public:
    DetectorConstruction(): G4VUserDetectorConstruction(),
    fLogicalVoxel10(nullptr),
    fLogicalVoxel20(nullptr)
    {};

    ~DetectorConstruction(){
//        delete fLogicalVoxel10;
//        delete fLogicalVoxel20;
    };

    virtual G4VPhysicalVolume* Construct();
private:
    G4LogicalVolume* fLogicalVoxel10;
    G4LogicalVolume* fLogicalVoxel20;

};


#endif //G4TPR2010_DETECTORCONSTRUCTION_H
