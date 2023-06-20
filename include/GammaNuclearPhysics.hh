#ifndef GammaNuclearPhysics_h
#define GammaNuclearPhysics_h 1

#include "globals.hh"
#include "G4VPhysicsConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class GammaNuclearPhysics : public G4VPhysicsConstructor
{
  public:
    GammaNuclearPhysics(const G4String& name="gamma");
   ~GammaNuclearPhysics();

  public:
    virtual void ConstructParticle() { };
    virtual void ConstructProcess();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

