/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#ifndef SCACTIONINITIALIZATION_HH
#define SCACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

#include "SCPrimaryGenerator.hh"
#include "SCRunAction.hh"

class SCActionInitialization : public G4VUserActionInitialization
{
    public:
        SCActionInitialization();
        ~SCActionInitialization();

        virtual void BuildForMaster() const;
        virtual void Build() const;
};

#endif