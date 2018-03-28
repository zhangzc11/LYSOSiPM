

#include "LYSOSiPMDetectorConstruction.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Paraboloid.hh"
#include "G4RotationMatrix.hh"
#include "G4UnionSolid.hh"
#include <G4SubtractionSolid.hh>
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
	//mpt->AddProperty("ABSLENGTH", ene, abs, num);
	mpt->AddConstProperty("SCINTILLATIONYIELD",32.0/keV);
	//mpt->AddConstProperty("SCINTILLATIONYIELD",4/keV);//mimic SiPM pde
	mpt->AddConstProperty("RESOLUTIONSCALE", 1);
	mpt->AddConstProperty("FASTTIMECONSTANT",41.0*ns);
	scintillator->SetMaterialPropertiesTable(mpt);

	//use Marco's absorption length: https://github.com/marco-toli/TB_timing/blob/3f99f77d68aa1c1d395b388e4e509dac17de7211/src/MyMaterials.cc#L2041
	const G4int nEntries_ABS = 85;
	G4double PhotonEnergy_ABS[nEntries_ABS] =
    { 4.42857*eV, 4.35088*eV, 4.27586*eV, 4.20339*eV, 4.13333*eV, 4.06557*eV, 4*eV, 3.93651*eV, 3.875*eV, 3.81538*eV,
      3.75758*eV, 3.70149*eV, 3.64706*eV, 3.5942*eV, 3.54286*eV, 3.49296*eV, 3.44444*eV, 3.39726*eV, 3.35135*eV,
      3.30667*eV, 3.26316*eV, 3.22078*eV, 3.17949*eV, 3.13924*eV, 3.1*eV, 3.06173*eV, 3.02439*eV, 2.98795*eV,
      2.95238*eV, 2.91765*eV, 2.88372*eV, 2.85057*eV, 2.81818*eV, 2.78652*eV, 2.75556*eV, 2.72527*eV, 2.69565*eV,
      2.66667*eV, 2.6383*eV, 2.61053*eV, 2.58333*eV, 2.5567*eV, 2.53061*eV, 2.50505*eV, 2.48*eV, 2.45545*eV,
      2.43137*eV, 2.40777*eV, 2.38462*eV, 2.3619*eV, 2.33962*eV, 2.31776*eV, 2.2963*eV, 2.27523*eV, 2.25455*eV,
      2.23423*eV, 2.21429*eV, 2.19469*eV, 2.17544*eV, 2.15652*eV, 2.13793*eV, 2.11966*eV, 2.10169*eV, 2.08403*eV,
      2.06667*eV, 2.04959*eV, 2.03279*eV, 2.01626*eV, 2*eV, 1.984*eV, 1.96825*eV, 1.95276*eV, 1.9375*eV, 1.92248*eV,
      1.90769*eV, 1.89313*eV, 1.87879*eV, 1.86466*eV, 1.85075*eV, 1.83704*eV, 1.82353*eV, 1.81022*eV, 1.7971*eV, 1.78417*eV, 1.0*eV
    };

	G4double Absorption[nEntries_ABS] =
    { 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm,
      0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm, 0.*mm,
      0.5*mm, 0.93828*mm, 1.92292*mm, 3.19852*mm, 7.84337*mm, 19.4627*mm, 43.2508*mm, 90.9185*mm, 161.725*mm,
      267.35*mm, 325.724*mm, 369.759*mm, 527.641*mm, 433.773*mm, 451.487*mm, 510.549*mm, 352.191*mm, 432.319*mm,
      499.728*mm, 416.34*mm, 433.836*mm, 580.102*mm, 434.027*mm, 469.628*mm, 458.186*mm, 500.534*mm, 487.4*mm,
      426.389*mm, 486.997*mm, 451.24*mm, 500.008*mm, 500.425*mm, 500.712*mm, 470.476*mm, 475.17*mm, 500.267*mm,
      493.917*mm, 500.192*mm, 507.001*mm, 544.182*mm, 500.366*mm, 500.553*mm, 500.793*mm, 500.08*mm, 500.38*mm,
      451.895*mm, 500.089*mm, 500.602*mm, 500.547*mm, 500.33*mm, 500.171*mm, 500.461*mm, 500.85*mm, 500.493*mm,
      500.18*mm, 500.011*mm, 500.956*mm, 500.05*mm, 500.495*mm, 500.982*mm, 500.846*mm, 500.64*mm, 500.212*mm,
      500.801*mm, 500.457*mm, 500.729*mm, 500.8*mm
	};
	mpt->AddProperty("ABSLENGTH", PhotonEnergy_ABS, Absorption, nEntries_ABS);

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
	G4double gel_dX = 4 * mm, gel_dY = 4 * mm, gel_dZ = 1 * mm;

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
	//1. parabola part
	G4Paraboloid * crystalS_p1 = new G4Paraboloid("crystalS_p1", 0.9*mm, 0.0*mm, 6.0*mm);
	G4Box* crystalS_p2 = new G4Box("crystalS_p2", cryst_dX/2, cryst_dY/2, cryst_dZ/2);
	G4RotationMatrix rotm  = G4RotationMatrix();
	G4ThreeVector  translation(0, 0, -2.4*mm);

	//G4UnionSolid* crystalS = new G4UnionSolid("crystalBox", crystalS_p2, crystalS_p1, &rotm, translation);

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

