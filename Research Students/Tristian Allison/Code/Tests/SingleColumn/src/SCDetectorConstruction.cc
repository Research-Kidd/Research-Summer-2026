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
    nist = G4NistManager::Instance();

}

SCDetectorConstruction::~SCDetectorConstruction()
{

}

void SCDetectorConstruction::ConstructScintillator()
{
    // TODO: fix these with correct energy emission spectrum when found
    G4double energy[3] = {1.239841939*eV/0.9, 1.239841939*eV/0.55, 1.239841939*eV/0.2};
    G4double rindexCsI[3] = {1.7481, 1.7481, 1.7481};
    G4double fraction[3] = {.3, 1.0, 0.2};
    
    // Material
    G4Material *columnMat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

    // Material property table for CsI scintillator
    G4MaterialPropertiesTable *mptColumn = new G4MaterialPropertiesTable();
    mptColumn->AddProperty("RINDEX", energy, rindexCsI, 3);
    mptColumn->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction, 3, true);
    mptColumn->AddConstProperty("SCINTILLATIONYIELD", 52.0/keV);
    mptColumn->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptColumn->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1080. * ns);
    mptColumn->AddConstProperty("SCINTILLATIONYIELD1", 1.);
    columnMat->SetMaterialPropertiesTable(mptColumn);

    // Column Scintillator
    G4double columnRadius = 5. * micrometer;
    G4double columnHeight = 45. * micrometer;

    solidColumn = new G4Tubs("solidColumn", 0., columnRadius, 0.5 * columnHeight, 0.0, 360. * deg);
    logicColumn = new G4LogicalVolume(solidColumn, columnMat, "logicColumn");
    physColumn = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), logicColumn, "physColumn", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *columnVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 0.5));
    columnVisAtt->SetForceSolid(true);
    logicColumn->SetVisAttributes(columnVisAtt);
}

G4VPhysicalVolume *SCDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true; // make sure volumes do not overlap

    // Manipulate materials of the volume
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    // Material property table for world
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    G4double worldRindex[2] = {1.0, 1.0};
    G4double worldEnergy[2] = {1.0*eV, 6.0*eV};
    mptWorld->AddProperty("RINDEX", worldEnergy, worldRindex, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    // world
    G4double xWorld = 1. * mm;
    G4double yWorld = 1. * mm;
    G4double zWorld = 1. * mm;

    solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    ConstructScintillator();

    return physWorld;

} 

void SCDetectorConstruction::ConstructSDandField()
{
    //SCSensitiveDetector *sensDet = new SCSensitiveDetector("SensitiveDetector");
    //logicDetector->SetSensitiveDetector(sensDet);
    //G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);

}