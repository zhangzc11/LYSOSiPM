

#ifndef LYSOSiPMEventAction_h
#define LYSOSiPMEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

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
	void AddPhoTime(G4double time);

private:
    G4double cEnergyAbs;
    G4double scatAng;
    G4double scatPhi;
    G4double deltaPhi;
    G4bool scattered;
    G4bool recorded;
	std::vector<G4double> * allPhoTime;
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

    
