/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#include "SCPhysicsList.hh"

SCPhysicsList::SCPhysicsList()
{
    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics());
    
    // Optical Physics
    RegisterPhysics(new G4OpticalPhysics());
}

SCPhysicsList::~SCPhysicsList()
{
    
}