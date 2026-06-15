/*
    Title           :   SCDetectorConstruction.cc
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 10, 2026
    Purpose         :
*/
#include "SCDetectorConstruction.hh"

SCDetectorConstruction::SCDetectorConstruction()
{
    checkOverlaps = true; // make sure volumes do not overlap
    
    nist = G4NistManager::Instance();
}

SCDetectorConstruction::~SCDetectorConstruction()
{

}

void SCDetectorConstruction::ConstructScintillator()
{
    // Constants
    const G4int size = 8;
    const G4double λ[size] = {700.*nm, 650.*nm, 600.*nm, 550.*nm, 500.*nm, 450.*nm, 400.*nm, 350.*nm};

    // TODO: fix these with correct energy emission spectrum when found
    G4double energy[size], rindexCsI[size], absCsI[size];
    G4double fraction[size] = {0.15, 0.4, 0.7, 1.0, 0.7, 0.3, 0.1, 0.05};

    G4double sum = 0.;
    for (int i = 0; i < size; i++)
        sum += fraction[i];

    // assign values to arrays
    for (int i = 0; i < size; i++)
    {
        energy[i] = h_Planck*c_light/λ[i];
        rindexCsI[i] = 1.7481;
        absCsI[i] = 30. * cm;
        fraction[i] = fraction[i] / sum; // normalize fraction
    }
    
    // Material
    G4Material *columnMat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

    // Material property table for CsI scintillator
    G4MaterialPropertiesTable *mptColumn = new G4MaterialPropertiesTable();
    mptColumn->AddProperty("RINDEX", energy, rindexCsI, size);
    mptColumn->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction, size, true);
    mptColumn->AddConstProperty("SCINTILLATIONYIELD", 0.01/keV); // fix this for real runs at 52/keV
    mptColumn->AddConstProperty("RESOLUTIONSCALE", 1.);
    mptColumn->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1080. * ns);
    mptColumn->AddConstProperty("SCINTILLATIONYIELD1", 1.);
    mptColumn->AddProperty("ABSLENGTH", energy, absCsI, size);
    columnMat->SetMaterialPropertiesTable(mptColumn);

    // Column Scintillator
    G4double columnRadius = 5. * micrometer;
    G4double columnHeight = 45. * micrometer;

    solidColumn = new G4Tubs("solidColumn", 0., columnRadius, 0.5 * columnHeight, 0.0, 360. * deg);
    logicColumn = new G4LogicalVolume(solidColumn, columnMat, "logicColumn");
    //physColumn = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 0.), logicColumn, "physColumn", logicWorld, false, 0, checkOverlaps);

    ///* for making array of columns
    G4int length = 25, width = 25;
    G4double scintillatorRadius = 0.55 * mm;
    G4double pitch = 10.*um;

    /*
    for (int i = -scintillatorRadius/pitch; i < scintillatorRadius/pitch; i++) 
    {
        G4double x = i * pitch;
        for (int j = -scintillatorRadius/pitch; j < scintillatorRadius/pitch; j++)
        {
            G4double y = j * pitch;

            if (sqrt(pow(x,2.)+pow(y,2.)) <= scintillatorRadius) // if within circle
                new G4PVPlacement(nullptr, G4ThreeVector(x, y, 0.), logicColumn, "physColumn", logicWorld, false, 0, checkOverlaps);    
        }
    }
    */

    for (int i = -width; i < width; i++) 
    {
        G4double x = i * pitch;
        for (int j = -length; j < length; j++)
        {
            G4double y = j * pitch;
            new G4PVPlacement(nullptr, G4ThreeVector(x, y, 0.), logicColumn, "physColumn", logicWorld, false, 0, checkOverlaps);
        }
    }
    //*/

    G4VisAttributes *columnVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 0.5));
    columnVisAtt->SetForceSolid(true);
    logicColumn->SetVisAttributes(columnVisAtt);
}

