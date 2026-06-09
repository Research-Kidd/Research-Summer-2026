/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "SCPhysicsList.hh"
#include "SCDetectorConstruction.hh"
#include "SCActionInitialization.hh"

int main(int argc, char** argv)
{
    G4UIExecutive *ui = nullptr; // hands over command line control

    // make runManager based on whether built multithreaded or not
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4RunManager *runManager = new G4RunManager;
    #endif

    // Physics list
    runManager->SetUserInitialization(new SCPhysicsList());

    // Detector Construction
    runManager->SetUserInitialization(new SCDetectorConstruction());

    // Action Initialization
    runManager->SetUserInitialization(new SCActionInitialization());

    if (argc == 1) 
    {
        ui = new G4UIExecutive(argc, argv);
    }


    // Initialise visualization control manager
    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialise();

    // UI manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (ui)
    {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();    
    }
    else
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    return 0;
}