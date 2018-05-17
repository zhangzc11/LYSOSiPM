

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
    analysisManager->CreateNtupleIColumn("nPhotons_Cherenkov_Gen");//4
    analysisManager->CreateNtupleIColumn("nPhotons_Scintillation_Gen");//4
    analysisManager->CreateNtupleIColumn("allPhoIndex", fEventAction->GetPhoIndexArray());//7
    analysisManager->CreateNtupleDColumn("allPhoTime", fEventAction->GetPhoTimeArray());//8
    analysisManager->CreateNtupleDColumn("allPhoTimeLocal", fEventAction->GetPhoTimeLocalArray());//9
    analysisManager->CreateNtupleDColumn("allPhoWaveLength", fEventAction->GetPhoWaveLengthArray());//10
    analysisManager->CreateNtupleDColumn("allPhoTrackLength", fEventAction->GetPhoTrackLengthArray());//11
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexX", fEventAction->GetPhoTrackVertexXArray());//12
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexY", fEventAction->GetPhoTrackVertexYArray());//13
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexZ", fEventAction->GetPhoTrackVertexZArray());//14
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexR", fEventAction->GetPhoTrackVertexRArray());//15
    analysisManager->CreateNtupleIColumn("allPhoIsCerenkov", fEventAction->GetPhoIsCerenkovArray());//16
    analysisManager->CreateNtupleDColumn("time1", fEventAction->GetTime1Array());//17
    analysisManager->CreateNtupleDColumn("time2", fEventAction->GetTime2Array());//18
    analysisManager->CreateNtupleDColumn("amp1", fEventAction->GetAmp1Array());//19
    analysisManager->CreateNtupleDColumn("amp2", fEventAction->GetAmp2Array());//20

    analysisManager->CreateNtupleIColumn("allPhoIndex_sptr", fEventAction->GetPhoIndexArray_sptr());//21
    analysisManager->CreateNtupleDColumn("allPhoTime_sptr", fEventAction->GetPhoTimeArray_sptr());//22
    analysisManager->CreateNtupleDColumn("allPhoWaveLength_sptr", fEventAction->GetPhoWaveLengthArray_sptr());//23
    analysisManager->CreateNtupleDColumn("allPhoTrackLength_sptr", fEventAction->GetPhoTrackLengthArray_sptr());//24
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexX_sptr", fEventAction->GetPhoTrackVertexXArray_sptr());//25
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexY_sptr", fEventAction->GetPhoTrackVertexYArray_sptr());//26
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexZ_sptr", fEventAction->GetPhoTrackVertexZArray_sptr());//27
    analysisManager->CreateNtupleDColumn("allPhoTrackVertexR_sptr", fEventAction->GetPhoTrackVertexRArray_sptr());//28
    analysisManager->CreateNtupleIColumn("allPhoIsCerenkov_sptr", fEventAction->GetPhoIsCerenkovArray_sptr());//29
    analysisManager->CreateNtupleDColumn("amp1_sptr", fEventAction->GetAmp1Array_sptr());//30
    analysisManager->CreateNtupleDColumn("amp2_sptr", fEventAction->GetAmp2Array_sptr());//31

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


