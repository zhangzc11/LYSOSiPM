

#include "LYSOSiPMPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4Box.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"

LYSOSiPMPrimaryGeneratorAction::LYSOSiPMPrimaryGeneratorAction()
        : G4VUserPrimaryGeneratorAction(),
          fParticleGun(0)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);

  // default particle kinematic
  //
  G4ParticleDefinition* particleDefinition
          = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.0));
  fParticleGun->SetParticleEnergy(100.0*keV);
  //fParticleGun->SetParticlePosition(G4ThreeVector(0.0*mm,0.0*mm,0.0*mm)); //this one doesn't work at all
}


LYSOSiPMPrimaryGeneratorAction::~LYSOSiPMPrimaryGeneratorAction()
{
	delete fParticleGun;
}



void LYSOSiPMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // This function is called at the begining of event

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get world volume
  // from G4LogicalVolumeStore
  //
  G4double worldZHalfLength = 0;
  G4LogicalVolume* worldLV
          = G4LogicalVolumeStore::GetInstance()->GetVolume("World");
  G4Box* worldBox = 0;
  if ( worldLV) worldBox = dynamic_cast< G4Box*>(worldLV->GetSolid());
  if ( worldBox ) {
    worldZHalfLength = worldBox->GetZHalfLength();
  }
  else  {
    G4ExceptionDescription msg;
    msg << "World volume of box not found." << G4endl;
    msg << "Perhaps you have changed geometry." << G4endl;
    msg << "The gun will be place in the center.";
    G4Exception("LYSOSiPMPrimaryGeneratorAction::GeneratePrimaries()",
                "MyCode0002", JustWarning, msg);
  }

  // Set gun position
  //fParticleGun->SetParticlePosition(G4ThreeVector(2., 0., -worldZHalfLength));

  fParticleGun->GeneratePrimaryVertex(anEvent);

 }


