/// \file TB1106SteppingAction.hh
/// \brief Definition of the TB1106SteppingAction class

#ifndef TB1106SteppingAction_h
#define TB1106SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class TB1106EventAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class TB1106SteppingAction : public G4UserSteppingAction
{
  public:
    TB1106SteppingAction(TB1106EventAction* eventAction);
    virtual ~TB1106SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    TB1106EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
