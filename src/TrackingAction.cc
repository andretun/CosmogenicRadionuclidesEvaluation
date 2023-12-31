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
/// \file TrackingAction.cc
/// \brief Implementation of the TrackingAction class

#include "TrackingAction.hh"

#include "Run.hh"
#include "EventAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4StepStatus.hh"
#include "G4ParticleTypes.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


TrackingAction::TrackingAction(EventAction* event)
:G4UserTrackingAction(), fEventAction(event)
{}


void TrackingAction::PreUserTrackingAction(const G4Track* track)
{  
  //count secondary particles
  if (track->GetTrackID() == 1) return;  
  G4String name   = track->GetDefinition()->GetParticleName();
  G4double energy = track->GetKineticEnergy();
  Run* run = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());    
  run->ParticleCount(name, energy);
       
  // histograms: energy at creation
  G4AnalysisManager* analysis = G4AnalysisManager::Instance();
 
  const G4ParticleDefinition* particle = track->GetParticleDefinition();  //particle
  G4String type = particle->GetParticleType();                            //particle type
  G4ThreeVector posVector;                                                //particle position (x, y, z)
  G4double posRadius;                                                     //particle position r
  G4double depth;                                                         //particle radial depth

  G4double meteoriteRadius = 241*m;	                                      //meteorite radius
  G4double histogramX = 8*m;                                              //histogram X axis
  
  if (type == "nucleus") {
    G4int atomicNumber = particle->GetAtomicNumber();                     //particle atomic mumber
    G4int atomicMass = particle->GetAtomicMass();                         //particle atomic mass

    // Al26
    if(atomicNumber == 13 && atomicMass == 26) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(0, depth);
      // G4cout << "1) Al26 position: " << posRadius << " mm" << G4endl;
      // G4cout << "2) Al26 depth: " << depth << " mm" << G4endl;
      // G4cout << "3) Met Radius: " << meteoriteRadius << " mm" << G4endl << G4endl;
    }

    // Mn54
    if(atomicNumber == 25 && atomicMass == 54) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(1, depth);
      // G4cout << "Mn54 pos: " << depth/10 << " cm" << G4endl;
    }

    //Co57
    if(atomicNumber == 27 && atomicMass == 57) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(2, depth);
      // G4cout << "Co57 pos: " << depth/10 << " cm" << G4endl;
    }

    //Na22
    if(atomicNumber == 11 && atomicMass == 22) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(3, depth);
      // G4cout << "Na22 pos: " << posRadius/1000 << G4endl;
    }

    //Co60
    if(atomicNumber == 27 && atomicMass == 60) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(4, depth);
      // G4cout << "Co60 pos: " << depth/10 << " cm" << G4endl;
    }

    //Ti44
    if(atomicNumber == 22 && atomicMass == 44) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(5, depth);
      // G4cout << "Ti44 pos: " << depth/10 << " cm" << G4endl;
    }

    //Ca41
    if(atomicNumber == 20 && atomicMass == 41) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(6, depth);
      // G4cout << "Ca41 pos: " << depth/10 << " cm" << G4endl;
    }

    //Cl36
    if(atomicNumber == 17 && atomicMass == 36) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(7, depth);
      // G4cout << "Ca41 pos: " << depth/10 << " cm" << G4endl;
    }

    //Be10
    if(atomicNumber == 4 && atomicMass == 10) {
      posVector = track->GetPosition(); // Position in which Al26 is created
      posRadius = sqrt(posVector.getX()*posVector.getX() + posVector.getY()*posVector.getY() + posVector.getZ()*posVector.getZ()); // mm
      depth = meteoriteRadius - posRadius; // The default unit of measure is mm
      if(depth <= histogramX)
        analysis->FillH1(8, depth);
      // G4cout << "Be10 pos: " << depth/10 << " cm" << G4endl;
    }

  }

}