void SCDetectorConstruction::ConstructDetector()
{
    // ------------------------------------------
    // Same material as the world since this won't hinder photons differently
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    // -------------------------------------------

    G4double xDet = 500. * um;
    G4double yDet = 500. * um;
    G4double zDet = 50. * um;

    solidDetector = new G4Box("solidDetector", 0.5 * xDet, 0.5 * yDet, 0.5 * zDet);
    logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 1.3 * mm), logicDetector, "physDetector", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.3));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);
}

void SCDetectorConstruction::ConstructSource()
{
    // Define Carbon-14
    G4Isotope *C14 = new G4Isotope("C14", 6, 14, 14.003242 * g / mole);
    G4Element *elC14 = new G4Element("Carbon-14", "C14", 1);
    elC14->AddIsotope(C14, 100 * perCent);
    G4Material *matC14 = new G4Material("C14Source", 1.51 * g / cm3, 1);
    matC14->AddElement(elC14, 100 * perCent);

    // Carbon 14 Source
    G4double sourceRadius = 50.*um;

    solidSource = new G4Sphere("solidSource", 0., sourceRadius, 0.0, 360. * deg, 0.0, 180. * deg);
    logicSource = new G4LogicalVolume(solidSource, matC14, "logicSource");
    physSource = new G4PVPlacement(0, G4ThreeVector(0., 0., -1000. * um), logicSource, "physSource", logicWorld, 0, checkOverlaps);
    
    G4VisAttributes *sourceVisAtt =  new G4VisAttributes(G4Color(0.0, 0.0, 1.0, 0.5));
    sourceVisAtt->SetForceSolid(true);
    logicSource->SetVisAttributes(sourceVisAtt);
}

void SCDetectorConstruction::ConstructCollimator()
{
    // Material
    G4Material *collimatorMat = nist->FindOrBuildMaterial("G4_Cu");

    // Collimator
    G4double innerRadius = 0.5 * mm;
    G4double outerRadius = 1.5 * mm;
    G4double height = 1. * mm;

    solidCollimator = new G4Tubs("solidCollimator", innerRadius, outerRadius, 0.5 * height, 0.0, 360. * deg);
    logicCollimator = new G4LogicalVolume(solidCollimator, collimatorMat, "logicCollimator");
    physCollimator = new G4PVPlacement(nullptr, G4ThreeVector(0., 0., 527.5*um), logicCollimator, "physCollimator", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *collimatorVisAtt = new G4VisAttributes(G4Color(0.722, 0.451, 0.2, 0.5));
    collimatorVisAtt->SetForceSolid(true);
    logicCollimator->SetVisAttributes(collimatorVisAtt);

}

G4VPhysicalVolume *SCDetectorConstruction::Construct()
{
    // Manipulate materials of the volume
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    
    // Material property table for world
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    G4double worldRindex[2] = {1.0, 1.0};
    G4double worldEnergy[2] = {1.0*eV, 6.0*eV};
    G4double worldAbs[2] = {10.0 * m, 10.0 * m};
    mptWorld->AddProperty("RINDEX", worldEnergy, worldRindex, 2);
    mptWorld->AddProperty("ABSLENGTH", worldEnergy, worldAbs, 2);
    worldMat->SetMaterialPropertiesTable(mptWorld);

    // world
    G4double xWorld = 5. * mm;
    G4double yWorld = 5. * mm;
    G4double zWorld = 5. * mm;

    solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);

    ConstructScintillator();

    ConstructDetector();

    //ConstructSource();
    
    //ConstructCollimator();

    return physWorld;

} 

void SCDetectorConstruction::ConstructSDandField()
{
    // Photon Detector
    SCSensitiveDetector *sensDet = new SCSensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);

    // Photon Detector
    SCSensitiveDetector *sensColumn = new SCSensitiveDetector("SensitiveColumn");
    logicColumn->SetSensitiveDetector(sensColumn);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensColumn);
}