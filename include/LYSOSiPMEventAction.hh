

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
const G4double digi_step = 0.01;//in ns
const G4int kDet = 1;
const G4int NSaveMax = 9999;
const G4double grease_x = 0.0;
const G4double grease_y = 0.0;
const G4double grease_z = 1.5;//mm

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
	void AddPhoton(G4double time, G4double time_local, G4double trackLength, G4double trackVertexX, G4double trackVertexY, G4double trackVertexZ);
	std::vector<G4double> & GetTimeArray(){ return fTime;}
	std::vector<G4double> & GetAmpArray(){ return fAmp;}
	
	std::vector<G4double> & GetPhoTimeArray(){ return allPhoTime_save;}
	std::vector<G4int> & GetPhoIndexArray(){ return allPhoIndex_save;}
	std::vector<G4double> & GetPhoTimeLocalArray(){ return allPhoTimeLocal_save;}
	std::vector<G4double> & GetPhoTrackLengthArray(){ return allPhoTrackLength_save;}
	std::vector<G4double> & GetPhoTrackVertexXArray(){ return allPhoTrackVertexX_save;}
	std::vector<G4double> & GetPhoTrackVertexYArray(){ return allPhoTrackVertexY_save;}
	std::vector<G4double> & GetPhoTrackVertexZArray(){ return allPhoTrackVertexZ_save;}
	std::vector<G4double> & GetPhoTrackVertexRArray(){ return allPhoTrackVertexR_save;}

private:
    G4double cEnergyAbs;
    G4double scatAng;
    G4double scatPhi;
    G4double deltaPhi;
    G4bool scattered;
    G4bool recorded;
	
	std::vector<G4double> allPhoTime;
	std::vector<G4double> allPhoTimeLocal;
	std::map<G4double, G4int> time_index;
	std::vector<G4double> allPhoTime_save;
	std::vector<G4int> allPhoIndex_save;
	std::vector<G4double> allPhoTimeLocal_save;
	std::vector<G4double> allPhoTrackLength;
	std::vector<G4double> allPhoTrackLength_save;
	std::vector<G4double> allPhoTrackVertexX;
	std::vector<G4double> allPhoTrackVertexX_save;
	std::vector<G4double> allPhoTrackVertexY;
	std::vector<G4double> allPhoTrackVertexY_save;
	std::vector<G4double> allPhoTrackVertexZ;
	std::vector<G4double> allPhoTrackVertexZ_save;
	std::vector<G4double> allPhoTrackVertexR_save;
	std::vector<G4double> fTime;
	std::vector<G4double> fAmp;

	G4int photonIndex;
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

    
