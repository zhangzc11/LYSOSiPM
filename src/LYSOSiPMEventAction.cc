#include <random>

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
		  fTime1(kDigi),
		  fTime2(kDigi),
		  fAmp1(kDigi),
		  fAmp2(kDigi),
		  photonIndex(0),
		  fAmp1_sptr(kDigi),
		  fAmp2_sptr(kDigi),
		  nPhotons_Cerenkov(0),
		  nPhotons_Cerenkov_Gen(0),
		  nPhotons_Cerenkov_Collect(0),
		  nPhotons_Scintillation_Gen(0),
		  nPhotons_Scintillation_Collect(0)
{}

LYSOSiPMEventAction::~LYSOSiPMEventAction() {}

void LYSOSiPMEventAction::CountScintillationPhotonGen()
{
	nPhotons_Scintillation_Gen ++ ;
}

void LYSOSiPMEventAction::CountCerenkovPhotonGen()
{
	nPhotons_Cerenkov_Gen ++ ;
}

void LYSOSiPMEventAction::CountScintillationPhotonCollect()
{
	nPhotons_Scintillation_Collect ++ ;
}

void LYSOSiPMEventAction::CountCerenkovPhotonCollect()
{
	nPhotons_Cerenkov_Collect ++ ;
}


void LYSOSiPMEventAction::AddPhoton(G4double time, G4double time_local, G4double trackLength, G4double trackVertexX, G4double trackVertexY, G4double trackVertexZ, G4double trackTotalEnergy, G4int isCerenkov)
{
	//allPhoTime.push_back(time);
	allPhoTimeLocal.push_back(time_local);

	allPhoTrackLength.push_back(trackLength);
	allPhoWaveLength.push_back(0.001241/trackTotalEnergy);//1eV = 1241nm, 1MeV = 0.001241nm
	allPhoTrackVertexX.push_back(trackVertexX);
	allPhoTrackVertexY.push_back(trackVertexY);
	allPhoTrackVertexZ.push_back(trackVertexZ);
	allPhoIsCerenkov.push_back(isCerenkov);
	if(isCerenkov) nPhotons_Cerenkov++;

	std::random_device rd;
    	std::mt19937 e2(rd());
	std::normal_distribution<> dist(time, SPTR);
	G4double time_sptr = dist(e2); 
	time_index.insert(std::pair<G4double, G4int>(time, photonIndex));
	time_index_sptr.insert(std::pair<G4double, G4int>(time_sptr, photonIndex));

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
	nPhotons_Cerenkov = 0;
	nPhotons_Cerenkov_Gen = 0;
	nPhotons_Cerenkov_Collect = 0;
	nPhotons_Scintillation_Gen = 0;
	nPhotons_Scintillation_Collect = 0;

}


