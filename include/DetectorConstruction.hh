#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4Material;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();

  public:
  
    virtual G4VPhysicalVolume* Construct();

    G4Material* 
    MaterialWithSingleIsotope(G4String, G4String, G4double, G4int, G4int);

    void SetRadius   (G4double);
    void SetMaterial (G4String);

  public:
                    
     G4double           GetRadius()     {return fRadius;};
     G4double           GetWorldSize()  {return fWorldSize;};
     G4Material*        GetMaterial()   {return fMaterial;};
     G4double           GetVolume();

     void               PrintParameters();

  private:
     
     G4double           fRadius;
     G4Material*        fMaterial;
     G4LogicalVolume*   fLAbsor;
     G4VPhysicalVolume* fPAbsor;

     G4Material*        meteoriteMaterial;
     
     G4double           fWorldSize;
     G4Material*        fWorldMat;
     G4VPhysicalVolume* fPWorld;
     
     DetectorMessenger* fDetectorMessenger;

  private:
    
     void               DefineMaterials();
     G4VPhysicalVolume* ConstructVolumes();
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif
