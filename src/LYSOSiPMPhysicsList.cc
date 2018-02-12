#include "LYSOSiPMPhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"


LYSOSiPMPhysicsList::LYSOSiPMPhysicsList()
        : G4VModularPhysicsList(){
    SetVerboseLevel(1);

    // Default physics
    RegisterPhysics(new G4DecayPhysics());

    // Radioactive decay
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    //Polarised EM physics
    RegisterPhysics(new G4EmLivermorePolarizedPhysics());
}



LYSOSiPMPhysicsList::~LYSOSiPMPhysicsList()
{
}
