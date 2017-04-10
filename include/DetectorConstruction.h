#ifndef G4TPR2010_DETECTORCONSTRUCTION_H
#define G4TPR2010_DETECTORCONSTRUCTION_H


#include <G4VUserDetectorConstruction.hh>

class DetectorConstruction: public G4VUserDetectorConstruction {

public:
    DetectorConstruction(G4VPhysicalVolume* physicalWorld): G4VUserDetectorConstruction(),
    fScoringVoxel(nullptr),
    fPhysicalWorld(physicalWorld) {
        fScoringVoxel = physicalWorld->GetLogicalVolume();
        physicalWorld->GetLogicalVolume();
    };

    ~DetectorConstruction(){
//        delete fScoringVoxel;
//        delete fLogicalVoxel20;
    };

    virtual void ConstructSDandField();

    virtual G4VPhysicalVolume* Construct();
private:
    G4LogicalVolume* fScoringVoxel;
    G4VPhysicalVolume* fPhysicalWorld;

};


#endif //G4TPR2010_DETECTORCONSTRUCTION_H