void LYSOSiPMEventAction::EndOfEventAction(const G4Event *event) {
    // Accumulate statistics

	//std::sort(allPhoTime.begin(), allPhoTime.end());
	//no sptr
	G4int numSave = 0;
	for(auto tmp : time_index)
	{
		allPhoTime.push_back(tmp.first);
		if(numSave<NSaveMax)
		{
			allPhoTime_save.push_back(tmp.first);
			allPhoIndex_save.push_back(numSave);
			allPhoTrackLength_save.push_back(allPhoTrackLength[tmp.second]);
			allPhoWaveLength_save.push_back(allPhoWaveLength[tmp.second]);
			allPhoTimeLocal_save.push_back(allPhoTimeLocal[tmp.second]);
			allPhoTrackVertexX_save.push_back(allPhoTrackVertexX[tmp.second]);
			allPhoTrackVertexY_save.push_back(allPhoTrackVertexY[tmp.second]);
			allPhoTrackVertexZ_save.push_back(allPhoTrackVertexZ[tmp.second]);
			allPhoIsCerenkov_save.push_back(allPhoIsCerenkov[tmp.second]);
			allPhoTrackVertexR_save.push_back(std::sqrt(
							(allPhoTrackVertexX[tmp.second] - grease_x)*(allPhoTrackVertexX[tmp.second] - grease_x) + 
							(allPhoTrackVertexY[tmp.second] - grease_y)*(allPhoTrackVertexY[tmp.second] - grease_y)+
							(allPhoTrackVertexZ[tmp.second] - grease_z)*(allPhoTrackVertexZ[tmp.second] - grease_z)));
		}
		numSave++;
	}

	//with sptr
	G4int numSave_sptr = 0;
	for(auto tmp : time_index_sptr)
	{
		allPhoTime_sptr.push_back(tmp.first);
		if(numSave_sptr<NSaveMax)
		{
			allPhoTime_save_sptr.push_back(tmp.first);
			allPhoIndex_save_sptr.push_back(numSave_sptr);
			allPhoTrackLength_save_sptr.push_back(allPhoTrackLength[tmp.second]);
			allPhoWaveLength_save_sptr.push_back(allPhoWaveLength[tmp.second]);
			allPhoTrackVertexX_save_sptr.push_back(allPhoTrackVertexX[tmp.second]);
			allPhoTrackVertexY_save_sptr.push_back(allPhoTrackVertexY[tmp.second]);
			allPhoTrackVertexZ_save_sptr.push_back(allPhoTrackVertexZ[tmp.second]);
			allPhoIsCerenkov_save_sptr.push_back(allPhoIsCerenkov[tmp.second]);
			allPhoTrackVertexR_save_sptr.push_back(std::sqrt(
							(allPhoTrackVertexX[tmp.second] - grease_x)*(allPhoTrackVertexX[tmp.second] - grease_x) + 
							(allPhoTrackVertexY[tmp.second] - grease_y)*(allPhoTrackVertexY[tmp.second] - grease_y)+
							(allPhoTrackVertexZ[tmp.second] - grease_z)*(allPhoTrackVertexZ[tmp.second] - grease_z)));
		}
		numSave_sptr++;
	}




	//sudo-digitization photon current pulse - no sptr:

	G4int kPhotonIndex1 = 0;
	G4int kPhotonIndex2 = 0;
	G4int kPhotonIndex_pre1 = 0;
	G4int kPhotonIndex_pre2 = 0;
	for(G4int iS = 0; iS<kDigi; iS++)
	{
		G4double time_this1 = iS*digi_step1; //ns
		G4double time_this2 = iS*digi_step2; //ns
		for(G4int kp = kPhotonIndex_pre1; kp<allPhoTime.size(); kp++)
		{
			if(allPhoTime[kp]>time_this1) break;
			kPhotonIndex1 ++;
		}

		for(G4int kp = kPhotonIndex_pre2; kp<allPhoTime.size(); kp++)
		{
			if(allPhoTime[kp]>time_this2) break;
			kPhotonIndex2 ++;
		}
		
		fTime1[iS] = time_this1;
		fTime2[iS] = time_this2;

		fAmp1[iS] = 1.0*(kPhotonIndex1-kPhotonIndex_pre1)/digi_step1;
		fAmp2[iS] = 1.0*(kPhotonIndex2-kPhotonIndex_pre2)/digi_step2;

		kPhotonIndex_pre1 = kPhotonIndex1;
		kPhotonIndex_pre2 = kPhotonIndex2;
	}

	//sudo-digitization photon current pulse - with sptr:

	G4int kPhotonIndex1_sptr = 0;
	G4int kPhotonIndex2_sptr = 0;
	G4int kPhotonIndex_pre1_sptr = 0;
	G4int kPhotonIndex_pre2_sptr = 0;
	for(G4int iS = 0; iS<kDigi; iS++)
	{
		G4double time_this1 = iS*digi_step1; //ns
		G4double time_this2 = iS*digi_step2; //ns
		for(G4int kp = kPhotonIndex_pre1_sptr; kp<allPhoTime_sptr.size(); kp++)
		{
			if(allPhoTime_sptr[kp]>time_this1) break;
			kPhotonIndex1_sptr ++;
		}

		for(G4int kp = kPhotonIndex_pre2_sptr; kp<allPhoTime_sptr.size(); kp++)
		{
			if(allPhoTime_sptr[kp]>time_this2) break;
			kPhotonIndex2_sptr ++;
		}
		
		fAmp1_sptr[iS] = 1.0*(kPhotonIndex1_sptr-kPhotonIndex_pre1_sptr)/digi_step1;
		fAmp2_sptr[iS] = 1.0*(kPhotonIndex2_sptr-kPhotonIndex_pre2_sptr)/digi_step2;
	
		if(iS == 0 )
		{
			fAmp1_sptr[iS] = 1.0*(kPhotonIndex1_sptr-kPhotonIndex_pre1_sptr)/(0.0 - allPhoTime_sptr[0]);
			fAmp2_sptr[iS] = 1.0*(kPhotonIndex2_sptr-kPhotonIndex_pre2_sptr)/(0.0 - allPhoTime_sptr[0]);
		}

		kPhotonIndex_pre1_sptr = kPhotonIndex1_sptr;
		kPhotonIndex_pre2_sptr = kPhotonIndex2_sptr;
	}


	// get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // fill ntuple
    if(cEnergyAbs > 0) analysisManager->FillNtupleDColumn(0, cEnergyAbs);
    analysisManager->FillNtupleDColumn(1, event->GetPrimaryVertex()->GetX0());
    analysisManager->FillNtupleDColumn(2, event->GetPrimaryVertex()->GetY0());
    analysisManager->FillNtupleIColumn(3, allPhoTime.size());
    analysisManager->FillNtupleIColumn(4, nPhotons_Cerenkov);
    analysisManager->FillNtupleIColumn(5, nPhotons_Cerenkov_Gen);
    analysisManager->FillNtupleIColumn(6, nPhotons_Scintillation_Gen);
    analysisManager->FillNtupleIColumn(7, nPhotons_Cerenkov_Collect);
    analysisManager->FillNtupleIColumn(8, nPhotons_Scintillation_Collect);

    analysisManager->AddNtupleRow();

	allPhoTime.clear();
	time_index.clear();
	allPhoTime_save.clear();
	allPhoIndex_save.clear();
	allPhoTimeLocal_save.clear();
	allPhoWaveLength.clear();
	allPhoWaveLength_save.clear();
	allPhoTrackLength.clear();
	allPhoTrackLength_save.clear();
	allPhoTrackVertexX.clear();
	allPhoTrackVertexX_save.clear();
	allPhoTrackVertexY.clear();
	allPhoTrackVertexY_save.clear();
	allPhoTrackVertexZ.clear();
	allPhoTrackVertexZ_save.clear();
	allPhoTrackVertexR_save.clear();
	allPhoIsCerenkov.clear();
	allPhoIsCerenkov_save.clear();


	allPhoTime_sptr.clear();
	time_index_sptr.clear();
	allPhoTime_save_sptr.clear();
	allPhoIndex_save_sptr.clear();
	allPhoWaveLength_save_sptr.clear();
	allPhoTrackLength_save_sptr.clear();
	allPhoTrackVertexX_save_sptr.clear();
	allPhoTrackVertexY_save_sptr.clear();
	allPhoTrackVertexZ_save_sptr.clear();
	allPhoTrackVertexR_save_sptr.clear();
	allPhoIsCerenkov_save_sptr.clear();


}




