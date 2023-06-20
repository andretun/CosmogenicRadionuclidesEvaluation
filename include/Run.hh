#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "G4VProcess.hh"
#include "globals.hh"
#include <map>

class DetectorConstruction;
class G4ParticleDefinition;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class Run : public G4Run
{
  public:
    Run(DetectorConstruction*);
   ~Run();

  public:
    void SetPrimary(G4ParticleDefinition* particle, G4double energy);
    void CountProcesses(const G4VProcess* process);
    void ParticleCount(G4String, G4double);

    virtual void Merge(const G4Run*);
    void EndOfRun();     
   
  private:
    struct ParticleData {
     ParticleData()
       : fCount(0), fEmean(0.), fEmin(0.), fEmax(0.) {}
     ParticleData(G4int count, G4double ekin, G4double emin, G4double emax)
       : fCount(count), fEmean(ekin), fEmin(emin), fEmax(emax) {}
     G4int     fCount;
     G4double  fEmean;
     G4double  fEmin;
     G4double  fEmax;
    };
     
  private:
    DetectorConstruction* fDetector;
    G4ParticleDefinition* fParticle;
    G4double              fEkin;
    
    G4double fEnergyDeposit, fEnergyDeposit2;
    G4double fEnergyFlow,    fEnergyFlow2;
    
    std::map<G4String,G4int>        fProcCounter;
    std::map<G4String,ParticleData> fParticleDataMap1;
    std::map<G4String,ParticleData> fParticleDataMap2;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
