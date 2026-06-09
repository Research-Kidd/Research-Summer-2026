/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#ifndef PMDETECTORCONSTRUCTION_HH
#define PMDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh" // main class for detector construction

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"

// volume libraries
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"

#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4SDManager.hh"

#include "SCSensitiveDetector.hh"

class SCDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        SCDetectorConstruction();
        virtual ~SCDetectorConstruction();

        virtual G4VPhysicalVolume *Construct();

    private:
        G4LogicalVolume *logicDetector, *logicWorld, *logicColumn;
        G4VPhysicalVolume *physWorld, *physColumn;
        G4Box *solidWorld;
        G4Tubs *solidColumn;
        G4NistManager *nist;

        G4bool checkOverlaps = true; // make sure volumes do not overlap

        virtual void ConstructSDandField();

        void ConstructScintillator();
};


#endif