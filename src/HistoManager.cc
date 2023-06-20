#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("RadionuclidesProduction")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
