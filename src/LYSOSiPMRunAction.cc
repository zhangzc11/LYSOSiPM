

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
    analysisManager->CreateNtupleIColumn("nPhotons");//3
    analysisManager->CreateNtupleIColumn("nPhotons_Cherenkov");//4
    analysisManager->CreateNtupleIColumn("allPhoIndex", fEventAction->GetPhoIndexArray());//5
    analysisManager->CreateNtupleDColumn("allPhoTime", fEventAction->GetPhoTimeArray());//6
    analysisManager->CreateNtupleDColumn("allPhoTimeLocal", fEventAction->GetPhoTimeLocalArray());//7
    analysisManager->CreateNtupleDColumn("allPhoWaveLength", fEventAction->GetPhoWaveLengthArray());//8
    analysisManager->CreateNtupleDColumn("allPhoTrackLength", fEventAction->GetPhoTrackLengthArray());//9
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexX", fEventAction->GetPhoTrackVertexXArray());//10
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexY", fEventAction->GetPhoTrackVertexYArray());//11
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexZ", fEventAction->GetPhoTrackVertexZArray());//12
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexR", fEventAction->GetPhoTrackVertexRArray());//13
    analysisManager->CreateNtupleIColumn("allPhoIsCerenkov", fEventAction->GetPhoIsCerenkovArray());//14
    analysisManager->CreateNtupleDColumn("time1", fEventAction->GetTime1Array());//15
    analysisManager->CreateNtupleDColumn("time2", fEventAction->GetTime2Array());//16
    analysisManager->CreateNtupleDColumn("amp1", fEventAction->GetAmp1Array());//17
    analysisManager->CreateNtupleDColumn("amp2", fEventAction->GetAmp2Array());//18
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


