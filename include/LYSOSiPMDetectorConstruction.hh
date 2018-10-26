//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: LYSOSiPMDetectorConstruction.hh 75215 2013-10-29 16:07:06Z gcosmo $
// 
/// \file LYSOSiPMDetectorConstruction.hh
/// \brief Definition of the LYSOSiPMDetectorConstruction class

#ifndef LYSOSiPMDetectorConstruction_h
#define LYSOSiPMDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

//#include "G4SystemOfUnits.hh"

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

//constants 

const G4double crystal_thick = 4.0 ;
const G4double SiPM_size = 3.0;
const G4double LYSO_sizeX = 8.0;
const G4double LYSO_sizeY = 8.0;


/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class LYSOSiPMDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    LYSOSiPMDetectorConstruction();
    virtual ~LYSOSiPMDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // get methods
    //
    const G4VPhysicalVolume* GetCAbsorberPV() const;

    const G4VPhysicalVolume* GetGapPV() const;
    const G4VPhysicalVolume* GetGelPV() const;
    const G4VPhysicalVolume* GetResinPV() const;

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();

    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger;
                                      // magnetic field messenger
    G4VPhysicalVolume*   cAbsorberPV; // the absorber physical volume
    G4VPhysicalVolume*	 gelPV;
    G4VPhysicalVolume*	 resinPV;
    G4VPhysicalVolume*   cFoilPV;
    G4VPhysicalVolume*   gapPV;      // the gap physical volume
    //G4VPhysicalVolume*   gap2PV;      // the gap physical volume

    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps
};

// inline functions

inline const G4VPhysicalVolume* LYSOSiPMDetectorConstruction::GetCAbsorberPV() const {
  return cAbsorberPV;
}


inline const G4VPhysicalVolume* LYSOSiPMDetectorConstruction::GetGapPV() const  {
  return gapPV;
}

inline const G4VPhysicalVolume* LYSOSiPMDetectorConstruction::GetGelPV() const  {
  return gelPV;
}

inline const G4VPhysicalVolume* LYSOSiPMDetectorConstruction::GetResinPV() const  {
  return resinPV;
}


#endif

