#include <G4Tubs.hh>
#include <G4SDManager.hh>
#include <G4MultiFunctionalDetector.hh>
#include <G4PSDoseDeposit.hh>
#include "DetectorConstruction.h"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {

    G4VPhysicalVolume* physicalWorld = fParser.GetWorldVolume();
    G4bool hasOverlaps = physicalWorld->CheckOverlaps();

    if (hasOverlaps) {
            G4cout << "Geometry has Overlaps!" << G4endl;
            return nullptr;
        }

    return physicalWorld;

}

void DetectorConstruction::ConstructSDandField() {
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();

    G4MultiFunctionalDetector *detector = new G4MultiFunctionalDetector("detector");
    G4VPrimitiveScorer* psDose = new G4PSDoseDeposit("dose");
    detector->RegisterPrimitive(psDose);
    SetSensitiveDetector("ScoringVoxel", detector);
    sdManager->AddNewDetector(detector);

}
