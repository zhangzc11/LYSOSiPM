

#include "LYSOSiPMActionInitialization.hh"
#include "LYSOSiPMPrimaryGeneratorAction.hh"
#include "LYSOSiPMRunAction.hh"
#include "LYSOSiPMEventAction.hh"
#include "LYSOSiPMSteppingAction.hh"
#include "LYSOSiPMDetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LYSOSiPMActionInitialization::LYSOSiPMActionInitialization
                            (LYSOSiPMDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}



LYSOSiPMActionInitialization::~LYSOSiPMActionInitialization()
{}



void LYSOSiPMActionInitialization::BuildForMaster() const
{
  LYSOSiPMEventAction* eventAction = new LYSOSiPMEventAction;
  SetUserAction(new LYSOSiPMRunAction(eventAction));
}



void LYSOSiPMActionInitialization::Build() const
{
  SetUserAction(new LYSOSiPMPrimaryGeneratorAction);
  
  auto eventAction = new LYSOSiPMEventAction;
  SetUserAction(eventAction);

  SetUserAction(new LYSOSiPMRunAction(eventAction));

  SetUserAction(new LYSOSiPMSteppingAction(fDetConstruction,eventAction));
}  


