

#include "LYSOSiPMEventAction.hh"
#include "LYSOSiPMAnalysis.hh"
#include "LYSOSiPMPrimaryGeneratorAction.hh"
#include "LYSOSiPMSteppingAction.hh"
#include "G4RunManager.hh"

LYSOSiPMEventAction::LYSOSiPMEventAction()
        : G4UserEventAction(),
          cEnergyAbs(0.),
          //scatAng(0.),
          //scatPhi(0.),
          deltaPhi(0.),
		  fTime(kDigi),
		  fAmp(kDigi)
{}

LYSOSiPMEventAction::~LYSOSiPMEventAction() {}

void LYSOSiPMEventAction::AddPhoTime(G4double time)
{
	allPhoTime.push_back(time);
}

void LYSOSiPMEventAction::BeginOfEventAction(const G4Event * /*event*/) {
    // initialisation per event
    cEnergyAbs = 0.;
    //scatAng = 0.;
    //scatPhi = 0.;
    deltaPhi = 0.;
    scattered = false;
    recorded = false;
}


void LYSOSiPMEventAction::EndOfEventAction(const G4Event *event) {
    // Accumulate statistics

	//sort photon time in grease
	G4double phoTime1 = 0.0;
	G4double phoTime10 = 0.0;
	G4double phoTime50 = 0.0;
	G4double phoTime100 = 0.0;
	G4double phoTime1000 = 0.0;

	std::sort(allPhoTime.begin(), allPhoTime.end());
	if(allPhoTime.size()>=1) phoTime1 = allPhoTime[0];
	if(allPhoTime.size()>=10) phoTime10 = allPhoTime[10];
	if(allPhoTime.size()>=50) phoTime50 = allPhoTime[49];
	if(allPhoTime.size()>=100) phoTime100 = allPhoTime[99];
	if(allPhoTime.size()>=1000) phoTime1000 = allPhoTime[999];

	//sudo-digitization photon current pulse:

	G4int kPhotonIndex = 0;
	for(G4int iS = 0; iS<kDigi; iS++)
	{
		//10ps per sample
		G4double time_this = iS*0.01; //ns
		G4int kPhotonIndex_pre = kPhotonIndex;
		for(G4int kp = kPhotonIndex_pre; kp<allPhoTime.size();kp++)
		{
			if(allPhoTime[kp]>time_this) break;
			kPhotonIndex ++;
		}
		fTime[iS] = time_this;
		fAmp[iS] = 1.0*kPhotonIndex;
	}

	// get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // fill ntuple
    if(cEnergyAbs > 0) analysisManager->FillNtupleDColumn(0, cEnergyAbs);
    analysisManager->FillNtupleDColumn(1, event->GetPrimaryVertex()->GetX0());
    analysisManager->FillNtupleDColumn(2, event->GetPrimaryVertex()->GetY0());
    analysisManager->FillNtupleDColumn(3, allPhoTime.size());
    analysisManager->FillNtupleDColumn(4, phoTime1);
    analysisManager->FillNtupleDColumn(5, phoTime10);
    analysisManager->FillNtupleDColumn(6, phoTime50);
    analysisManager->FillNtupleDColumn(7, phoTime100);
    analysisManager->FillNtupleDColumn(8, phoTime1000);
    analysisManager->AddNtupleRow();

	allPhoTime.clear();
}




