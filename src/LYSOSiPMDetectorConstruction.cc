

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

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

G4ThreadLocal
G4GlobalMagFieldMessenger *LYSOSiPMDetectorConstruction::fMagFieldMessenger = 0;


LYSOSiPMDetectorConstruction::LYSOSiPMDetectorConstruction()
        : G4VUserDetectorConstruction(),
          cAbsorberPV(0),
		  gelPV(0),
          cFoilPV(0),
          cFoil2PV(0),
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

	

	//ALuminium wrap
	G4double density = 2.700*g/cm3;// a = 26.98*g/mole;
    G4Element*  Al = nist->FindOrBuildElement("Al" , isotopes);
    G4Material* Aluminium = new G4Material("Al", density, 1);
    Aluminium->AddElement(Al, 1);

	//LYSO
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
	G4double abs[num]   =  {0.413*m, 0.413*m, 0.413*m, 0.413*m,
			0.413*m, 0.413*m, 0.413*m, 0.413*m,
			0.413*m, 0.413*m, 0.413*m, 0.413*m,
			0.413*m, 0.413*m, 0.413*m, 0.413*m,
			0.413*m, 0.413*m, 0.413*m, 0.413*m};

	mpt->AddProperty("FASTCOMPONENT", ene, fast, num);
	mpt->AddProperty("RINDEX", ene, rLyso , num);
	mpt->AddProperty("ABSLENGTH", ene, abs, num);
	mpt->AddConstProperty("SCINTILLATIONYIELD",32/keV);
	//mpt->AddConstProperty("SCINTILLATIONYIELD",4/keV);//mimic SiPM pde
	mpt->AddConstProperty("RESOLUTIONSCALE", 1);
	mpt->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	scintillator->SetMaterialPropertiesTable(mpt);

	//air
    G4Material* Air  =  nist->FindOrBuildMaterial("G4_AIR");
	G4double rAir[num] =  {1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00,
			1.00, 1.00, 1.00, 1.00};
	G4MaterialPropertiesTable* mptAir = new G4MaterialPropertiesTable();
	mptAir->AddProperty("RINDEX",ene,rAir,num);
	Air->SetMaterialPropertiesTable(mptAir);

	//optical grease
	std::vector<G4int> natoms;
	std::vector<G4String> elements;
	elements.push_back("C");     natoms.push_back(2);
	elements.push_back("H");     natoms.push_back(6);
	elements.push_back("Si");    natoms.push_back(1);
	elements.push_back("O");     natoms.push_back(1);

	G4double silicone_density = 1.060*g/cm3;
	G4Material* fSilicone = nist->ConstructNewMaterial("Silicone", elements, natoms, silicone_density);
	elements.clear();
	natoms.clear();

	G4double rSilicone[num] =  {1.50, 1.50, 1.50, 1.50,
			1.50, 1.50, 1.50, 1.50,
			1.50, 1.50, 1.50, 1.50,
			1.50, 1.50, 1.50, 1.50,
			1.50, 1.50, 1.50, 1.50};
	G4double absGrease[num]   =  {0.10*mm, 0.10*mm, 0.10*mm, 0.10*mm,
			0.10*mm, 0.10*mm, 0.10*mm, 0.10*mm,
			0.10*mm, 0.10*mm, 0.10*mm, 0.10*mm,
			0.10*mm, 0.10*mm, 0.10*mm, 0.10*mm,
			0.10*mm, 0.10*mm, 0.10*mm, 0.10*mm};

	G4MaterialPropertiesTable* mptSilicone = new G4MaterialPropertiesTable();
	mptSilicone->AddProperty("RINDEX",ene,rSilicone,num);
	mptSilicone->AddProperty("ABSLENGTH",ene,absGrease,num);
	fSilicone->SetMaterialPropertiesTable(mptSilicone);

	//teflon wrap
	elements.push_back("C");     natoms.push_back(2);
	elements.push_back("F");     natoms.push_back(4);
	G4double teflon_density = 2.2*g/cm3;
	G4Material* fteflon = nist->ConstructNewMaterial("teflon", elements, natoms, teflon_density);
	const G4int num2 = 2;
	G4double ene2[num2]   =  {2.0*eV, 3.5*eV};
	G4double ref2[num2]   =  {1.0, 1.0};
	G4double eff2[num2]   =  {0.0, 0.0};
    G4MaterialPropertiesTable* mpt_teflon = new G4MaterialPropertiesTable();
	mpt_teflon->AddProperty("REFLECTIVITY",ene2,ref2,num2);
    mpt_teflon->AddProperty("EFFICIENCY",ene2,eff2,num2);
	fteflon->SetMaterialPropertiesTable(mpt_teflon);	
}


