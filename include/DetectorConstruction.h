#ifndef G4TPR2010_DETECTORCONSTRUCTION_H
#define G4TPR2010_DETECTORCONSTRUCTION_H


#include <G4VUserDetectorConstruction.hh>
#include <G4GDMLParser.hh>

class DetectorConstruction: public G4VUserDetectorConstruction {

public:
    DetectorConstruction(const G4GDMLParser& parser):G4VUserDetectorConstruction(),
    fParser(parser)
    {
    };

    ~DetectorConstruction(){
        // what do I need to delete?
        // fParser is a ref, so I do not delete it?
    };

    virtual void ConstructSDandField();

    virtual G4VPhysicalVolume* Construct();
private:
    const G4GDMLParser& fParser;
};


#endif //G4TPR2010_DETECTORCONSTRUCTION_H
