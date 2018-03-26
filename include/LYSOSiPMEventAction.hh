

#ifndef LYSOSiPMEventAction_h
#define LYSOSiPMEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include <vector>
#include <map>
/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

//constants
const G4int kDigi = 1024;//number of samples
const G4double digi_step1 = 0.1;//100 ns window
const G4double digi_step2 = 0.003;//3 ns window
const G4int kDet = 1;
const G4int NSaveMax = 5000;
const G4double grease_x = 0.0;
const G4double grease_y = 0.0;
const G4double grease_z = 1.5;//mm
const G4double SPTR = 66.0;//ps

class LYSOSiPMEventAction : public G4UserEventAction {
public:
    LYSOSiPMEventAction();

    virtual ~LYSOSiPMEventAction();

    virtual void BeginOfEventAction(const G4Event *event);

    virtual void EndOfEventAction(const G4Event *event);

    void AddAbsC(G4double de);

    void AddScatAngle(G4double ang);
    void AddScatPhi(G4double phi);
    void AddDeltaPhi(G4double delPhi);

    void ScatBool(G4bool scatYN);
    void RecordedBool(G4bool recordYN);
	void AddPhoton(G4double time, G4double time_local, G4double trackLength, G4double trackVertexX, G4double trackVertexY, G4double trackVertexZ, G4double trackTotalEnergy, G4int isCerenkov);

	std::vector<G4double> & GetTime1Array(){ return fTime1;}
	std::vector<G4double> & GetTime2Array(){ return fTime2;}
	std::vector<G4double> & GetAmp1Array(){ return fAmp1;}
	std::vector<G4double> & GetAmp2Array(){ return fAmp2;}
	std::vector<G4double> & GetPhoTimeArray(){ return allPhoTime_save;}
	std::vector<G4int> & GetPhoIndexArray(){ return allPhoIndex_save;}
	std::vector<G4double> & GetPhoTimeLocalArray(){ return allPhoTimeLocal_save;}
	std::vector<G4double> & GetPhoTrackLengthArray(){ return allPhoTrackLength_save;}
	std::vector<G4double> & GetPhoWaveLengthArray(){ return allPhoWaveLength_save;}
	std::vector<G4double> & GetPhoTrackVertexXArray(){ return allPhoTrackVertexX_save;}
	std::vector<G4double> & GetPhoTrackVertexYArray(){ return allPhoTrackVertexY_save;}
	std::vector<G4double> & GetPhoTrackVertexZArray(){ return allPhoTrackVertexZ_save;}
	std::vector<G4double> & GetPhoTrackVertexRArray(){ return allPhoTrackVertexR_save;}
	std::vector<G4int> & GetPhoIsCerenkovArray(){ return allPhoIsCerenkov_save;}

	std::vector<G4double> & GetAmp1Array_sptr(){ return fAmp1_sptr;}
	std::vector<G4double> & GetAmp2Array_sptr(){ return fAmp2_sptr;}
	std::vector<G4double> & GetPhoTimeArray_sptr(){ return allPhoTime_save_sptr;}
	std::vector<G4int> & GetPhoIndexArray_sptr(){ return allPhoIndex_save_sptr;}
	std::vector<G4double> & GetPhoTrackLengthArray_sptr(){ return allPhoTrackLength_save_sptr;}
	std::vector<G4double> & GetPhoWaveLengthArray_sptr(){ return allPhoWaveLength_save_sptr;}
	std::vector<G4double> & GetPhoTrackVertexXArray_sptr(){ return allPhoTrackVertexX_save_sptr;}
	std::vector<G4double> & GetPhoTrackVertexYArray_sptr(){ return allPhoTrackVertexY_save_sptr;}
	std::vector<G4double> & GetPhoTrackVertexZArray_sptr(){ return allPhoTrackVertexZ_save_sptr;}
	std::vector<G4double> & GetPhoTrackVertexRArray_sptr(){ return allPhoTrackVertexR_save_sptr;}
	std::vector<G4int> & GetPhoIsCerenkovArray_sptr(){ return allPhoIsCerenkov_save_sptr;}

private:
    G4double cEnergyAbs;
    G4double scatAng;
    G4double scatPhi;
    G4double deltaPhi;
    G4bool scattered;
    G4bool recorded;
	
	G4int photonIndex;
	std::vector<G4double> allPhoTime;
	std::vector<G4double> allPhoTimeLocal;
	std::map<G4double, G4int> time_index;
	std::vector<G4double> allPhoTime_save;
	std::vector<G4int> allPhoIndex_save;
	std::vector<G4double> allPhoTimeLocal_save;
	std::vector<G4double> allPhoWaveLength;
	std::vector<G4double> allPhoWaveLength_save;
	std::vector<G4double> allPhoTrackLength;
	std::vector<G4double> allPhoTrackLength_save;
	std::vector<G4double> allPhoTrackVertexX;
	std::vector<G4double> allPhoTrackVertexX_save;
	std::vector<G4double> allPhoTrackVertexY;
	std::vector<G4double> allPhoTrackVertexY_save;
	std::vector<G4double> allPhoTrackVertexZ;
	std::vector<G4double> allPhoTrackVertexZ_save;
	std::vector<G4double> allPhoTrackVertexR_save;
	std::vector<G4int> allPhoIsCerenkov_save;
	std::vector<G4int> allPhoIsCerenkov;
	std::vector<G4double> fTime1;
	std::vector<G4double> fTime2;
	std::vector<G4double> fAmp1;
	std::vector<G4double> fAmp2;


	std::vector<G4double> allPhoTime_sptr;
	std::map<G4double, G4int> time_index_sptr;
	std::vector<G4double> allPhoTime_save_sptr;
	std::vector<G4int> allPhoIndex_save_sptr;
	std::vector<G4double> allPhoWaveLength_save_sptr;
	std::vector<G4double> allPhoTrackLength_save_sptr;
	std::vector<G4double> allPhoTrackVertexX_save_sptr;
	std::vector<G4double> allPhoTrackVertexY_save_sptr;
	std::vector<G4double> allPhoTrackVertexZ_save_sptr;
	std::vector<G4int> allPhoIsCerenkov_save_sptr;
	std::vector<G4double> fAmp1_sptr;
	std::vector<G4double> fAmp2_sptr;


	G4int nPhotons_Cerenkov;
};

// inline functions
inline void LYSOSiPMEventAction::AddAbsC(G4double de){
    cEnergyAbs += de;
}

inline void LYSOSiPMEventAction::AddScatAngle(G4double ang){
    scatAng = ang;
}

inline void LYSOSiPMEventAction::AddScatPhi(G4double phi){
    scatPhi = phi;
}

inline void LYSOSiPMEventAction::AddDeltaPhi(G4double dPhi) {
    deltaPhi += dPhi;
}

inline void LYSOSiPMEventAction::ScatBool(G4bool isScattered){
    scattered = isScattered;
}
inline void LYSOSiPMEventAction::RecordedBool(G4bool isRecorded) {
    recorded = isRecorded;
}
#endif

    
