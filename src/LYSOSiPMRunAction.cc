

#include "LYSOSiPMRunAction.hh"
#include "LYSOSiPMAnalysis.hh"
#include "LYSOSiPMEventAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"



LYSOSiPMRunAction::LYSOSiPMRunAction(LYSOSiPMEventAction* eventAction)
        : G4UserRunAction(),
		fEventAction(eventAction)
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
	if( fEventAction)
	{
    analysisManager->CreateNtuple("tree", "Edep");
    analysisManager->CreateNtupleDColumn("Eabs");//0
    analysisManager->CreateNtupleDColumn("x");//1
    analysisManager->CreateNtupleDColumn("y");//2
    analysisManager->CreateNtupleDColumn("nPhotons");//3
    analysisManager->CreateNtupleDColumn("phoTime1");//4
    analysisManager->CreateNtupleDColumn("phoTime10");//5
    analysisManager->CreateNtupleDColumn("phoTime50");//6
    analysisManager->CreateNtupleDColumn("phoTime100");//7
    analysisManager->CreateNtupleDColumn("phoTime1000");//8
    analysisManager->CreateNtupleDColumn("time", fEventAction->GetTimeArray());//9
    analysisManager->CreateNtupleDColumn("amp", fEventAction->GetAmpArray());//10
    analysisManager->FinishNtuple();
	}
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


