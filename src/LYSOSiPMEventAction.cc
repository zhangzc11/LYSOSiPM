

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
          deltaPhi(0.)

{}


LYSOSiPMEventAction::~LYSOSiPMEventAction() {}


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
    // get analysis manager
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    // fill histograms
    if(cEnergyAbs > 0) analysisManager->FillH1(0, cEnergyAbs);
    if(scattered && recorded) analysisManager->FillH1(1, scatAng);
    if(scattered) analysisManager->FillH1(2, scatPhi);
    if(scattered) analysisManager->FillH1(3, deltaPhi);

    // fill ntuple
    if(cEnergyAbs > 0) analysisManager->FillNtupleDColumn(0, cEnergyAbs);
    analysisManager->FillNtupleDColumn(1, scatAng);
    analysisManager->AddNtupleRow();

}




