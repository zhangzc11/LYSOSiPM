

#include <G4SubtractionSolid.hh>
#include "LYSOSiPMDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"


G4ThreadLocal
G4GlobalMagFieldMessenger *LYSOSiPMDetectorConstruction::fMagFieldMessenger = 0;


LYSOSiPMDetectorConstruction::LYSOSiPMDetectorConstruction()
        : G4VUserDetectorConstruction(),
          cAbsorberPV(0),

          cFoilPV(0),

          fGapPV(0),
          fCheckOverlaps(true) {
}


LYSOSiPMDetectorConstruction::~LYSOSiPMDetectorConstruction() {
}


G4VPhysicalVolume *LYSOSiPMDetectorConstruction::Construct() {
    // Define materials
    DefineMaterials();

    // Define volumes
    return DefineVolumes();
}



void LYSOSiPMDetectorConstruction::DefineMaterials() {

    G4NistManager *nist = G4NistManager::Instance();
    G4bool isotopes = false;

    nist->FindOrBuildMaterial("G4_AIR");
    G4double density = 2.700*g/cm3, a = 26.98*g/mole;

    G4Element*  Al = nist->FindOrBuildElement("Al" , isotopes);
    G4Material* Aluminium = new G4Material("Al", density, 1);
    Aluminium->AddElement(Al, 1);

	G4int ncomponents;
	G4double prelude_density = 7.4*g/cm3;
	G4Material* prelude = new G4Material("prelude", prelude_density, ncomponents=4);
	prelude->AddElement(nist->FindOrBuildElement("Lu"),71*perCent);
	prelude->AddElement(nist->FindOrBuildElement("Si"),7*perCent);
	prelude->AddElement(nist->FindOrBuildElement("O"), 18*perCent);
	prelude->AddElement(nist->FindOrBuildElement("Y"), 4*perCent);

	G4Material* scintillator = new G4Material("scintillator", prelude_density ,ncomponents=2);
	scintillator->AddMaterial(prelude,99.81*perCent);
	scintillator->AddElement(nist->FindOrBuildElement("Ce"), 0.19*perCent);

	G4MaterialPropertiesTable *mpt = new G4MaterialPropertiesTable();

	const G4int num = 20;
	G4double ene[num]   =  {1.79*eV, 1.85*eV, 1.91*eV, 1.97*eV,
			2.04*eV, 2.11*eV, 2.19*eV, 2.27*eV,
			2.36*eV, 2.45*eV, 2.56*eV, 2.67*eV,
			2.80*eV, 2.94*eV, 3.09*eV, 3.25*eV,
			3.44*eV, 3.65*eV, 3.89*eV, 4.16*eV};
	G4double fast[num]  =  {0.01, 0.10, 0.20, 0.50,
			0.90, 1.70, 2.90, 5.00,
			8.30, 12.5, 17.0, 22.9,
			26.4, 25.6, 16.8, 4.20,
			0.30, 0.20, 0.10, 0.01};
	G4double rLyso[num] =  {1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81,
			1.81, 1.81, 1.81, 1.81};
	G4double abs[num]   =  {3.5*m, 3.5*m, 3.5*m, 3.5*m,
			3.5*m, 3.5*m, 3.5*m, 3.5*m,
			3.5*m, 3.5*m, 3.5*m, 3.5*m,
			3.5*m, 3.5*m, 3.5*m, 3.5*m,
			3.5*m, 3.5*m, 3.5*m, 3.5*m};

	mpt->AddProperty("FASTCOMPONENT", ene, fast, num);
	mpt->AddProperty("RINDEX", ene, rLyso , num);
	mpt->AddProperty("ABSLENGTH", ene, abs, num);
	mpt->AddConstProperty("SCINTILLATIONYIELD",32/keV);
	mpt->AddConstProperty("RESOLUTIONSCALE", 1);
	mpt->AddConstProperty("FASTTIMECONSTANT",41*ns);
	scintillator->SetMaterialPropertiesTable(mpt);

}


G4VPhysicalVolume *LYSOSiPMDetectorConstruction::DefineVolumes() {
    // Geometry parameters

    //World size
    G4double worldSizeXY = 4. * cm;
    G4double worldSizeZ = 4. * cm;

    //Crystal Parameters
    G4double cryst_dX = 12 * mm, cryst_dY = 12 * mm, cryst_dZ = 3 * mm;
    G4double foilThickness = 0.5 * mm;
    G4double outBox_dX = cryst_dX+foilThickness, outBox_dY = cryst_dY+foilThickness, outBox_dZ = cryst_dZ;


    // Get materials
    G4Material* defaultMaterial = G4Material::GetMaterial("G4_AIR");
    G4Material* cryst_mat = G4Material::GetMaterial("scintillator");
    G4Material* foil_mat = G4Material::GetMaterial("Al");

    //
    // World
    //
    G4VSolid *worldS
            = new G4Box("World",           // its name
                        worldSizeXY / 2, worldSizeXY / 2, worldSizeZ / 2); // its size

    G4LogicalVolume *worldLV
            = new G4LogicalVolume(
                    worldS,           // its solid
                    defaultMaterial,  // its material
                    "World");         // its name

    G4VPhysicalVolume *worldPV
            = new G4PVPlacement(
                    0,                // no rotation
                    G4ThreeVector(),  // at (0,0,0)
                    worldLV,          // its logical volume
                    "World",          // its name
                    0,                // its mother  volume
                    false,            // no boolean operation
                    0,                // copy number
                    fCheckOverlaps);  // checking overlaps

    //
    //Crystals wrapped in foil
    //
    G4double gap = 0. * mm;        //a gap for wrapping
    //Foil wrapping
    G4Box* outerBox = new G4Box("Outerbox", outBox_dX/2, outBox_dY/2, outBox_dZ/2);
    G4Box* innerBox = new G4Box("Innerbox", cryst_dX/2, cryst_dY/2, cryst_dZ/2+5*mm);

    G4SubtractionSolid* foilS = new G4SubtractionSolid("Foilwrapping", outerBox, innerBox);

    G4Box* crystalS = new G4Box("crystal", cryst_dX/2, cryst_dY/2, cryst_dZ/2);

    G4LogicalVolume* crystalLV
            = new G4LogicalVolume(
                    crystalS,     // its solid
                    cryst_mat,  // its material
                    "lysoCrystal");   // its name

    G4LogicalVolume* foilLV
            = new G4LogicalVolume(
                    foilS,     // its solid
                    foil_mat,  // its material
                    "foilwrap");   // its name

    cAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(),  // at (0,0,0)
            crystalLV,          // its logical volume
            "crystalPV",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            0,                // copy number
            fCheckOverlaps);  // checking overlaps
    cFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(),
            foilLV,
            "foilPV",
            worldLV,
            false,
            0,
            fCheckOverlaps);

    worldLV->SetVisAttributes(G4VisAttributes::Invisible);

    G4VisAttributes *simpleBoxVisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));
    simpleBoxVisAtt->SetVisibility(true);
    crystalLV->SetVisAttributes(simpleBoxVisAtt);

    //
    // Always return the physical World
    //
    return worldPV;
}


void LYSOSiPMDetectorConstruction::ConstructSDandField() {
   
  G4ThreeVector fieldValue = G4ThreeVector(0,0,0);
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);

  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

