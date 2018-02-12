
#include <G4SIunits.hh>
#include "LYSOSiPMSteppingAction.hh"
#include "LYSOSiPMEventAction.hh"
#include "LYSOSiPMDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"



LYSOSiPMSteppingAction::LYSOSiPMSteppingAction(
        const LYSOSiPMDetectorConstruction* detectorConstruction,
        LYSOSiPMEventAction* eventAction)
        : G4UserSteppingAction(),
          fDetConstruction(detectorConstruction),
          fEventAction(eventAction)
{
}


LYSOSiPMSteppingAction::~LYSOSiPMSteppingAction()
{
}



void LYSOSiPMSteppingAction::UserSteppingAction(const G4Step* step)
{
// Collect energy and track length step by step

    // get volume of the current step
    //i deleted the touchable handle bit. add back in if issues arise
    G4VPhysicalVolume* volume
            = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    // energy deposit
    G4double edep = step->GetTotalEnergyDeposit();
    G4double delPhi = step->GetPostStepPoint()->GetPolarization().deltaPhi(step->GetPreStepPoint()->GetPolarization());

    fEventAction->AddDeltaPhi(delPhi);

    isScattered = false;
    alreadyRecorded = false;

    if ( volume == fDetConstruction->GetCAbsorberPV() ) {
        fEventAction->AddAbsC(edep);

    }

   }







