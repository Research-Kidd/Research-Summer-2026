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
    fTotalEnergyDeposited = 0.;
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
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();

    G4double energy = preStepPoint->GetKineticEnergy();
    G4double fWlen = ((h_Planck * c_light) / energy) / nm;

    analysisManager->FillH1(0, fWlen);

    return true;
}