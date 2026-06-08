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