/*
    Title           :
    Author          :   Tristan Allison
    Date Created    :   June 8, 2026
    Date Edited     :   June 9, 2026
    Purpose         :
*/
#include "SCRunAction.hh"

SCRunAction::SCRunAction()
{
    // get instance of analysis manager and let NtupleMerging
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    
    analysisManager->CreateNtuple("Photons", "Photons");
    analysisManager->CreateNtupleIColumn("iEvent");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("dx");
    analysisManager->CreateNtupleDColumn("dy");
    analysisManager->CreateNtupleDColumn("dz");
    analysisManager->CreateNtupleDColumn("energy");
    analysisManager->CreateNtupleDColumn("fWlen");
    analysisManager->CreateNtupleDColumn("fGlobalTime");
    analysisManager->FinishNtuple();
}

SCRunAction::~SCRunAction()
{

}

void SCRunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID(); 

    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("output" + strRunID.str() + ".root");


}

void SCRunAction::EndOfRunAction(const G4Run *run)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();

    analysisManager->CloseFile();

    G4int runID = run->GetRunID();

    G4cout << "Finishing run " << runID << G4endl;
}