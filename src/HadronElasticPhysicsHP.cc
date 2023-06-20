#include "HadronElasticPhysicsHP.hh"

#include "NeutronHPMessenger.hh"

#include "G4HadronicProcess.hh"
#include "G4ParticleHPElastic.hh"
#include "G4ParticleHPElasticData.hh"
#include "G4ParticleHPThermalScattering.hh"
#include "G4ParticleHPThermalScatteringData.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HadronElasticPhysicsHP::HadronElasticPhysicsHP(G4int ver)
: G4HadronElasticPhysics(ver),
  fThermal(true), fNeutronMessenger(0)  
{
  fNeutronMessenger   = new NeutronHPMessenger(this);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HadronElasticPhysicsHP::~HadronElasticPhysicsHP()
{
  delete fNeutronMessenger;  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HadronElasticPhysicsHP::ConstructProcess()
{
  G4HadronElasticPhysics::ConstructProcess();
  GetNeutronModel()->SetMinEnergy(19.5*MeV);

  G4HadronicProcess* process = GetNeutronProcess();
  G4ParticleHPElastic* model1 = new G4ParticleHPElastic();
  process->RegisterMe(model1);
  process->AddDataSet(new G4ParticleHPElasticData());

  if (fThermal) {
    model1->SetMinEnergy(4*eV);
    G4ParticleHPThermalScattering* model2 = new G4ParticleHPThermalScattering();
    process->RegisterMe(model2);
    process->AddDataSet(new G4ParticleHPThermalScatteringData());
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
