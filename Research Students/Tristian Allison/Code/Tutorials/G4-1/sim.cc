#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

int main(int argc, char** argv)
{
    G4UIExecutive *ui = new G4UIExecutive(argc, argv); // hands over command line control

    // make runManager based on whether built multithreaded or not
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4RunManager *runManager = new G4RunManager;
    #endif

    // Initialise visualization control manager
    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialise();

    // UI manager
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    ui->SessionStart();

    return 0;
}