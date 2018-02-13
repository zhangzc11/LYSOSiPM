

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
		  fAmp(kDigi),
		  photonIndex(0)
{}

LYSOSiPMEventAction::~LYSOSiPMEventAction() {}

void LYSOSiPMEventAction::AddPhoton(G4double time, G4double time_local, G4double trackLength, G4double trackVertexX, G4double trackVertexY, G4double trackVertexZ)
{
	//allPhoTime.push_back(time);
	allPhoTimeLocal.push_back(time_local);
	allPhoTrackLength.push_back(trackLength);
	allPhoTrackVertexX.push_back(trackVertexX);
	allPhoTrackVertexY.push_back(trackVertexY);
	allPhoTrackVertexZ.push_back(trackVertexZ);

	time_index.insert(std::pair<G4double, G4int>(time, photonIndex));

	photonIndex ++;
}

void LYSOSiPMEventAction::BeginOfEventAction(const G4Event * /*event*/) {
    // initialisation per event
    cEnergyAbs = 0.;
    //scatAng = 0.;
    //scatPhi = 0.;
    deltaPhi = 0.;
    scattered = false;
    recorded = false;
	photonIndex = 0;
}


void LYSOSiPMEventAction::EndOfEventAction(const G4Event *event) {
    // Accumulate statistics

	//std::sort(allPhoTime.begin(), allPhoTime.end());
	G4int numSave = 0;
	for(auto tmp : time_index)
	{
		allPhoTime.push_back(tmp.first);
		if(numSave<NSaveMax)
		{
			allPhoTime_save.push_back(tmp.first);
			allPhoIndex_save.push_back(numSave);
			allPhoTrackLength_save.push_back(allPhoTrackLength[tmp.second]);
			allPhoTimeLocal_save.push_back(allPhoTimeLocal[tmp.second]);
			allPhoTrackVertexX_save.push_back(allPhoTrackVertexX[tmp.second]);
			allPhoTrackVertexY_save.push_back(allPhoTrackVertexY[tmp.second]);
			allPhoTrackVertexZ_save.push_back(allPhoTrackVertexZ[tmp.second]);
			allPhoTrackVertexR_save.push_back(std::sqrt(
							(allPhoTrackVertexX[tmp.second] - grease_x)*(allPhoTrackVertexX[tmp.second] - grease_x) + 
							(allPhoTrackVertexY[tmp.second] - grease_y)*(allPhoTrackVertexY[tmp.second] - grease_y)+
							(allPhoTrackVertexZ[tmp.second] - grease_z)*(allPhoTrackVertexZ[tmp.second] - grease_z)));
		}
		numSave++;
	}



	//sudo-digitization photon current pulse:

	G4int kPhotonIndex = 0;
	G4int kPhotonIndex_pre = 0;
	for(G4int iS = 0; iS<kDigi; iS++)
	{
		//10ps per sample
		G4double time_this = iS*digi_step; //ns
		for(G4int kp = kPhotonIndex_pre; kp<allPhoTime.size();kp++)
		{
			if(allPhoTime[kp]>time_this) break;
			kPhotonIndex ++;
		}
		
		fTime[iS] = time_this;
		fAmp[iS] = 1.0*(kPhotonIndex-kPhotonIndex_pre)/digi_step;
		kPhotonIndex_pre = kPhotonIndex;
	}

	// get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // fill ntuple
    if(cEnergyAbs > 0) analysisManager->FillNtupleDColumn(0, cEnergyAbs);
    analysisManager->FillNtupleDColumn(1, event->GetPrimaryVertex()->GetX0());
    analysisManager->FillNtupleDColumn(2, event->GetPrimaryVertex()->GetY0());
    analysisManager->FillNtupleIColumn(3, allPhoTime.size());
    analysisManager->AddNtupleRow();

	allPhoTime.clear();
	allPhoTimeLocal.clear();
	time_index.clear();
	allPhoTime_save.clear();
	allPhoIndex_save.clear();
	allPhoTimeLocal_save.clear();
	allPhoTrackLength.clear();
	allPhoTrackLength_save.clear();
	allPhoTrackVertexX.clear();
	allPhoTrackVertexX_save.clear();
	allPhoTrackVertexY.clear();
	allPhoTrackVertexY_save.clear();
	allPhoTrackVertexZ.clear();
	allPhoTrackVertexZ_save.clear();
	allPhoTrackVertexR_save.clear();

}




