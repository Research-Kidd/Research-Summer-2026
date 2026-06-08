#include "SCPhysicsList.hh"

SCPhysicsList::SCPhysicsList()
{
    // EM Physics
    RegisterPhysics(new G4EmStandardPhysics());
}

SCPhysicsList::~SCPhysicsList()
{
    
}