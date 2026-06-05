#include "PMSensitiveDetector.hh"

PMSensitiveDetector::PMSensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
    fToatalEnergyDeposited = 0.;
}

PMSensitiveDetector::~PMSensitiveDetector()
{

}

void PMSensitiveDetector::Initialize(G4HCofThisEvent *)
{
    fToatalEnergyDeposited = 0.;
}

void PMSensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
    G4cout << "Deposited energy: " << fToatalEnergyDeposited << G4endl;
}

G4bool PMSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *touchHist)
{
    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();

    if (fEnergyDeposited > 0)
    {
        fToatalEnergyDeposited += fEnergyDeposited;
    }

    return true;
}
