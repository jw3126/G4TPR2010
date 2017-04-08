#include <G4Tubs.hh>
#include "G4Box.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "DetectorConstruction.h"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {

    // world
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* mediumWorld = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* H2O = nist->FindOrBuildMaterial("G4_WATER");

    // logical
    G4Box* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 1.5*m);
    G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, mediumWorld, "logicalWorld");

    // physical
    G4RotationMatrix* pRot = nullptr;
    const G4ThreeVector& tlate = G4ThreeVector();
    G4LogicalVolume* pCurrentLogical = logicalWorld;
    const G4String& pName = "physicalWorld";
    G4LogicalVolume* pMotherLogical = nullptr; // the world has no mother volume
    G4bool pMany = false; // boolean solid?
    G4int pCopyNo = 0;  // multiple copies of volume in physical world?
    const G4bool pSurfChk = true;  // check overlaps?

    G4VPhysicalVolume* physicalWorld =
            new G4PVPlacement(pRot,
                              tlate,
                              pCurrentLogical,
                              pName,
                              pMotherLogical,
                              pMany,
                              pCopyNo,
                              pSurfChk);

    G4double hlz_Tank = 17.5*cm;

    G4Box* solidTank = new G4Box("solidTank", 10*cm, 10*cm, hlz_Tank);
    G4LogicalVolume* logicalTank = new G4LogicalVolume(solidTank, H2O, "logicalTank");
    new G4PVPlacement(
            pRot,
            tlate,
            logicalTank,
            "physicalTank",
            logicalWorld,
            pMany,
            pCopyNo,
            pSurfChk
    );

    // voxels
    G4double pRMin = 0;
    G4double pRMax = 1*cm;
    G4double pDz = 1*cm;
    G4double pSPhi = 0; // starting angle
    G4double pDPhi = 2*pi;

    G4Tubs* solidVoxel10 = new G4Tubs("solidVoxel10",
    pRMin,
    pRMax,
    pDz,
    pSPhi,
    pDPhi);

    auto tlate_Voxel10 = G4ThreeVector(0,0, hlz_Tank - 10*cm);
    fLogicalVoxel10 = new G4LogicalVolume(solidVoxel10, H2O, "fLogicalVoxel10");
    new G4PVPlacement(
        pRot,
        tlate_Voxel10,
        fLogicalVoxel10,
        "physicalVoxel10",
        logicalTank,
        pMany,
        pCopyNo,
        pSurfChk
    );

    G4Tubs* solidVoxel20 = new G4Tubs("solidVoxel20",
                                      pRMin,
                                      pRMax,
                                      pDz,
                                      pSPhi,
                                      pDPhi);

    auto tlate_Voxel20 = G4ThreeVector(0,0, hlz_Tank - 20*cm);
    fLogicalVoxel20 = new G4LogicalVolume(solidVoxel20, H2O, "fLogicalVoxel20");
    new G4PVPlacement(
            pRot,
            tlate_Voxel20,
            fLogicalVoxel20,
            "physicalVoxel20",
            logicalTank,
            pMany,
            pCopyNo,
            pSurfChk
    );




    return physicalWorld;
}