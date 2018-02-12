

#include "LYSOSiPMRunAction.hh"
#include "LYSOSiPMAnalysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"



LYSOSiPMRunAction::LYSOSiPMRunAction()
        : G4UserRunAction()
{
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(1);

    // Create analysis manager
    // The choice of analysis technology is done via selection of a namespace
    // in LYSOSiPMAnalysis.hh
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;

    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(0);

    // Book histograms, ntuple

    // Creating ntuple
    analysisManager->CreateNtuple("tree", "Edep");
    analysisManager->CreateNtupleDColumn("Eabs");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("nPhotons");
    analysisManager->CreateNtupleDColumn("phoTime1");
    analysisManager->CreateNtupleDColumn("phoTime10");
    analysisManager->CreateNtupleDColumn("phoTime50");
    analysisManager->CreateNtupleDColumn("phoTime100");
    analysisManager->CreateNtupleDColumn("phoTime1000");
    analysisManager->FinishNtuple();
}




LYSOSiPMRunAction::~LYSOSiPMRunAction()
{
    delete G4AnalysisManager::Instance();
}


void LYSOSiPMRunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    //inform the runManager to save random number seed
    //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    G4String fileName = "ntuple";
    analysisManager->OpenFile(fileName);
}



void LYSOSiPMRunAction::EndOfRunAction(const G4Run* /*run*/)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // save histograms & ntuple
    analysisManager->Write();
    analysisManager->CloseFile();
}


