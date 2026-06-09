/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#ifndef SCPRIMARYGENERATOR_HH
#define SCPRIMARYGENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonTable.hh"

class SCPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
    public:
        SCPrimaryGenerator();
        ~SCPrimaryGenerator();

        virtual void GeneratePrimaries(G4Event *);

    private:
        G4ParticleGun *fParticleGun;
};

#endif