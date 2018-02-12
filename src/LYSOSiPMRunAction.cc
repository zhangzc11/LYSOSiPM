

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

    // Creating histograms
    analysisManager->CreateH1("E", "Energy deposit in LYSO", 200, 0., 10.0*MeV);
    analysisManager->CreateH1("ScatAngle", "Scattering angle", 4, 0., 360*degree);
    analysisManager->CreateH1("ScatPhi", "Scattering angle (phi)", 360, 0., 360*degree);
    analysisManager->CreateH1("DeltaPhi", "Delta phi", 360, 0., 360*degree);

    // Creating ntuple
    analysisManager->CreateNtuple("tree", "Edep");
    analysisManager->CreateNtupleDColumn("Eabs");
    analysisManager->CreateNtupleDColumn("ScatAngle");
    analysisManager->CreateNtupleDColumn("ScatPhi");
    analysisManager->CreateNtupleDColumn("DeltaPhi");
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
    G4String fileName = "LYSOSiPM_out_ntuple";
    analysisManager->OpenFile(fileName);
}



void LYSOSiPMRunAction::EndOfRunAction(const G4Run* /*run*/)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    // save histograms & ntuple
    analysisManager->Write();
    analysisManager->CloseFile();
}


