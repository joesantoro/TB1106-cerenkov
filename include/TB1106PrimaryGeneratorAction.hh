
/// \file TB1106PrimaryGeneratorAction.hh
/// \brief Definition of the B1PrimaryGeneratorAction class

#ifndef TB1106PrimaryGeneratorAction_h
#define TB1106PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4Box;

/// The primary generator action class with particle gun.
/// The default kinematics is a 6 MeV gamma, randomly distribued 
/// in a 10x10cm beam on the top of the phantom.

class TB1106PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    TB1106PrimaryGeneratorAction();    
    virtual ~TB1106PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event*);         
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4Box* fEnvelopeBox;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
