#include <stdlib.h>
#include <time.h>

#include <G4SIunits.hh>
#include "LYSOSiPMSteppingAction.hh"
#include "LYSOSiPMEventAction.hh"
#include "LYSOSiPMDetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4SteppingManager.hh"
#include "G4StepPoint.hh"
#include "G4RunManager.hh"


LYSOSiPMSteppingAction::LYSOSiPMSteppingAction(
        const LYSOSiPMDetectorConstruction* detectorConstruction,
        LYSOSiPMEventAction* eventAction)
        : G4UserSteppingAction(),
          fDetConstruction(detectorConstruction),
          fEventAction(eventAction)
{
	srand (time(NULL));
}


LYSOSiPMSteppingAction::~LYSOSiPMSteppingAction()
{
}


void LYSOSiPMSteppingAction::UserSteppingAction(const G4Step* step)
{
	// Collect energy and track length step by step
	
	//the track of the step	
	G4Track* theTrack = step->GetTrack () ;

    // get volume of the current step
	G4StepPoint * thePrePoint  = step->GetPreStepPoint () ;
	G4StepPoint * thePostPoint = step->GetPostStepPoint () ;
	G4VPhysicalVolume * thePrePV  = thePrePoint->GetPhysicalVolume () ;
	G4VPhysicalVolume * thePostPV = thePostPoint->GetPhysicalVolume () ;
	G4String thePrePVName  = "" ; if ( thePrePV )  thePrePVName  = thePrePV  -> GetName () ;
	G4String thePostPVName = "" ; if ( thePostPV ) thePostPVName = thePostPV -> GetName () ;
	
	//what kind of particle the step is
	bool isOpticalPhoton = false;
	if(step->GetTrack()->GetParticleDefinition()->GetParticleType() == "opticalphoton") isOpticalPhoton = true;

	if(isOpticalPhoton)
	{
		G4int isCerenkovLight = 0;
		if(step->GetTrack()->GetCreatorProcess()->GetProcessName() == "Cerenkov") isCerenkovLight = 1;
		G4int isScintillation = 0;
		if(step->GetTrack()->GetCreatorProcess()->GetProcessName() == "Scincilattion") isScintillation = 1;

		//get the current step number
		G4int nStep = theTrack -> GetCurrentStepNumber();
		
		//count the number of generated Scintillaiton photons
		
		if(theTrack->GetLogicalVolumeAtVertex()->GetName() == "Crystal" && nStep == 1 && isScintillation == 1 && thePrePVName == "Crystal")
		{
			fEventAction->CountScintillationPhotonGen();
		}

		if(theTrack->GetLogicalVolumeAtVertex()->GetName() == "Crystal" && nStep == 1 && isCerenkovLight == 1 && thePrePVName == "Crystal")
		{
			fEventAction->CountCerenkovPhotonGen();
		}
		
		//count the photons that enters the SiPM
		if (thePostPVName == "resinSiPM" && theTrack->GetLogicalVolumeAtVertex()->GetName() == "Crystal"  && (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption") && isScintillation == 1)
		{
			fEventAction->CountScintillationPhotonCollect();
		}
		if (thePostPVName == "resinSiPM" && theTrack->GetLogicalVolumeAtVertex()->GetName() == "Crystal"  && (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption") && isCerenkovLight == 1)
		{
			fEventAction->CountCerenkovPhotonCollect();
		}

		//photoelectrons in SiPM
		//PDE: 20%
		float rd_01 = (rand()*0.001)/(0.001*RAND_MAX);
		
		//if (thePostPVName == "resinSiPM" && theTrack->GetLogicalVolumeAtVertex()->GetName() == "Crystal" && thePrePVName == "opticalGel" && (theTrack->GetTrackStatus() != fAlive))
		//if (thePostPVName == "resinSiPM" && theTrack->GetLogicalVolumeAtVertex()->GetName() == "Crystal"  && (theTrack->GetTrackStatus() != fAlive))
		if (thePostPVName == "resinSiPM" && theTrack->GetLogicalVolumeAtVertex()->GetName() == "Crystal"  && (thePostPoint->GetProcessDefinedStep()->GetProcessName() == "OpAbsorption") && rd_01<0.2)
		{
		fEventAction->AddPhoton(thePrePoint->GetGlobalTime(), thePrePoint->GetLocalTime(), step->GetTrack()->GetTrackLength(), step->GetTrack()->GetVertexPosition().x(), step->GetTrack()->GetVertexPosition().y(), step->GetTrack()->GetVertexPosition().z(), step->GetTrack()->GetTotalEnergy(), isCerenkovLight);
		}
	}

    // energy deposit
    G4double edep = step->GetTotalEnergyDeposit();
    G4double delPhi = step->GetPostStepPoint()->GetPolarization().deltaPhi(step->GetPreStepPoint()->GetPolarization());

    fEventAction->AddDeltaPhi(delPhi);

    if ( thePrePVName == "Crystal" ){
        fEventAction->AddAbsC(edep);
    }

   }







