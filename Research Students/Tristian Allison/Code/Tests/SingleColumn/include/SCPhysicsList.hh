#ifndef SCPHYSICSLIST_HH
#define SCPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh" // makes a modular physics list
#include "G4EmStandardPhysics.hh" // imports electromagnetism physics list
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

// class inherits from G4VModular Physics List
class SCPhysicsList : public G4VModularPhysicsList
{
    public:
        SCPhysicsList();
        ~SCPhysicsList();
};

#endif