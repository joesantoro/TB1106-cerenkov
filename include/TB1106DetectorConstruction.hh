/// \file TB1106DetectorConstruction.hh
/// \brief Definition of the TB1106DetectorConstruction class

#ifndef TB1106DetectorConstruction_h
#define TB1106DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "TB1106SensitiveDetector.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class TB1106DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    G4LogicalVolume* logicEnv;
    G4LogicalVolume* logicDetectorArray;

    TB1106DetectorConstruction();
    virtual ~TB1106DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

private:
    //G4LogicalVolume* logicEnv;
    virtual void ConstructSDandField();

  protected:
    G4LogicalVolume*  fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