G4VPhysicalVolume *LYSOSiPMDetectorConstruction::DefineVolumes() {
    // Geometry parameters

    //World size
    G4double worldSizeXY = 4. * cm;
    G4double worldSizeZ = 4. * cm;

    //Crystal Parameters
    G4double cryst_dX = 12 * mm, cryst_dY = 12 * mm, cryst_dZ = 3 * mm;
	G4double gel_dX = 3 * mm, gel_dY = 3 * mm, gel_dZ = 1 * mm;

    G4double foilThickness = 0.5 * mm;
    G4double gapThickness = 0.0 * mm; //air gap for wrapping

    //G4double gapOut_dX = cryst_dX+gapThickness, gapOut_dY = cryst_dY+gapThickness*2, gapOut_dZ = cryst_dZ+gapThickness*2;

    G4double foilOut_dX = cryst_dX+foilThickness*2+gapThickness*2, foilOut_dY = cryst_dY+foilThickness*2+gapThickness*2, foilOut_dZ = cryst_dZ+foilThickness*2+gapThickness*2;


    // Get materials
    G4Material* air_mat = G4Material::GetMaterial("G4_AIR");
    G4Material* cryst_mat = G4Material::GetMaterial("scintillator");
    G4Material* gel_mat = G4Material::GetMaterial("Silicone");
    G4Material* foil_mat = G4Material::GetMaterial("teflon");

    //
    // World
    //
    G4VSolid *worldS
            = new G4Box("World",           // its name
                        worldSizeXY / 2, worldSizeXY / 2, worldSizeZ / 2); // its size

    G4LogicalVolume *worldLV
            = new G4LogicalVolume(
                    worldS,           // its solid
                    air_mat,  // its material
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

	//crystal
    G4Box* crystalS = new G4Box("crystalBox", cryst_dX/2, cryst_dY/2, cryst_dZ/2);
    G4LogicalVolume* crystalLV
            = new G4LogicalVolume(
                    crystalS,     // its solid
                    cryst_mat,  // its material
                    "Crystal");   // its name

	cAbsorberPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(),  // at (0,0,0)
            crystalLV,          // its logical volume
            "Crystal",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            0,                // copy number
            fCheckOverlaps);  // checking overlaps
	//silicon gel for the couple between crystal and SiPM
	G4Box* gelS = new G4Box("opticalGel", gel_dX/2, gel_dY/2, gel_dZ/2);
	G4LogicalVolume* gelLV
			= new G4LogicalVolume(
                     gelS,     // its solid
                     gel_mat,  // its material
                     "opticalGel");   // its name
	gelPV
            = new G4PVPlacement(
            0,                // no rotation
            G4ThreeVector(0, 0, cryst_dZ/2 + gel_dZ/2),  // its position
            gelLV,          // its logical volume
            "opticalGel",    // its name
            worldLV,          // its mother  volume
            false,            // no boolean operation
            0,                // copy number
            fCheckOverlaps);  // checking overlaps

	//surface between crystal and air
	G4OpticalSurface* OpLYSOSurface = new G4OpticalSurface("LYSOSurface");
	OpLYSOSurface->SetModel(glisur);
	OpLYSOSurface->SetType(dielectric_dielectric);
	OpLYSOSurface->SetFinish(ground);
	OpLYSOSurface->SetPolish(1.0);
	//G4LogicalBorderSurface* LYSOSurface = new G4LogicalBorderSurface("LYSOSurface", cAbsorberPV, worldPV, OpLYSOSurface);

	/*
	//gap
	G4Box* gelBox = new G4Box("opticalGel", gel_dX/2, gel_dY/2, gel_dZ/2 + cryst_dZ/2);
    G4Box* crystalBox = new G4Box("Innerbox", cryst_dX/2, cryst_dY/2, cryst_dZ/2);

	G4Box* gapBox = new G4Box("Outerbox", gapOut_dX/2, gapOut_dY/2, gapOut_dZ/2);

    G4SubtractionSolid* gapS_withGel = new G4SubtractionSolid("Foilwrapping_withGel", gapBox, crystalBox);
    G4SubtractionSolid* gapS = new G4SubtractionSolid("Foilwrapping", gapS_withGel, gelBox);

	G4LogicalVolume* gapLV
            = new G4LogicalVolume(
                    gapS,     // its solid
                    air_mat,  // its material
                    "airgap");   // its name
	gapPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(),
            gapLV,
            "airgap",
            worldLV,
            false,
            0,
            fCheckOverlaps);

	G4Box* gap2Box = new G4Box("gapBox2", gel_dX/2, gel_dY/2, gapThickness/2);

	G4LogicalVolume* gap2LV
            = new G4LogicalVolume(
                    gap2Box,     // its solid
                    air_mat,  // its material
                    "airgap2");   // its name
	gap2PV
            = new G4PVPlacement(
            0,
            G4ThreeVector(0, 0, - cryst_dZ/2 - gapThickness/2),
            gap2LV,
            "airgap2",
            worldLV,
            false,
            0,
            fCheckOverlaps);
	*/


	/*
	//foil
	G4Box* foilBox = new G4Box("Outerbox", foilOut_dX/2, foilOut_dY/2, foilOut_dZ/2);
    //G4SubtractionSolid* foilS_withgel = new G4SubtractionSolid("Foilwrapping_withgel", foilBox, gapBox);
    //G4SubtractionSolid* foilS = new G4SubtractionSolid("Foilwrapping_withgel", foilS_withgel, gelBox);
    G4SubtractionSolid* foilS_withgel = new G4SubtractionSolid("Foilwrapping_withgel", foilBox, crystalBox);
    G4SubtractionSolid* foilS = new G4SubtractionSolid("Foilwrapping_withgel", foilS_withgel, gelBox);

    G4LogicalVolume* foilLV
            = new G4LogicalVolume(
                    foilS,     // its solid
                    foil_mat,  // its material
                    "foilwrap");   // its name
	cFoilPV
            = new G4PVPlacement(
            0,
            G4ThreeVector(),
            foilLV,
            "foilwrap",
            worldLV,
            false,
            0,
            fCheckOverlaps);
	
	G4Box* foil2Box = new G4Box("foilBox2", gel_dX/2, gel_dY/2, foilThickness/2);

	G4LogicalVolume* foil2LV
            = new G4LogicalVolume(
                    foil2Box,     // its solid
                    foil_mat,  // its material
                    "foilwrap2");   // its name
	cFoil2PV
            = new G4PVPlacement(
            0,
            G4ThreeVector(0, 0, - cryst_dZ/2 - gapThickness - foilThickness/2),
            foil2LV,
            "foilwrap2",
            worldLV,
            false,
            0,
            fCheckOverlaps);
	
	*/
	//
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

