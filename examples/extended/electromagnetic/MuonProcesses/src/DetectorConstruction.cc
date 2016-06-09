//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: DetectorConstruction.cc,v 1.1 2004/06/14 10:09:25 maire Exp $
// GEANT4 tag $Name: geant4-07-01 $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
:pBox(0), lBox(0), aMaterial(0)
{
  BoxSize = 1*m;
  DefineMaterials();
  SetMaterial("Iron");  
  detectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete detectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  //
  // define Elements
  //
  G4double z,a;
  
  G4Element* C  = new G4Element("Carbon"   ,"C" , z= 6., a=  12.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen" ,"N" , z= 7., a=  14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"   ,"O" , z= 8., a=  16.00*g/mole);
  G4Element* Ca = new G4Element("Calcium"  ,"Ca", z=20., a=  40.08*g/mole);
  
  //
  // define materials
  //
  G4double density;
  G4int ncomponents, natoms;
  G4double fractionmass;
    
  new G4Material("galactic", z=1., a= 1.01*g/mole, universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);
    
  G4Material* Air = 
  new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
  Air->AddElement(N, fractionmass=70.*perCent);
  Air->AddElement(O, fractionmass=30.*perCent);

  G4Material* CaCO3 = 
  new G4Material("CaCO3", density= 2.80*g/cm3, ncomponents=3);
  CaCO3->AddElement(Ca, natoms= 1);
  CaCO3->AddElement(C , natoms= 1);
  CaCO3->AddElement(O , natoms= 3);
   
  new G4Material("Carbon", z= 6., a= 12.01*g/mole, density= 2.265*g/cm3);   
  new G4Material("Iron"  , z=26., a= 55.85*g/mole, density= 7.870*g/cm3);
  new G4Material("Tin"   , z=50., a= 118.7*g/mole, density= 7.310*g/cm3);

  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  G4Box*
  sBox = new G4Box("Container",				//its name
                   BoxSize/2,BoxSize/2,BoxSize/2);	//its dimensions

  lBox = new G4LogicalVolume(sBox,			//its shape
                             aMaterial,			//its material
                             aMaterial->GetName());	//its name

  pBox = new G4PVPlacement(0,				//no rotation
  			   G4ThreeVector(),		//at (0,0,0)
                           lBox,			//its logical volume			   
                           aMaterial->GetName(),	//its name
                           0,				//its mother  volume
                           false,			//no boolean operation
                           0);				//copy number
			   
  PrintParameters();
  
  //always return the root volume
  //
  return pBox;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintParameters()
{
  G4cout << "\n The Box is " << G4BestUnit(BoxSize,"Length")
         << " of " << aMaterial->GetName() << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);
  if (pttoMaterial) aMaterial = pttoMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetSize(G4double value)
{
  BoxSize = value;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4RunManager.hh"

void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructVolumes());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......