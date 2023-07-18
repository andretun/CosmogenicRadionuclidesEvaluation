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
/// \file HistoManager.cc
/// \brief Implementation of the HistoManager class

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


HistoManager::HistoManager()
  : fFileName("RadionuclidesProduction")
{
  Book();
}


HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}


void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);     //enable inactivation of histograms
  
  // Define histograms start values
  const G4int kMaxHisto = 9;
  const G4String id[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8"};    // Radionuclides
  const G4String title[] = {"Al26 number",            //0
                            "Mn54 number",            //1
                            "Co57 number",            //2
                            "Na22 number",            //3
                            "Co60 number",            //4
                            "Ti44 number",            //5
                            "Ca41 number",            //6
                            "Cl36 number",            //7
                            "Be10 number",            //8
                           };
  // Default values (to be reset via /analysis/h1/set command) 
  G4int nbins     = 100;
  G4double rmin   = -1*cm;
  G4double rmax   = 1*cm;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) { 
  G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, rmin, rmax);
  analysisManager->SetH1Activation(ih, false);
  }

}
