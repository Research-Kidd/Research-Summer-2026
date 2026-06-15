/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#include "SCSensitiveDetector.hh"

SCSensitiveDetector::SCSensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    
}

SCSensitiveDetector::~SCSensitiveDetector()
{

}

void SCSensitiveDetector::Initialize(G4HCofThisEvent *)
{
    
}

void SCSensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{

}

G4bool SCSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *touchHist)
{
    G4Track *track = aStep->GetTrack();
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();

    G4String volumeName = preStepPoint->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName(); // Get Volume Name
    G4String particleName = track->GetDefinition()->GetParticleName();


    if (volumeName == "logicDetector" && particleName == "opticalphoton")
    {
        // if a photon hits detector enter histogram info
        G4double energy = preStepPoint->GetKineticEnergy();
        G4double fWlen = ((h_Planck * c_light) / energy) / nm;

        analysisManager->FillH1(0, fWlen);

        G4cout << "Photon wavelength hitting detector: " << energy << " nm" << G4endl; // for verbosity
    }
    else if (volumeName == "logicColumn" && particleName == "e-")
    {
        // if an electron hits scintillator enter histogram info
        G4double energy = preStepPoint->GetKineticEnergy()/keV;
        analysisManager->FillH1(1, energy);

        track->SetTrackStatus(fStopAndKill);

        G4cout << "Electron energy hitting scintillator: " << energy << " keV" << G4endl; // for verbosity
    } 
    return true;
}