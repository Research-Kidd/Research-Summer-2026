/*
    Title           :   SCPrimaryGenerator.cc
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 16, 2026
    Purpose         :   Create a particle gun aimed at SC, shoots beta decay electrons 
*/
#include "SCPrimaryGenerator.hh"

SCPrimaryGenerator::SCPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    // Particle  position
    G4double x = 0. * um;
    G4double y = 0. * um;
    G4double z = -100. * um;

    G4ThreeVector pos(x, y, z);

    //Particle direction
    G4double px = 0.;
    G4double py = 0.;
    G4double pz = 0.;

    G4ThreeVector mom(px, py, pz);

    // Particle gun features
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
}

SCPrimaryGenerator::~SCPrimaryGenerator()
{
    delete fParticleGun;
}

void SCPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // Particle type
    G4int Z = 6;
    G4int A = 14;

    // learn more about this stuff to get more correct data
    G4double charge = 0. * eplus; // 
    G4double energy = 1. * eV; //

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);
    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    //fParticleGun->SetParticleEnergy(energy);

    // Create Vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}