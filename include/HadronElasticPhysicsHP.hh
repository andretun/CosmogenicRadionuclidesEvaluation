#ifndef HadronElasticPhysicsHP_h
#define HadronElasticPhysicsHP_h 1

#include "globals.hh"
#include "G4HadronElasticPhysics.hh"

class NeutronHPMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HadronElasticPhysicsHP : public G4HadronElasticPhysics
{
  public: 
    HadronElasticPhysicsHP(G4int ver = 1); 
   ~HadronElasticPhysicsHP();

  public: 
    virtual void ConstructProcess();
    
  public:
    void SetThermalPhysics(G4bool flag) {fThermal = flag;};
      
  private:
    G4bool                  fThermal;
    NeutronHPMessenger*     fNeutronMessenger;          
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
