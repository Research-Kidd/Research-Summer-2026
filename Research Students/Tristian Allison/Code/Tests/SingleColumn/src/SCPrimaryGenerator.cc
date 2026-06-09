/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :   Create a particle gun aimed at SC, shoots beta decay electrons 
*/
#include "SCPrimaryGenerator.hh"

SCPrimaryGenerator::SCPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    // Particle  position
    G4double x = 0. * um;
    G4double y = 100. * um;
    G4double z = -100. * um;

    G4ThreeVector pos(x, y, z);

    //Particle direction
    G4double px = 0.;
    G4double py = -1. / sqrt(2.);
    G4double pz = 1. / sqrt(2.);

    G4ThreeVector mom(px, py, pz);

    // Particle Type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("e-");

    // Particle gun features
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(49.47 * keV); // Energy obtained from NUDAT at https://www.nndc.bnl.gov/nudat3/decaysearchdirect.jsp?nuc=14C&unc=NDS
    fParticleGun->SetParticleDefinition(particle);

}

SCPrimaryGenerator::~SCPrimaryGenerator()
{
    delete fParticleGun;
}

void SCPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // Create Vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}