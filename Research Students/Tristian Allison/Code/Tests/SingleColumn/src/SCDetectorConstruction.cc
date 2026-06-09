/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#include "SCDetectorConstruction.hh"

SCDetectorConstruction::SCDetectorConstruction()
{

}

SCDetectorConstruction::~SCDetectorConstruction()
{

}

G4VPhysicalVolume *SCDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true; // make sure volumes do not overlap

    // Manipulate materials of the volume
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *columnMat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

    // world
    G4double xWorld = 1. * mm;
    G4double yWorld = 1. * mm;
    G4double zWorld = 1. * mm;

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    // Column Scintillator
    G4double columnRadius = 5. * micrometer;
    G4double columnHeight = 45. * micrometer;

    G4Tubs *solidColumn = new G4Tubs("solidColumn", 0., columnRadius, 0.5 * columnHeight, 0.0, 360. * deg);
    G4LogicalVolume *logicColumn = new G4LogicalVolume(solidColumn, columnMat, "logicColumn");
    G4VPhysicalVolume *physColumn = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), logicColumn, "physColumn", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *columnVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 0.5));
    columnVisAtt->SetForceSolid(true);
    logicColumn->SetVisAttributes(columnVisAtt);
    

    return physWorld;

} 

void SCDetectorConstruction::ConstructSDandField()
{
    //SCSensitiveDetector *sensDet = new SCSensitiveDetector("SensitiveDetector");
    //logicDetector->SetSensitiveDetector(sensDet);
    //G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);

}