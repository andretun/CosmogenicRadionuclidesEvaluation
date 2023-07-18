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
// Oct/2022  A. Antonione
//
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"


DetectorConstruction::DetectorConstruction()
:G4VUserDetectorConstruction(),
 fMaterial(0), fLAbsor(0), fPAbsor(0), meteoriteMaterial(0),  fWorldMat(0), fPWorld(0), fDetectorMessenger(0)
{
  fRadius = 241*m;  // Default value - it can be changed in a Macro
  fWorldSize = 1.01*fRadius;
  DefineMaterials();
  SetMaterial("Meteorite");  
  fDetectorMessenger = new DetectorMessenger(this);
}


DetectorConstruction::~DetectorConstruction()
{
  delete fDetectorMessenger;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}


void DetectorConstruction::DefineMaterials()
{
  // specific element name for thermal neutronHP
  // (see G4ParticleHPThermalScatteringNames.cc)

  // Manager for the elements
  G4NistManager *nistman = G4NistManager::Instance();
  
  
  // Meteorite material - bulk composition
  meteoriteMaterial = new G4Material("Meteorite", 1.194*g/cm3, 21);
  
  G4Element *elH = nistman->FindOrBuildElement("H");
  meteoriteMaterial->AddElement(elH, 1.15*perCent);
  
  G4Element *elC = nistman->FindOrBuildElement("C");
  meteoriteMaterial->AddElement(elC, 2.32*perCent);
  
  G4Element *elN = nistman->FindOrBuildElement("N");
  meteoriteMaterial->AddElement(elN, 0.112*perCent);
  
  G4Element *elO = nistman->FindOrBuildElement("O");
  meteoriteMaterial->AddElement(elO, 42.41*perCent);
  
  G4Element *elNa = nistman->FindOrBuildElement("Na");
  meteoriteMaterial->AddElement(elNa, 0.4*perCent);
  
  G4Element *elMg = nistman->FindOrBuildElement("Mg");
  meteoriteMaterial->AddElement(elMg, 11.9*perCent);  
  
  G4Element *elAl = nistman->FindOrBuildElement("Al");
  meteoriteMaterial->AddElement(elAl, 1.14*perCent);
  
  G4Element *elSi = nistman->FindOrBuildElement("Si");
  meteoriteMaterial->AddElement(elSi, 13.2*perCent);
  
  G4Element *elP = nistman->FindOrBuildElement("P");
  meteoriteMaterial->AddElement(elP, 0.1*perCent);
  
  G4Element *elS = nistman->FindOrBuildElement("S");
  meteoriteMaterial->AddElement(elS, 3*perCent);
  
  G4Element *elCl = nistman->FindOrBuildElement("Cl");
  meteoriteMaterial->AddElement(elCl, 0.05*perCent);
  
  G4Element *elK = nistman->FindOrBuildElement("K");
  meteoriteMaterial->AddElement(elK, 0.04*perCent);

  G4Element *elCa = nistman->FindOrBuildElement("Ca");
  meteoriteMaterial->AddElement(elCa, 1.2*perCent);

  G4Element *elTi = nistman->FindOrBuildElement("Ti");
  meteoriteMaterial->AddElement(elTi, 0.06*perCent);
    
  G4Element *elCr = nistman->FindOrBuildElement("Cr");
  meteoriteMaterial->AddElement(elCr, 0.309*perCent);
  
  G4Element *elMn = nistman->FindOrBuildElement("Mn");
  meteoriteMaterial->AddElement(elMn, 0.17*perCent);
  
  G4Element *elFe = nistman->FindOrBuildElement("Fe");
  meteoriteMaterial->AddElement(elFe, 21.1*perCent);
  
  G4Element *elCo = nistman->FindOrBuildElement("Co");
  meteoriteMaterial->AddElement(elCo, 0.056*perCent);
  
  G4Element *elNi = nistman->FindOrBuildElement("Ni");
  meteoriteMaterial->AddElement(elNi, 1.25*perCent);
  
  G4Element *elCu = nistman->FindOrBuildElement("Cu");
  meteoriteMaterial->AddElement(elCu, 0.013*perCent);
  
  G4Element *elZn = nistman->FindOrBuildElement("Zn");
  meteoriteMaterial->AddElement(elZn, 0.02*perCent);

      
  // vacuum
  fWorldMat = new G4Material("Galactic", 1, 1.01*g/mole, universe_mean_density,
                 kStateGas, 2.73*kelvin, 3.e-18*pascal);

 ///G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}


G4Material* DetectorConstruction::MaterialWithSingleIsotope( G4String name,
                           G4String symbol, G4double density, G4int Z, G4int A)
{
  // define a material from an isotope
  G4int ncomponents;
  G4double abundance, massfraction;

  G4Isotope* isotope = new G4Isotope(symbol, Z, A);
 
  G4Element* element  = new G4Element(name, symbol, ncomponents=1);
  element->AddIsotope(isotope, abundance= 100.*perCent);
 
  G4Material* material = new G4Material(name, density, ncomponents=1);
  material->AddElement(element, massfraction=100.*perCent);

  return material;
}


G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
  // World
  G4Box*
  sWorld = new G4Box("World",                             //name
                    fWorldSize,fWorldSize,fWorldSize);    //dimensions
                   
  G4LogicalVolume*
  lWorld = new G4LogicalVolume(sWorld,                    //shape
                              fWorldMat,                  //material
                              "World");                   //name

  fPWorld = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(),              //at (0,0,0)
                            lWorld,                       //logical volume
                            "World",                      //name
                            0,                            //mother volume
                            false,                        //no boolean operation
                            0);                           //copy number
                            
  // Absorber
  G4Sphere* 
  sAbsor = new G4Sphere("Absorber",                       //name
                      0., fRadius, 0., twopi, 0., pi);    //dimensions

  fLAbsor = new G4LogicalVolume(sAbsor,                   //shape
                              fMaterial,                  //material
                              fMaterial->GetName());      //name
                               
  fPAbsor = new G4PVPlacement(0,                          //no rotation
                            G4ThreeVector(),              //at (0,0,0)
                            fLAbsor,                      //logical volume
                            fMaterial->GetName(),         //name
                            lWorld,                       //mother  volume
                            false,                        //no boolean operation
                            0);                           //copy number
  PrintParameters();
  
  //always return the root volume
  return fPWorld;
}


void DetectorConstruction::PrintParameters()
{
  G4cout << "\n The Absorber is " << G4BestUnit(fRadius,"Length")
         << " of " << fMaterial->GetName() 
         << "\n \n" << fMaterial << G4endl;
}


void DetectorConstruction::SetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
     G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  
  if (pttoMaterial) { 
    fMaterial = pttoMaterial;
    if(fLAbsor) { fLAbsor->SetMaterial(fMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
  else {
    G4cout << "\n--> warning from DetectorConstruction::SetMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}


void DetectorConstruction::SetRadius(G4double value)
{
  fRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}


G4double DetectorConstruction::GetVolume()
{
  G4double volume;
  volume = 4/3 * 3.14159 * fRadius*fRadius*fRadius;
  return volume;
}
