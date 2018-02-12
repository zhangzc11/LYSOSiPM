//
// Created by psinclair on 26/10/16.
//

#ifndef LYSOSiPMPhysicsList_h
#define LYSOSiPMPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include "G4EmLivermorePolarizedPhysics.hh"

class G4VPhysicsConstructor;

class LYSOSiPMPhysicsList: public G4VModularPhysicsList
{
public:
    LYSOSiPMPhysicsList();
    virtual ~LYSOSiPMPhysicsList();

};


#endif
