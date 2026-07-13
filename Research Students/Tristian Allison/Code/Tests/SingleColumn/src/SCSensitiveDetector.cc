/*
    Title           :   SCSensitiveDetector.cc
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 16, 2026
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
    
    G4double fGlobalTime = preStepPoint->GetGlobalTime();
    

    if (volumeName == "logicDetector" && particleName == "opticalphoton")
    {
        // if a photon hits detector enter data
        G4double energy = preStepPoint->GetKineticEnergy();
        G4double fWlen = ((h_Planck * c_light) / energy) / nm;

        // get position and the momentum of the photon
        G4ThreeVector posPhoton = preStepPoint->GetPosition();
        G4ThreeVector momPhoton = preStepPoint->GetMomentumDirection();

        // log each data point
        analysisManager->FillNtupleIColumn(0, 0, eventID);
        analysisManager->FillNtupleDColumn(0, 1, posPhoton[0]); // mm
        analysisManager->FillNtupleDColumn(0, 2, posPhoton[1]); // mm
        analysisManager->FillNtupleDColumn(0, 3, posPhoton[2]); // mm
        analysisManager->FillNtupleDColumn(0, 4, momPhoton[0]);
        analysisManager->FillNtupleDColumn(0, 5, momPhoton[1]);
        analysisManager->FillNtupleDColumn(0, 6, momPhoton[2]);
        analysisManager->FillNtupleDColumn(0, 7, energy / eV); // eV
        analysisManager->FillNtupleDColumn(0, 8, fWlen); // nm
        analysisManager->FillNtupleDColumn(0, 9, fGlobalTime);
        analysisManager->AddNtupleRow(0);
        
        // What I have currently so I only have to log when the photon is incident
        track->SetTrackStatus(fStopAndKill);

        //G4cout << "Event " << eventID << ": Photon w/ wavelength " << fWlen << "nm" << G4endl;
    }
    
    return true;
}