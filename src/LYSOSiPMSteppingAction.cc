
#include <G4SIunits.hh>
#include "LYSOSiPMSteppingAction.hh"
#include "LYSOSiPMEventAction.hh"
#include "LYSOSiPMDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4StepPoint.hh"
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

	if (volume == fDetConstruction->GetGelPV())
	{
		bool isOpticalPhoton = false;
		if(step->GetTrack()->GetParticleDefinition()->GetParticleType() == "opticalphoton") isOpticalPhoton = true;
		//photon arrives at the optical grease
		G4StepPoint* point1 = step->GetPreStepPoint();

		//just entered the boundary
		if (point1->GetStepStatus() == fGeomBoundary && isOpticalPhoton) 
		{
			G4int isCerenkovLight = 0;
			if(step->GetTrack()->GetCreatorProcess()->GetProcessName() == "Cerenkov") isCerenkovLight = 1;
			fEventAction->AddPhoton(point1->GetGlobalTime(), point1->GetLocalTime(), step->GetTrack()->GetTrackLength(), step->GetTrack()->GetVertexPosition().x(), step->GetTrack()->GetVertexPosition().y(), step->GetTrack()->GetVertexPosition().z(), step->GetTrack()->GetTotalEnergy(), isCerenkovLight);
		}
	}

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







